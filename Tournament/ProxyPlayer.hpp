
// ProxyPlayer.hpp
// This will invoke another process and waits for a return code.

#ifndef __PROXY_PLAYER_HPP__
#define __PROXY_PLAYER_HPP__

#include "Player.hpp"
#include <string>
#include <sstream>

#undef UNICODE
#include <Windows.h>

class ProxyPlayer : public Player
{
public:
	// Initialize with process (without .exe) and identifier of opponent.
	ProxyPlayer(std::string const &process, std::string const &script = "", size_t opponent = -1)
		: mProcess(process), mScript(script), Player(opponent) {}

public:
	// Invoke other process.
	virtual Action fight()
	{
		DWORD choice = executeWithArguments(getArguments(3));
		switch (choice)
		{
		case 48: return load();
		case 49: return bullet();
		case 50: return plasma();
		case 45: return metal();
		case 61: return thermal();
		default: return (Action)(-1);
		}
	}

	// Notify external program of result.
	virtual void declared(Result result)
	{
		std::string arguments;
		switch (result)
		{
		case WIN:  arguments = getArguments(1);
		case LOSS: arguments = getArguments(2);
		default:   arguments = getArguments(0);
		}
		executeWithArguments(arguments);
	};

private:
	// External process name
	std::string mProcess;

	// External script name (for non binary submissions)
	std::string mScript;

	// Generates argument given game status.
	std::string getArguments(size_t status)
	{
		std::stringstream sst;
		sst << getOpponent()
			<< " " << getTurn()
			<< " " << status
			<< " " << getAmmo()
			<< " " << getAmmoOpponent();
		if (getTurn() > 0)
		{
			sst << " " << toActionString(getHistory())
				<< " " << toActionString(getHistoryOpponent());
		};
		return sst.str();
	}

	// Execute process with given arguments.
	DWORD executeWithArguments(std::string const &arguments) const
	{
		STARTUPINFO startup = { sizeof(startup) };
		PROCESS_INFORMATION process;
		LPSTR lpApplicationName;
		LPSTR lpCommandLine;

		lpApplicationName = const_cast<char *>(mProcess.c_str());
		if (mScript.length() == 0)
		{
			// Binary Proxy Player
			// name.exe arguments
			lpCommandLine = const_cast<char *>(arguments.c_str());
		}
		else
		{
			// Script Proxy Player
			// python.exe script.py arguments
			std::string actualArguments = mScript;
			actualArguments.append(1, ' ');
			actualArguments.append(arguments);
		}

		std::cout << mProcess << " " << arguments << std::endl;

		startup.cb = sizeof(startup);
		BOOL result = CreateProcess(lpApplicationName, lpCommandLine,
			NULL, NULL, TRUE, 0, NULL, NULL, &startup, &process);

		if (!result)
		{
			return -1;
		}
		else
		{
			// Wait for process to terminate and sanitize return code.
			DWORD exitCode;
			WaitForSingleObject(process.hProcess, INFINITE);
			GetExitCodeProcess(process.hProcess, &exitCode);
			return exitCode;
		}
	}
};

#define STRINGIFY(x) #x

// Example: BINARY_PLAYER(CustomPlayer)
// Effects: Invoke CustomPlayer.exe <arguments>
#define BINARY_PLAYER(x)                                              \
	class x final : public ProxyPlayer                                \
	{                                                                 \
	public:                                                           \
		x(size_t opponent = -1) : ProxyPlayer(#x ".exe", opponent) {} \
	};

// Example: SCRIPT_PLAYER(CustomPlayer, "python", "CustomScriptPlayer.py")
// Effects: Invoke python CustomScriptPlayer.py <arguments>
#define SCRIPT_PLAYER(x, y, z)                                        \
	class x final : public ProxyPlayer                                \
	{                                                                 \
	public:                                                           \
		x(size_t opponent = -1) : ProxyPlayer(y, z, opponent) {}      \
	};

#endif // !__CUSTOM_PLAYER_HPP__
