// SadisticShooter by muddyfish
// PPCG: http://codegolf.stackexchange.com/a/104947/11933

// SadisticShooter.hpp
// A very sad person. He likes to shoot people.

#ifndef __SAD_SHOOTER_PLAYER_HPP__
#define __SAD_SHOOTER_PLAYER_HPP__

#include <cstdlib>
#include "Player.hpp"
// #include <iostream>

class SadisticShooter final : public Player
{
public:
	SadisticShooter(size_t opponent = -1) : Player(opponent) {}
private:
	bool historySame(std::vector<Action> history, int elements) {
		if (history.size() < elements) return false;

		std::vector<Action> lastElements(history.end() - elements, history.end());

		for (Action const &action : lastElements)
			if (action != lastElements[0]) return false;
		return true;
	}
public:
	virtual Action fight()
	{
		int my_ammo = getAmmo();
		int opponent_ammo = getAmmoOpponent();
		int turn_number = getTurn();
		//std::cout << " :: Turn " << turn_number << " ammo: " << my_ammo << " oppo: " << opponent_ammo << std::endl;

		if (turn_number == 90) {
			// Getting impatient
			return load();
		}
		if (my_ammo == 0 && opponent_ammo == 0) {
			// It would be idiotic not to load here
			return load();
		}
		if (my_ammo >= 2 && historySame(getHistoryOpponent(), 3)) {
			if (getHistoryOpponent()[turn_number - 1] == THERMAL) return bullet();
			if (getHistoryOpponent()[turn_number - 1] == METAL) return thermal();
		}
		if (my_ammo < 2 && opponent_ammo == 1) {
			// I'd rather not die thank you very much
			return metal();
		}
		if (my_ammo == 1) {
			if (opponent_ammo == 0) {
				// You think I would just shoot you?
				return load();
			}
			if (turn_number == 2) {
				return thermal();
			}
			return bullet();
		}
		if (opponent_ammo >= 2) {
			// Your plasma weapon doesn't scare me
			return thermal();
		}
		if (my_ammo >= 2) {
			// 85% more bullet per bullet
			if (turn_number == 4) return bullet();
			return plasma();
		}
		// Just load the gun already
		return load();
	}
};

#endif // !__SAD_SHOOTER_PLAYER_HPP__
