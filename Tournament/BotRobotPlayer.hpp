// BotRobot, ATaco
// PPCG: http://codegolf.stackexchange.com/a/104910/11933

// BotRobotPlayer.hpp
// ONE HUNDRED THOUSAND GENERATIONS TO MAKE THE ULTIMATE LIFEFORM!

#ifndef __BOT_ROBOT_PLAYER_HPP__
#define __BOT_ROBOT_PLAYER_HPP__

#include "Player.hpp"

class BotRobotPlayer final : public Player
{
public:
	BotRobotPlayer(size_t opponent = -1) : Player(opponent) {}

public:
	virtual Action fight()
	{
		std::string action = "";
		action += std::to_string(getAmmo());
		action += ":";
		action += std::to_string(getAmmoOpponent());

		int toDo = 3;

		for (int i = 0; i < 2; i++) {
			if (options[i].compare(action) == 0) {
				toDo = outputs[i];
				break;
			}
		}

		switch (toDo) {
		case 0:
			return load();
		case 1:
			return bullet();
		case 2:
			return plasma();
		case 3:
			return metal();
		default:
			return thermal();
		}
	}

private:
	std::string options[15] =
	{
		"0:0",
		"0:1",
		"0:2",
		"0:3",
		"0:4",
		"0:5",
		"1:0",
		"1:1",
		"1:2",
		"1:3",
		"2:0",
		"2:1",
		"2:4",
		"3:2",
		"4:3"
	};

	int outputs[15] =
	{
		0,
		3,
		0,
		4,
		4,
		3,
		1,
		3,
		1,
		1,
		2,
		0,
		3,
		2,
		1
	};
};

#endif // !__BOT_ROBOT_PLAYER_HPP__