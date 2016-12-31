// Player.hpp
// Holds a tournament.

// C++ Entries
#include "GunClubPlayer.hpp"
#include "OpportunistPlayer.hpp"
#include "TurtlePlayer.hpp"
#include "BarricadePlayer.hpp"
#include "BotRobotPlayer.hpp"
#include "PlasmaPlayer.hpp"
#include "SadisticShooter.hpp"
#include "DeceptivePlayer.hpp"
#include "StudiousPlayer.hpp"
#include "SurvivorPlayer.hpp"
#include "FatedPlayer.hpp"
#include "CBetaPlayer.hpp"
#include "MontePlayer.hpp"

// Non C++ Entries
#include "ProxyPlayer.hpp"
SCRIPT_PLAYER(PythonPlayer, "python", "PythonPlayer.py");

// Tournament
#include "Tournament.hpp"

// Support C++11
#if __cplusplus > 201103L
using std::make_unique;
#else
namespace {
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}
#endif

// Tournament pool of all valid entries.
class Pool final
{
public:
	static std::unique_ptr<Player> newPlayer(size_t index, size_t opponent = -1)
	{
		switch (index)
		{
		case 0: return make_unique<GunClubPlayer>(opponent);
		case 1: return make_unique<OpportunistPlayer>(opponent);
		case 2: return make_unique<TurtlePlayer>(opponent);
		case 3: return make_unique<BarricadePlayer>(opponent);
		case 4: return make_unique<BotRobotPlayer>(opponent);
		case 5: return make_unique<PlasmaPlayer>(opponent);
		case 6: return make_unique<SadisticShooter>(opponent);
		case 7: return make_unique<DeceptivePlayer>(opponent);
		case 8: return make_unique<StudiousPlayer>(opponent);
		case 9: return make_unique<SurvivorPlayer>(opponent);
		case 10: return make_unique<FatedPlayer>(opponent);
		case 11: return make_unique<CBetaPlayer>(opponent);
		case 12: return make_unique<MontePlayer>(opponent);
		case 13: return make_unique<PythonPlayer>(opponent);
		default: return nullptr;
		}
	}

public:
	static size_t size() { return 14; }
};

int main()
{
	size_t repetition = 100;

	Tournament<Pool> tournament(repetition);
	tournament.run();

	std::cout << " :: Press Enter to Quit...";
	std::cin.ignore();
	return 0;
}