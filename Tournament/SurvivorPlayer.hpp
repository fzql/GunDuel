// SurvivorPlayer.hpp
// Live to fight another day

#ifndef __SURVIVOR_PLAYER_HPP__
#define __SURVIVOR_PLAYER_HPP__

#include "Player.hpp"

class SurvivorPlayer final : public Player
{
public:
	SurvivorPlayer(size_t opponent = -1) : Player(opponent)
	{
	}

public:
	virtual Action fight()
	{
		int myAmmo = getAmmo();
		int opponentAmmo = getAmmoOpponent();
		int turn = getTurn();
		if (turn == 0) {
			return load();
		}
		switch (opponentAmmo) {
		case 0:
			if (myAmmo > 2) {
				return GetRandomInteger(1) % 2 ? bullet() : plasma();
			}
			return load();
		case 1:
			if (myAmmo > 2) {
				return plasma();
			}
			return metal();
		default:
			if (myAmmo > 2) {
				return plasma();
			}
			return GetRandomInteger(1) % 2 ? metal() : thermal();
		}
	}
};

#endif // !__SURVIVOR_PLAYER_HPP__