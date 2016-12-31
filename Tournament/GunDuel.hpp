// GunDuel.hpp
// Implements a futuristic gun duel between two players

#ifndef __GUN_DUEL_HPP__
#define __GUN_DUEL_HPP__

#include "Player.hpp"

class GunDuel final
{
public:
	// Outcomes for each turn
	enum Outcome { DRAW, AWIN, BWIN };

	// Outcome table for two players
	const Outcome OUTCOME[5][5] =
	{
		{ DRAW, BWIN, BWIN, DRAW, DRAW },
		{ AWIN, DRAW, BWIN, DRAW, AWIN },
		{ AWIN, AWIN, DRAW, AWIN, DRAW },
		{ DRAW, DRAW, BWIN, DRAW, DRAW },
		{ DRAW, BWIN, DRAW, DRAW, DRAW }
	};

public:
	// Register a duel from two players
	GunDuel(Player &a, Player &b, size_t turns = 100) : mA(a), mB(b), mTurns(turns) {}

public:
	// Start a duel between two players
	Outcome fight()
	{
		size_t turn = 0;
		bool forceEnd = false;
		Outcome status = DRAW;
		while (!forceEnd && turn < mTurns && status == DRAW)
		{
			Player::Action actionA = mA.fight();
			Player::Action actionB = mB.fight();
			// Verify that actions are valid from both sides.
			bool validA = mA.getAmmo() >= 0 && (size_t)actionA < (size_t)5;
			bool validB = mB.getAmmo() >= 0 && (size_t)actionB < (size_t)5;
			mA.perceive(actionB);
			mB.perceive(actionA);

			if (validA && validB)
				status = OUTCOME[actionA][actionB];
			else
			{
				if (validA && !validB)
					status = AWIN;
				else if (!validA && validB)
					status = BWIN;
				else
					status = DRAW;
				forceEnd = true;
			}
			++turn;
		}
		// Notify players of the outcome.
		switch (status)
		{
		case AWIN:
			mA.declared(Player::WIN);
			mB.declared(Player::LOSS);
			break;
		case BWIN:
			mA.declared(Player::LOSS);
			mB.declared(Player::WIN);
			break;
		default:
			mA.declared(Player::DRAW);
			mB.declared(Player::DRAW);
		}
		return status;
	}

private:
	// Players.
	Player &mA, &mB;

	// Limit on total turns per duel.
	size_t mTurns;
};

#endif // !__GUN_DUEL_HPP__