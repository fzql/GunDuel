// Player.hpp
// Holds a tournament.

#include "Player.hpp"
#include "GunClubPlayer.hpp"
#include "HumanPlayer.hpp"

#include "ProxyPlayer.hpp"
#include "GunDuel.hpp"

int main()
{
	size_t duelLength = 100;
	size_t repetition = 1;

	HumanPlayer h(2);
	GunClubPlayer g(1);

	GunDuel duel(h, g, duelLength);
	GunDuel::Outcome outcome = duel.fight();
	switch (outcome)
	{
	case GunDuel::AWIN:
		std::cout << " :: AWIN" << std::endl;
		break;
	case GunDuel::BWIN:
		std::cout << " :: BWIN" << std::endl;
		break;
	default:
		std::cout << " :: DRAW" << std::endl;
		break;
	}
	system("pause");
}