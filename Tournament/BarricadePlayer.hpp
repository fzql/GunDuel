// BarricadePlayer by devRicher
// PPCG: http://codegolf.stackexchange.com/a/104909/11933

// BarricadePlayer.hpp
// A very tactical player.

#ifndef __BARRICADE_PLAYER_HPP__
#define __BARRICADE_PLAYER_HPP__

#include "Player.hpp"
#include <cstdlib>
#include <ctime>

class BarricadePlayer final : public Player
{
public:
	BarricadePlayer(size_t opponent = -1) : Player(opponent) { srand(time(0)); }

public:
	virtual Action fight()
	{
		if (getTurn() == 0) { return load(); }
		int r = rand() % 100 + 1; //Get a random
		if ((r <= 15) && (getAmmo() > 0)) { return bullet(); } //Override any action, and just shoot
		else
		{
			if (getTurn() % 5 == 0) //Every first and fifth turn
				return load();
			if (getAmmoOpponent() == 1) return metal();
			if (getAmmoOpponent() > 1) { return r <= 50 ? metal() : thermal(); }
			if (getAmmoOpponent() == 0) return load();

		}
		return bullet();
	}
};

#endif // !__BARRICADE_PLAYER_HPP__