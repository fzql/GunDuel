// OpportunistPlayer by ColdK
// PPCG: http://codegolf.stackexchange.com/a/104902/11933

#ifndef __OPPORTUNIST_PLAYER_HPP__
#define __OPPORTUNIST_PLAYER_HPP__

#include "Player.hpp"

#include <string>
#include <vector>

class OpportunistPlayer final : public Player
{
public:
	OpportunistPlayer(size_t opponent = -1) : Player(opponent) {}

public:
	virtual Action fight()
	{
		switch (getTurn() % 3)
		{
		case 0:
			return load();
			break;
		case 1:
			return metal();
			break;
		case 2:
			return bullet();
			break;
		}
		return plasma();
	}
};

#endif // !__OPPORTUNIST_PLAYER_HPP__