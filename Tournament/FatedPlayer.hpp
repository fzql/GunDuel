// Fated Player by H Walters.
// PPCG: http://codegolf.stackexchange.com/a/105131/11933

#ifndef __FATEDPLAYER_H__
#define __FATEDPLAYER_H__

#include "Player.hpp"
#include <functional>
class FatedPlayer final : public Player
{
public:
	FatedPlayer(size_t o = -1) : Player(o) {}
	Action fight() {
		std::vector<std::function<Action()>>c{ [&] {return load(); } };
		switch (getAmmo()) {
		default:c.push_back([&] {return plasma(); });
		case 1:c.push_back([&] {return bullet(); });
		case 0:;
		}
		switch (getAmmoOpponent()) {
		default:c.push_back([&] {return thermal(); });
		case 1:c.push_back([&] {return metal(); });
		case 0:;
		}
		return c[GetRandomInteger(int(c.size() - 1))]();
	}
};

#endif