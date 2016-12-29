// HumanPlayer.hpp
// A human player. You (via the console) decide what they will do!

#ifndef __HUMAN_PLAYER_HPP__
#define __HUMAN_PLAYER_HPP__

#include "Player.hpp"
#include <iostream>
#include <conio.h>

class HumanPlayer final : public Player
{
public:
	HumanPlayer(size_t opponent = -1) : Player(opponent) {}

private:
	static const char *RESULT[3];

public:
	virtual Action fight()
	{
		std::cout << " :: Turn " << getTurn() << std::endl;

		// Prompts for player input
		int ch;
		bool acceptableInput = false;
		do {
			std::cout << "    You [0/12/-=] >> ";
			ch = _getch();
			acceptableInput = ch == '0' || ch == '1' || ch == '2' || ch == '-' || ch == '=';
			if (!acceptableInput)
			{
				std::cout << std::endl;
			}
		} while (!acceptableInput);
		std::cout << "[" << (char)ch << "] ";

		// Displays player action
		Action action;
		switch (ch)
		{
		case '1':
			std::cout << "fire a bullet";
			action = bullet();
			break;
		case '2':
			std::cout << "fire a plasma beam";
			action = plasma();
			break;
		case '-':
			std::cout << "defend using metal shield";
			action = metal();
			break;
		case '=':
			std::cout << "defend using thermal deflector";
			action = thermal();
			break;
		default:
			std::cout << "load ammo";
			action = load();
		}
		std::cout << " (" << getAmmo() << " ammo)" << std::endl;

		// Submit action
		return action;
	}

	virtual void perceive(Action action)
	{
		Player::perceive(action);
		std::cout << "    Opponent selects [" << ACTION[(size_t)action] << "] ";
		switch (action)
		{
		case LOAD:
			std::cout << "load ammo";
			break;
		case BULLET:
			std::cout << "fire a bullet";
			break;
		case PLASMA:
			std::cout << "fire a plasma beam";
			break;
		case METAL:
			std::cout << "defend using metal shield";
			break;
		case THERMAL:
			std::cout << "defend using thermal deflector";
			break;
		}
		std::cout << " (" << getAmmoOpponent() << " ammo)" << std::endl;
	}

	virtual void declared(Result result)
	{
		std::cout << " :: You " << RESULT[(size_t)result]
			<< " after " << getTurn() << " turns!" << std::endl
			<< " :: Replay" << std::endl;

		std::cout << "    YOU " << toActionString(getHistory()) << std::endl;
		std::cout << "    FOE " << toActionString(getHistoryOpponent()) << std::endl;
	};
};

const char *HumanPlayer::RESULT[3] = { "drew", "won", "lost" };

#endif // !__HUMAN_PLAYER_HPP__