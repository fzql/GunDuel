// SpecificPlayer by Charles Jackson (Dysnomian) -- 21/01/2017
// PPCG: http://codegolf.stackexchange.com/a/104933/11933

#ifndef __SPECIFIC_PLAYER_HPP__
#define __SPECIFIC_PLAYER_HPP__

#include "Player.hpp"

class SpecificPlayer final : public Player
{
public:
	SpecificPlayer(size_t opponent = -1) : Player(opponent) {}

	//override
	virtual Action fight()
	{
		returnval = load(); //this should always be overwritten

							// if both players have no ammo we of course load
		if (oa == 0 && ma == 0) { returnval = load(); }

		// if (opponent has increased their ammo to a point they can fire something) then shield from it
		else if (oa == 1 && op == LOAD) { returnval = metal(); }
		else if (oa == 2 && op == LOAD) { returnval = thermal(); }
		else if (op == LOAD) { returnval = randomBlock(oa); }

		// if we have a master plan to follow through on do so, unless a defensive measure above is deemed necessary
		else if (nextDefined) { returnval = next; nextDefined = false; }

		// if opponent didn't fire their first shot on the second turn (turn 1) then we should block
		else if (t == 2 && oa >= 1) { returnval = randomBlock(oa); }

		//if opponent may be doing two attacks in a row
		else if (oa == 1 && op == BULLET) { returnval = metal(); }
		else if (oa == 2 && op == PLASMA) { returnval = thermal(); }

		// if we had no ammo last turn and still don't, load
		else if (ma == 0 && pa == 0) { returnval = load(); }

		// if we have just collected enough ammo to plasma, wait a turn before firing
		else if (ma == 2 && pa == 1) {
			returnval = randomBlock(oa); next = plasma(); nextDefined = true;
		}

		// time for some random actions
		else
		{
			int caseval = GetRandomInteger(4) % 3; //loading is less likely than attacking or blocking
			switch (caseval)
			{
			case 0: returnval = randomBlock(oa); break; // 40%
			case 1: returnval = randomAttack(ma); break; // 40%
			case 2: returnval = load(); break; // 20%
			}
		}

		pa = ma; //update previous ammo then update our current ammo
		switch (returnval)
		{
		case LOAD:
			ma += 1;
			break;
		case BULLET:
			ma -= 1;
			break;
		case PLASMA:
			ma -= 2;
			break;
		}
		t++; //also increment turn counter

		return returnval;
	}

	//override
	void perceive(Action action)
	{
		//record what action opponent took and update their ammo
		op = action;
		switch (action)
		{
		case LOAD:
			oa += 1;
			break;
		case BULLET:
			oa -= 1;
			break;
		case PLASMA:
			oa -= 2;
			break;
		}
	}

private:
	Action returnval; //our action to return
	Action next; //the action we want to take next turn - no matter what!
	bool nextDefined = false; //flag for if we want to be taking the "next" action.
	int t = 0; //turn number
	int ma = 0; //my ammo
	int oa = 0; //opponent ammo
	int pa = 0; //my previous ammo
	Action op; //opponent previous action

	Action randomBlock(int oa)
	{
		Action a;
		if (oa == 0) { a = load(); }
		else if (oa == 1) { a = metal(); }
		else
		{
			// more chance of ordianry block than laser block
			a = GetRandomInteger(2) % 2 ? metal() : thermal();
		}
		return a;
	}

	Action randomAttack(int ma)
	{
		Action a;
		if (ma == 0) { a = load(); }
		else if (ma == 1) { a = bullet(); }
		else
		{
			// more chance of ordianry attack than plasma
			a = GetRandomInteger(2) % 2 ? bullet() : plasma();
		}
		return a;
	}
};

#endif // !__SPECIFIC_PLAYER_HPP__