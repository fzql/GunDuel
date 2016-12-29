// PlasmaPlayer by Brian J
// PPCG: http://codegolf.stackexchange.com/a/104933/11933

#ifndef __PLASMA_PLAYER_HPP__
#define __PLASMA_PLAYER_HPP__

#include "Player.hpp"

class PlasmaPlayer final : public Player
{
public:
	PlasmaPlayer(size_t opponent = -1) : Player(opponent) {}

	virtual Action fight()
	{
		// Imma Firin Mah Lazer!
		if (getAmmo() > 1) return plasma();

		// Imma Block Yur Lazer!
		if (getAmmoOpponent() > 1) return thermal();

		// Imma need more Lazer ammo
		return load();
	}
};

#endif // !__PLASMA_PLAYER_HPP__