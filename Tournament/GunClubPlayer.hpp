// GunClubPlayer.hpp
// A gun club enthusiast. Minimalistic example of derived class

#ifndef __GUN_CLUB_PLAYER_HPP__
#define __GUN_CLUB_PLAYER_HPP__

#include "Player.hpp"

class GunClubPlayer final : public Player
{
public:
	GunClubPlayer(size_t opponent = -1) : Player(opponent) {}

public:
	virtual Action fight()
	{
		return getTurn() % 2 ? bullet() : load();
	}
};

#endif // !__GUN_CLUB_PLAYER_HPP__