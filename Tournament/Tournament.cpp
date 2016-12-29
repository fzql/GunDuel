// Player.hpp
// Holds a tournament.

#include "Tournament.hpp"

// C++ Entries
#include "GunClubPlayer.hpp"
#include "OpportunistPlayer.hpp"
#include "TurtlePlayer.hpp"
#include "BarricadePlayer.hpp"
#include "BotRobotPlayer.hpp"
#include "PlasmaPlayer.hpp"
#include "SadisticShooterPlayer.hpp"
#include "DeceptivePlayer.hpp"
#include <iostream>

// Tournament pool of all valid entries.
class Pool final
{
public:
	static std::unique_ptr<Player> newPlayer(size_t index, size_t opponent)
	{
		switch (index)
		{
		case 0: return std::make_unique<GunClubPlayer>(opponent);
		case 1: return std::make_unique<OpportunistPlayer>(opponent);
		case 2: return std::make_unique<TurtlePlayer>(opponent);
		case 3: return std::make_unique<BarricadePlayer>(opponent);
		case 4: return std::make_unique<BotRobotPlayer>(opponent);
		case 5: return std::make_unique<PlasmaPlayer>(opponent);
		case 6: return std::make_unique<SadisticShooterPlayer>(opponent);
		case 7: return std::make_unique<DeceptivePlayer>(opponent);
		default: return nullptr;
		}
	}

public:
	static size_t size() { return 8; }
};

int main()
{
	size_t repetition = 100;

	Tournament<Pool> tournament(repetition);
	tournament.run();

    std::cout<<"Press Enter to quit... ";
    std::cin.ignore();
    return 0;
}
