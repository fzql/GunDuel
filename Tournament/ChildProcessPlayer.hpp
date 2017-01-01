#ifndef __CHILDPROCESSPLAYER_HPP__
#define __CHILDPROCESSPLAYER_HPP__

#include "Player.hpp"
#include <Windows.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

// Template takes an unsigned int as a uniquification id for each spawned process.
//
// RECOMMENDED USAGE:
//
// STEP 1:
//    In Tournament.cpp, create a type for each external player:
//        typedef ChildProcessPlayer<0> PythonicPlayer;
//        typedef ChildProcessPlayer<2> CygwinBashPlayer;
//
// STEP 2:
//   Use the above typedef for the Pool::newPlayer's make_unique calls.
//
// STEP 3:
//   In Tournament.cpp in main, before running the tournament, bind each incarnation to a process:
//       PythonicPlayer::module() = "python pythonic.py";
//       CygwinBashPlayer::module() = "C:\\cygwin\\bin\\bash -c bashplayer.sh"
//   Optionally, if a particular external player prefers a nl style, configure it as well:
//       CygwinBashPlayer::nlstyle(CygwinBashPlayer::NLS_LF);
// =========
//
// STRICT ENTRY RULES:
//
// There's a fixed requirement for all entries on how to do I/O, since both stdin and stdout
// are connected to the tournament driver.  Violating this could lead to a deadlock.
// All entries MUST follow this exact algorithm (in pseudocode):
//
//      LOOP FOREVER
//          READ LINE INTO L
//          IF (LEFT(L,1) == 'I')
//             INITIALIZE ROUND
//             // i.e., set your/opponent ammo to 0, if tracking them
//             // Note: The entire line at this point is a unique id per opponnent;
//             // optionally track this as well.
//             CONTINUE LOOP
//          ELSE IF (LEFT(L,1) == 'F')
//             WRITELN F // where F is your move
//          ELSE IF (LEFT(L,1) == 'P')
//             PROCESS MID(L,2,1)      // optional
//          END IF
//      CONTINUE LOOP
//
// Here, F is one of '0', '1', '2', '-', or '=' for load/bullet/plasma/metal/thermal.
//
// PROCESS means to optionally respond to what your opponent did (including tracking
// your opponent's ammo if you're doing this).  Note that the opponent's action is
// also one of '0', '1', '2', '-', or '=', and is in the second character.
template <unsigned id>
class ChildProcessPlayer final : public Player 
{
public:
	// Both a setter and getter of the module used for this player type
	static const char*& module() 
	{
		static const char* x = 0; return x;
	}
	// New line styles
	enum NewLineStyle {
		NLS_CURRENT,
		NLS_LF,    // LF only (*NIX style)
		NLS_CRLF,  // CR-LF (Windows style)
		NLS_CR     // CR only (MAC style)
	};
	// Optionally set this for a ChildProcessPlayer if they are expecting
	// different newline conventions.
	static const char* newline(NewLineStyle nls = NLS_CURRENT) {
		static NewLineStyle style = NLS_CRLF;
		if (nls == NLS_CURRENT) nls = style;
		switch (nls) {
		default:
		case NLS_CRLF: return "\r\n";
		case NLS_LF:   return "\n";
		case NLS_CR:   return "\r"; // not sure if we'll need this unless _proxying_ macs via child or something
		}
	}
	static STARTUPINFO& si() { static STARTUPINFO x = {sizeof(STARTUPINFO)}; return x; }
	static PROCESS_INFORMATION& pi() { static PROCESS_INFORMATION x = {}; return x; }
	static HANDLE& toChildH() { static HANDLE h = INVALID_HANDLE_VALUE; return h; }
	static HANDLE& fromChildH() { static HANDLE h = INVALID_HANDLE_VALUE; return h; }
	// Both setter and getter for a failure condition
	static const char*& failure(const char* set = 0) {
		static const char* f = 0;
		if (set) {
		   f = set;
		   std::cerr << "ChildProcess<" << id << "> failure: " << f << std::endl;
		}
		return f;
	}
	// Utility... report on pipe configuration
	static void reportPipe(HANDLE p) {
		DWORD flags, outBufferSize, inBufferSize, maxInstances;
		if (!GetNamedPipeInfo(p, &flags, &outBufferSize, &inBufferSize, &maxInstances)) {
			std::cerr << "Report error for pipe: " << GetLastError() << std::endl;
			return;
		}
		std::cerr
			<< ((flags & PIPE_SERVER_END) ? "SERVER" : "CLIENT")
			<< ((flags & PIPE_TYPE_MESSAGE) ? " MESSAGE" : " BYTE") << " PIPE:"
			<< " out buffer " << outBufferSize << ", in buffer " << inBufferSize
			<< " max instances " << maxInstances << std::endl;
	}
	// Wrapper for creating new pipes
	static BOOLEAN NewPipe(HANDLE& in, HANDLE& out, unsigned buffer=0) {
		SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES) };
		saAttr.bInheritHandle = TRUE;
		BOOLEAN rv = CreatePipe(&in, &out, &saAttr, buffer);
		reportPipe(in);
		reportPipe(out);
		return rv;
	}
	// Start the process
	static void startProcess() {
		// Start only the first time; this way we can just blindly call this
		// in the ctor.
		static bool started = false;
		if (started) return;
		started = true;

		// Handle's we're giving to the child
		HANDLE hChildStd_IN_Rd  = INVALID_HANDLE_VALUE;
		HANDLE hChildStd_OUT_Wr = INVALID_HANDLE_VALUE;

		if (!NewPipe(fromChildH(), hChildStd_OUT_Wr, 1))
		{
			failure("1. Failed to create pipes for child stdout");
			return;
		}
		if (!NewPipe(hChildStd_IN_Rd, toChildH(), 1))
		{
			failure("2. Failed to create pipes for child stdin");
			return;
		}
		// Tell CreateProcess to use handles from our pipes
		// for stdin/stdout
		si().hStdOutput = hChildStd_OUT_Wr;
		si().hStdInput = hChildStd_IN_Rd;
		si().dwFlags |= STARTF_USESTDHANDLES;

		// Convert string literal stored in module
		// to a volatile nul-terminated char for use by ancient CreateProcess method.
		std::string modulestr(module());
		std::vector<char> modulebuffer(modulestr.size() + 1);
		std::copy(modulestr.begin(), modulestr.end(), modulebuffer.begin());
		// Create the child process
		BOOL bSuccess =
			CreateProcessA(0,
			 &modulebuffer[0],
			 NULL,
			 NULL,
			 TRUE,
			 0,
			 NULL,
			 NULL,
			 &si(),
			 &pi());
		// Report on failure
		if (!bSuccess)
		{
			failure("3. Failed to spawn this child");
			std::cerr << "ERROR CODE: " << GetLastError() << std::endl;
			return;
		}
		CloseHandle(pi().hProcess);
		CloseHandle(pi().hThread);
	}
	// Writes a string to the child process's stdin
	static void write(const std::string& value) {
		if (toChildH() == INVALID_HANDLE_VALUE) return;
		DWORD bytesWritten = 0;
		if (!WriteFile(toChildH(), value.c_str(), value.size(), &bytesWritten, 0)) {
			failure("Problem writing to child");
			std::cerr << "E:" << GetLastError() << std::endl;
			CloseHandle(toChildH());
			toChildH() = INVALID_HANDLE_VALUE;
		}
	}
	// Writes a line to the child process's stdin using the configured NL style
	static void writeln(const std::string& value) {
		write(value + newline());
	}
	// Read a character from the child process's stdout.
	static int read() {
		if (fromChildH() == INVALID_HANDLE_VALUE) return std::char_traits<char>::eof();
		char rv='~';
		DWORD bytesRead = 0, bytesAvail=0;
		if (!ReadFile(fromChildH(), reinterpret_cast<void*>(&rv), 1, &bytesRead, 0)) {
			failure("Problem reading from child");
			std::cerr << "E:" << GetLastError() << std::endl;
			CloseHandle(fromChildH());
			fromChildH() = INVALID_HANDLE_VALUE;
			return std::char_traits<char>::eof();
		}
		if (bytesRead == 0) {
			failure("Premature end of file from child");
			CloseHandle(fromChildH());
			fromChildH() = INVALID_HANDLE_VALUE;
			return std::char_traits<char>::eof();
		}
		return std::char_traits<char>::to_int_type(rv);
	}
	ChildProcessPlayer(size_t opponent)
		: Player(opponent)
	{
		// Start the child if we haven't already
		startProcess();
		// Tell the child there's a new round, and which opponent is playing
		writeln(std::string("I") + std::to_string(opponent));
	}
	Action fight() {
		size_t response;
		// Ask child process to move
		writeln("F");
		// Read until we see a move
		for (;;) {
			int i = read();
			if (i == std::char_traits<char>::eof()) {
				// Create an invalid value to return
				// (trip invalid value handling logic)
				return static_cast<Player::Action>(5);
			}
			char c = std::char_traits<char>::to_char_type(i);
			static const std::string responses = "012-=";
			response = responses.find_first_of(c);
			if (response < 5) {
				return static_cast<Player::Action>(response);
			}
		}
	}
	void perceive(Action a) {
		// Tell child process what the opponent did
		switch (a) {
		case LOAD   : writeln("P0"); return;
		case BULLET : writeln("P1"); return;
		case PLASMA : writeln("P2"); return;
		case METAL  : writeln("P-"); return;
		case THERMAL: writeln("P="); return;
		default:      writeln("P?");
		}
	}
};

#endif