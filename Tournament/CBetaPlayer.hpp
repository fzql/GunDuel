// CBetaPlayer (c¦Â) by George V. Williams
// PPCG: http://codegolf.stackexchange.com/a/105154/11933

#ifndef __CBETA_PLAYER_HPP__
#define __CBETA_PLAYER_HPP__

#include "Player.hpp"
#include <iostream>

class CBetaPlayer final : public Player
{
public:
	CBetaPlayer(size_t opponent = -1) : Player(opponent)
	{
	}

public:
	virtual Action fight()
	{
		int my_ammo = getAmmo(), opp_ammo = getAmmoOpponent();

		while (my_ammo >= MAX_AMMO || opp_ammo >= MAX_AMMO) {
			my_ammo--;
			opp_ammo--;
		}

		if (my_ammo < 0) my_ammo = 0;
		if (opp_ammo < 0) opp_ammo = 0;

		double cdf = GetRandomDouble();
		int move = -1;
		while (cdf > 0 && move < MAX_MOVES - 1)
			cdf -= probs[my_ammo][opp_ammo][++move];

		switch (move) {
		case 0: return load();
		case 1: return bullet();
		case 2: return plasma();
		case 3: return metal();
		case 4: return thermal();
		default: return fight();
		}
	}

	static double GetRandomDouble() {
		static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		static std::default_random_engine generator((unsigned)seed);
		std::uniform_real_distribution<double> distribution(0.0, 1.0);
		return distribution(generator);
	}

private:
	static const int MAX_AMMO = 5;
	static const int MAX_MOVES = 5;

	double probs[MAX_AMMO][MAX_AMMO][5] =
	{
		{ { 1, 0, 0, 0, 0 },{ 0.58359, 0, 0, 0.41641, 0 },{ 0.28835, 0, 0, 0.50247, 0.20918 },{ 0.17984, 0, 0, 0.54611, 0.27405 },{ 0.12707, 0, 0, 0.56275, 0.31018 } },
		{ { 0.7377, 0.2623, 0, 0, 0 },{ 0.28907, 0.21569, 0, 0.49524, 0 },{ 0.0461, 0.06632, 0, 0.53336, 0.35422 },{ 0.06464, 0.05069, 0, 0.43704, 0.44763 },{ 0.02215, 0.038, 0, 0.33631, 0.60354 } },
		{ { 0.47406, 0.37135, 0.1546, 0, 0 },{ 0.1862, 0.24577, 0.15519, 0.41284, 0 },{ 0, 0.28343, 0.35828, 0, 0.35828 },{ 0, 0.20234, 0.31224, 0, 0.48542 },{ 0, 0.12953, 0.26546, 0, 0.605 } },
		{ { 0.33075, 0.44563, 0.22362, 0, 0 },{ 0.17867, 0.20071, 0.20071, 0.41991, 0 },{ 0, 0.30849, 0.43234, 0, 0.25916 },{ 0, 0.21836, 0.39082, 0, 0.39082 },{ 0, 0.14328, 0.33659, 0, 0.52013 } },
		{ { 0.24032, 0.48974, 0.26994, 0, 0 },{ 0.14807, 0.15668, 0.27756, 0.41769, 0 },{ 0, 0.26804, 0.53575, 0, 0.19621 },{ 0, 0.22106, 0.48124, 0, 0.2977 },{ 0, 0.15411, 0.42294, 0, 0.42294 } }
	};


};

#endif // !__CBETA_PLAYER_HPP__