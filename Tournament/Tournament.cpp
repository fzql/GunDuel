// Player.hpp
// Holds a tournament.

// C++ Entries
#include "GunClubPlayer.hpp"
#include "OpportunistPlayer.hpp"
#include "TurtlePlayer.hpp"
#include "BarricadePlayer.hpp"
#include "BotRobotPlayer.hpp"
#include "PlasmaPlayer.hpp"
#include "SadisticShooter.hpp"
#include "DeceptivePlayer.hpp"
#include "StudiousPlayer.hpp"
#include "SurvivorPlayer.hpp"
#include "FatedPlayer.hpp"
#include "CBetaPlayer.hpp"
#include "MontePlayer.hpp"
#include "CamtoPlayer.hpp"
#include "HanSoloPlayer.hpp"
#include <functional>
#include "HumanPlayer.hpp"

// Command Line Interface non-C++ Entries
#include "ProxyPlayer.hpp"

// Standard I/O Interface Entries
#include "ChildProcessPlayer.hpp"
// using TestChildPlayer = ChildProcessPlayer<0>;

// Tournament
#include "Tournament.hpp"

// Attempt to support C++11 (now useless since many entries require C++14)
#if __cplusplus > 201103L
using std::make_unique;
#else
namespace {
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}
#endif

struct LateEntryChild : public ChildProcessPlayer < 65536 > {
	LateEntryChild(size_t opponent) : ChildProcessPlayer< 65536 >(opponent) {}
};

// Tournament pool of all valid entries.
class Pool final
{
public:
	enum { pool_size = 15 };

	static std::unique_ptr<Player> newPlayer(size_t index, size_t opponent = -1)
	{
		if (index >= size()) return nullptr;
		return registry()[index](opponent);
	}
private:
	static std::vector<std::function<std::unique_ptr<Player>(size_t)>>& registry() {
		static std::vector<std::function<std::unique_ptr<Player>(size_t)>> thereg;
		return thereg;
	};
public:
	static void registerEntry(std::function<std::unique_ptr<Player>(size_t)> pred) { registry().emplace_back(pred); }
	static size_t size() { return registry().size(); }
};

int main(int argc, const char* argv[])
{
	size_t repetition = 100;

	static std::string late_entry_module;
	std::vector<std::string> arg(argv + 1, argv + argc);
	bool versusHuman = false;
	for (unsigned int i = 0, e = arg.size(); i < e; ++i) {
		if (arg[i] == "-nls=LF") {
			ChildProcessPlayer< 65536 >::newline(ChildProcessPlayer< 65536 >::NLS_LF);
			continue;
		}
		if (arg[i] == "-nls=CR") {
			ChildProcessPlayer< 65536 >::newline(ChildProcessPlayer< 65536 >::NLS_CR);
			continue;
		}
		if (arg[i] == "-nls=CRLF") {
			ChildProcessPlayer< 65536 >::newline(ChildProcessPlayer< 65536 >::NLS_CRLF);
			continue;
		}
		if (arg[i] == "-human") {
			versusHuman = true;
			continue;
		}
		if (arg[i] == "-lateentry") {
			// Consume the rest of the args
			for (; ++i < e;) {
				if (!late_entry_module.empty()) late_entry_module.push_back(' ');
				late_entry_module += arg[i];
			}
			break;
		}
		// If we make it here, we have no idea what's going on, so print help:
		std::cerr
			<< "Usage:\n"
			<< *argv << " [OPTIONS]\n"
			"\n"
			"With no [OPTIONS], this runs a standard tournament.\n"
			"\n"
			"OPTIONS include:\n"
			"  -nls=LF or -nls=CR or -nls=CRLF\n"
			"    Sets new line style for late entry (default CRLF).\n"
			"  -human\n"
			"    Instead of the current tournament entries adds a human player.\n"
			"    This option is ignored unless you also use -lateentry.\n"
			"    Note that this option must come *BEFORE* the -lateentry flag.\n"
			"  -lateentry [command]\n"
			"    Sets a \"late entry\", using the ChildProcessPlayer.\n"
			"    If this option is used, all arguments that follow will be used\n"
			"    as the command line to invoke the child.  The child process must\n"
			"    always read a line from stdin; it must always write a response\n"
			"    to stdout when the line is 'F'.  The response should be one of:"
			"    0, 1, 2, -, or = to load, shoot bullet, shoot plasma, raise metal,\n"
			"    or raise thermal respectively.  See contest rules for more details.\n"
			"\n"
			"    NOTE: LATE ENTRIES APPEAR ON THE SCOREBOARD AS \"LateEntryChild\"\n."
			<< std::endl;

		return 1;
	}

#define REGISTER_ENTRY(RAW_TYPE) Pool::registerEntry([](size_t opponent){return make_unique<RAW_TYPE>(opponent);})
	if (versusHuman && late_entry_module.empty()) {
		std::cerr
			<< "Sorry, but you can't play all the standard entries\n"
			<< "using this executable.  You can, however, play your own\n"
			<< "late entry." << std::endl;
		return 1;
	}
	if (versusHuman) {
		REGISTER_ENTRY(HumanPlayer);
	}
	else
	{
		REGISTER_ENTRY(GunClubPlayer);
		REGISTER_ENTRY(OpportunistPlayer);
		REGISTER_ENTRY(TurtlePlayer);
		REGISTER_ENTRY(BarricadePlayer);
		REGISTER_ENTRY(BotRobotPlayer);
		REGISTER_ENTRY(PlasmaPlayer);
		REGISTER_ENTRY(SadisticShooter);
		REGISTER_ENTRY(DeceptivePlayer);
		REGISTER_ENTRY(StudiousPlayer);
		REGISTER_ENTRY(SurvivorPlayer);
		REGISTER_ENTRY(FatedPlayer);
		REGISTER_ENTRY(CBetaPlayer);
		REGISTER_ENTRY(MontePlayer);
		REGISTER_ENTRY(CamtoPlayer);
		REGISTER_ENTRY(HanSoloPlayer);
	}

	if (!late_entry_module.empty()) {
		ChildProcessPlayer< 65536 >::module() = late_entry_module.c_str();
		std::cerr
			<< "--- LATE ENTRY FROM COMMAND LINE:\n"
			<< "[" << late_entry_module << "]" << std::endl;
		REGISTER_ENTRY(LateEntryChild);
	}

	// Test Child Player Configuration
	// TestChildPlayer::module() = "python TestChildPlayer.py";

	Tournament<Pool> tournament(repetition);
	tournament.run();

	std::cout << " :: Press Enter to Quit...";
	std::cin.ignore();
	return 0;
}
