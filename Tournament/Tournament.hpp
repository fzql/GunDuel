// Tournament.hpp
// Pitches Players against each other in a last-player-out gun duel tournament.

#ifndef __TOURNAMENT_HPP__
#define __TOURNAMENT_HPP__

#include <vector>
#include <tuple>
#include <algorithm>

// Class responsible for a tournament.
template <class ... Players>
class Tournament final
{
public:
	// Scorecard for a player.
	struct ScoreCard
	{
		// Is player still alive?
		bool alive;
		// How many rounds has the player survived?
		size_t survival;
		// Points in current round;
		size_t points;
		// How many points has the player gained in each round?
		std::vector<int> history;
	};

public:
	// Initializes a tournament.
	Tournament(size_t repetition = 100)
		: mSize(sizeof...(Players)), mRepetition(repetition), mScores(mSize)
	{

	}

public:
	// Run the tournament!
	void run()
	{

	}

private:

	// Fight once.
	void fightOnce()
	{

	}

	// Declare the start of a round.
	void startRound()
	{

	}

	// Declare the end of a round.
	void endRound()
	{
		// Get the minimum score.
		std::vector<int> points(mSize);
		std::transform(mScores.cbegin(), mScores.cend(), points.cbegin(), [](ScoreCard const &s) -> {
			return s.alive ? s.points : -1;
		});

		// Add scores to history.
		std::for_each(mScores.begin(), mScores.end(), [](ScoreCard &s) -> {
			s.history.push_back(points);
		});

		// Clear the scoreboard.
		points.assign(mSize, 0);
	}

private:
	// Get the number of remaining players
	size_t getPlayerRemaining() const
	{
		return std::count_if(mScores.cbegin(), mScores.cend(), [](ScoreCard const &s) -> {
			return s.alive;
		});
	}

private:
	// Number of participants.
	const size_t mSize;

	// Number of duel between every two players in each round of tournament.
	size_t mRepetition;

	// Each element holds a player.
	std::tuple<Players> mPlayers;

	// Keeps track of the scoreboard.
	std::vector<ScoreCard> mScores;
};

#endif // ! __TOURNAMENT_HPP__