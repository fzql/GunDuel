// TurtlePlayer by FlipTack
// PPCG: http://codegolf.stackexchange.com/a/104905/11933

#include "Player.hpp"

// For randomness:
#include <ctime>
#include <cstdlib>

class TurtlePlayer final : public Player {

public:
	TurtlePlayer(size_t opponent = -1) : Player(opponent) { srand(time(0)); }

public:
	virtual Action fight() {
		if (getAmmoOpponent() > 0) {
			// Beware! Opponent has ammo!

			if (rand() % 5 == 0 && getAmmo() > 0)
				// YOLO it:
				return getAmmo() > 1 ? plasma() : bullet();

			// Play it safe:
			if (getAmmoOpponent() == 1) return metal();
			return rand() % 2 ? metal() : thermal();
		}

		if (getAmmo() == 0)
			// Nobody has ammo: Time to load up.
			return load();

		else if (getAmmo() > 1)
			// We have enough ammo for a plasma: fire it!
			return plasma();

		else
			// Either load, or take a shot.
			return rand() % 2 ? load() : bullet();
	}
};