// MontePlayer by TheNumberOne
// PPCG: http://codegolf.stackexchange.com/a/105175/11933

#ifndef __Monte_PLAYER_HPP__
#define __Monte_PLAYER_HPP__

#include "Player.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <iostream>


class MontePlayer final : public Player
{
	static const int MAX_TURNS = 100;
	static const int TOTAL_ACTIONS = 5;

	//Increase this if number of players goes above 20.
	static const int MAX_PLAYERS = 20;

	//The number of simulated games we run every time our program is called.
	static const int MONTE_ROUNDS = 1000;


	/**
	* Represents the current state of the game.
	*/
	struct Game
	{
		int turn;
		int ammo;
		int opponentAmmo;
		bool alive;
		bool opponentAlive;

		Game(int turn, int ammo, int opponentAmmo, bool alive, bool opponentAlive)
			: turn(turn), ammo(ammo), opponentAmmo(opponentAmmo), alive(alive), opponentAlive(opponentAlive) {}
		Game() : turn(0), ammo(0), opponentAmmo(0), alive(false), opponentAlive(false) {}
	};

	struct Stat
	{
		int wins;
		int attempts;

		Stat() : wins(0), attempts(0) {}
	};

	/**
	* A Monte tree data structure.
	*/
	struct MonteTree
	{
		//The state of the game.
		Game game;

		//myStats[i] returns the statistic for doing the i action in this state.
		Stat myStats[TOTAL_ACTIONS];
		//opponentStats[i] returns the statistic for the opponent doing the i action in this state.
		Stat opponentStats[TOTAL_ACTIONS];
		//Total number of times we've created statistics from this tree.
		int totalPlays = 0;
		//The action that led to this tree.
		int myAction;
		//The opponent action that led to this tree.
		int opponentAction;

		//The tree preceding this one.
		MonteTree *parent = NULL;

		//subtrees[i][j] is the tree that would follow if I did action i and the
		//opponent did action j.
		MonteTree *subtrees[TOTAL_ACTIONS][TOTAL_ACTIONS] = { { NULL } };

		MonteTree(int turn, int ammo, int opponentAmmo) :
			game(turn, ammo, opponentAmmo, true, true) {}


		MonteTree(Game game, MonteTree *parent, int myAction, int opponentAction) :
			game(game), parent(parent), myAction(myAction), opponentAction(opponentAction)
		{
			//Make sure the parent tree keeps track of this tree.
			parent->subtrees[myAction][opponentAction] = this;
		}

		//The destructor so we can avoid slow ptr types and memory leaks.
		~MonteTree()
		{
			//Delete all subtrees.
			for (int i = 0; i < TOTAL_ACTIONS; i++)
			{
				for (int j = 0; j < TOTAL_ACTIONS; j++)
				{
					auto branch = subtrees[i][j];

					if (branch)
					{
						branch->parent = NULL;
						delete branch;
					}
				}
			}
		}
	};

	//The previous state.
	Game prevGame;
	//The id of the opponent.
	int opponent;
	//opponentHistory[a][b][c][d] returns the number of times
	//that opponent a did action d when I had b ammo and he had c ammo.
	static int opponentHistory[MAX_PLAYERS][MAX_TURNS][MAX_TURNS][TOTAL_ACTIONS];

public:
	MontePlayer(size_t opponent = -1) : Player(opponent)
	{
		srand((unsigned)time(NULL));
		this->opponent = (int)opponent;
	}

public:

	virtual Action fight()
	{
		//Create the root tree. Will be auto-destroyed after this function ends.
		MonteTree current(getTurn(), getAmmo(), getAmmoOpponent());

		//Set the previous game to this one.
		prevGame = current.game;

		//Get these variables so we can log later if nessecarry.
		int turn = getTurn(),
			ammo = getAmmo(),
			opponentAmmo = getAmmoOpponent();

		for (int i = 0; i < MONTE_ROUNDS; i++)
		{
			//Go down the tree until we find a leaf we haven't visites yet.
			MonteTree *leaf = selection(&current);

			//Randomly simulate the game at the leaf and get the result.
			int score = simulate(leaf->game);

			//Propagate the scores back up the root.
			update(leaf, score);
		}

		//Get the best move.
		int move = bestMove(current);

		//Move string for debugging purposes.
		char* m;

		//We have to do this so our bots state is updated.
		switch (move)
		{
		case Action::LOAD:
			load();
			m = "load";
			break;
		case Action::BULLET:
			bullet();
			m = "bullet";
			break;
		case Action::PLASMA:
			plasma();
			m = "plasma";
			break;
		case Action::METAL:
			metal();
			m = "metal";
			break;
		case Action::THERMAL:
			thermal();
			m = "thermal";
			break;
		default: //???
			std::cout << move << " ???????\n";
			throw move;
		}

		return (Action)move;
	}

	/**
	* Record what the enemy does so we can predict him.
	*/
	virtual void perceive(Action action)
	{
		Player::perceive(action);
		opponentHistory[opponent][prevGame.ammo][prevGame.opponentAmmo][action]++;
	}
private:

	/**
	* Trickle down root until we have to create a new leaf MonteTree or we hit the end of a game.
	*/
	MonteTree * selection(MonteTree *root)
	{
		while (!atEnd(root->game))
		{
			//First pick the move that my bot will do.

			//The action my bot will do.
			int myAction;
			//The number of actions with the same bestScore.
			int same = 0;
			//The bestScore
			double bestScore = -1;

			for (int i = 0; i < TOTAL_ACTIONS; i++)
			{
				//Ignore invalid or idiot moves.
				if (!isValidMove(root->game, i, true))
				{
					continue;
				}

				//Get the score for doing move i. Uses
				double score = computeScore(*root, i, true);

				//Randomly select one score if multiple actions have the same score.
				//Why this works is boring to explain.
				if (score == bestScore)
				{
					same++;
					if (Random(same) == 0)
					{
						myAction = i;
					}
				}
				//Yay! We found a better action.
				else if (score > bestScore)
				{
					same = 1;
					myAction = i;
					bestScore = score;
				}
			}

			//The action the enemy will do.
			int enemyAction;

			//The number of times the enemy has been in this same situation.
			int totalEnemyEncounters = 0;
			for (int i = 0; i < TOTAL_ACTIONS; i++)
			{
				totalEnemyEncounters += opponentHistory[opponent][root->game.ammo][root->game.opponentAmmo][i];
			}

			//Assume the enemy will choose an action it has chosen before if we've
			//seen it in this situation before. Otherwise we assume that the enemy is ourselves.
			if (totalEnemyEncounters > 0)
			{
				//Randomly select an action that the enemy has done with
				//weighted by the number of times that action has been done.
				int selection = Random(totalEnemyEncounters);
				for (int i = 0; i < TOTAL_ACTIONS; i++)
				{
					selection -= opponentHistory[opponent][root->game.ammo][root->game.opponentAmmo][i];
					if (selection < 0)
					{
						enemyAction = i;
						break;
					}
				}
			}
			else
			{
				//Use the same algorithm to pick the enemies move we use for ourselves.
				same = 0;
				bestScore = -1;
				for (int i = 0; i < TOTAL_ACTIONS; i++)
				{
					if (!isValidMove(root->game, i, false))
					{
						continue;
					}

					double score = computeScore(*root, i, false);
					if (score == bestScore)
					{
						same++;
						if (Random(same) == 0)
						{
							enemyAction = i;
						}
					}
					else if (score > bestScore)
					{
						same = 1;
						enemyAction = i;
						bestScore = score;
					}
				}
			}

			//If this combination of actions hasn't been explored yet, create a new subtree to explore.
			if (!(*root).subtrees[myAction][enemyAction])
			{
				return expand(root, myAction, enemyAction);
			}

			//Do these actions and explore the next subtree.
			root = (*root).subtrees[myAction][enemyAction];
		}
		return root;
	}

	/**
	* Creates a new leaf under root for the actions.
	*/
	MonteTree * expand(MonteTree *root, int myAction, int enemyAction)
	{
		return new MonteTree(
			doTurn(root->game, myAction, enemyAction),
			root,
			myAction,
			enemyAction);
	}

	/**
	* Computes the score of the given move in the given position.
	* Uses the UCB1 algorithm and returns infinity for moves not tried yet.
	*/
	double computeScore(const MonteTree &root, int move, bool me)
	{
		const Stat &stat = me ? root.myStats[move] : root.opponentStats[move];
		return stat.attempts == 0 ?
			HUGE_VAL :
			double(stat.wins) / stat.attempts + sqrt(2 * log(root.totalPlays) / stat.attempts);
	}

	/**
	* Randomly simulates the given game.
	* Has me do random moves that are not stupid.
	* Has opponent do what it has done in similar positions or random moves if not
	* observed in those positions yet.
	*
	* Returns 1 for win. 0 for loss. -1 for draw.
	*/
	int simulate(Game game)
	{
		while (!atEnd(game))
		{
			game = doRandomTurn(game);
		}

		if (game.alive > game.opponentAlive)
		{
			return 1;
		}
		else if (game.opponentAlive > game.alive)
		{
			return 0;
		}
		else //Draw
		{
			return -1;
		}
	}

	/**
	* Returns whether the game is over or not.
	*/
	bool atEnd(Game game)
	{
		return !game.alive || !game.opponentAlive || game.turn > MAX_TURNS;
	}

	/**
	* Simulates the given actions on the game.
	*/
	Game doTurn(Game game, int myAction, int enemyAction)
	{
		game.turn++;

		switch (myAction)
		{
		case Action::LOAD:
			game.ammo++;
			break;
		case Action::BULLET:
			if (game.ammo < 1)
			{
				game.alive = false;
				break;
			}
			game.ammo--;
			if (enemyAction == Action::LOAD || enemyAction == Action::THERMAL)
			{
				game.opponentAlive = false;
			}
			break;
		case Action::PLASMA:
			if (game.ammo < 2)
			{
				game.alive = false;
				break;
			}
			game.ammo -= 2;
			if (enemyAction != Action::PLASMA && enemyAction != Action::THERMAL)
			{
				game.opponentAlive = false;
			}
			break;
		}

		switch (enemyAction)
		{
		case Action::LOAD:
			game.opponentAmmo++;
			break;
		case Action::BULLET:
			if (game.opponentAmmo < 1)
			{
				game.opponentAlive = false;
				break;
			}
			game.opponentAmmo--;
			if (myAction == Action::LOAD || myAction == Action::THERMAL)
			{
				game.alive = false;
			}
			break;
		case Action::PLASMA:
			if (game.opponentAmmo < 2)
			{
				game.opponentAlive = false;
			}
			game.opponentAmmo -= 2;
			if (myAction != Action::PLASMA && myAction != Action::THERMAL)
			{
				game.alive = false;
			}
			break;
		}

		return game;
	}

	/**
	* Chooses a random move for me and my opponent and does it.
	*/
	Game doRandomTurn(Game &game)
	{
		//Select my random move.
		int myAction;
		int validMoves = 0;

		for (int i = 0; i < TOTAL_ACTIONS; i++)
		{
			//Don't do idiotic moves.
			//Select one at random.
			if (isValidMove(game, i, true))
			{
				validMoves++;
				if (Random(validMoves) == 0)
				{
					myAction = i;
				}
			}
		}

		//Choose random opponent action.
		int opponentAction;

		//Whether the enemy has encountered this situation before
		bool enemyEncountered = false;

		validMoves = 0;

		//Weird algorithm that works and I don't want to explain.
		//What it does:
		//If the enemy has encountered this position before,
		//then it chooses a random action weighted by how often it did that action.
		//If they haven't, makes the enemy choose a random not idiot move.
		for (int i = 0; i < TOTAL_ACTIONS; i++)
		{
			int weight = opponentHistory[opponent][game.ammo][game.opponentAmmo][i];
			if (weight > 0)
			{
				if (!enemyEncountered)
				{
					enemyEncountered = true;
					validMoves = 0;
				}
				validMoves += weight;
				if (Random(validMoves) < weight)
				{
					opponentAction = i;
				}
			}
			else if (!enemyEncountered && isValidMove(game, i, false))
			{
				validMoves++;
				if (Random(validMoves) == 0)
				{
					opponentAction = i;
				}
			}
		}

		return doTurn(game, myAction, opponentAction);
	}

	/**
	* Returns whether the given move is valid/not idiotic for the game.
	*/
	bool isValidMove(Game game, int move, bool me)
	{
		switch (move)
		{
		case Action::LOAD:
			return true;
		case Action::BULLET:
			return me ? game.ammo > 0 : game.opponentAmmo > 0;
		case Action::PLASMA:
			return me ? game.ammo > 1 : game.opponentAmmo > 1;
		case Action::METAL:
			return me ? game.opponentAmmo > 0 : game.ammo > 0;
		case Action::THERMAL:
			return me ? game.opponentAmmo > 1 : game.ammo > 1;
		default:
			return false;
		}
	}

	/**
	* Propagates the score up the MonteTree from the leaf.
	*/
	void update(MonteTree *leaf, int score)
	{
		while (true)
		{
			MonteTree *parent = leaf->parent;
			if (parent)
			{
				//-1 = draw, 1 = win for me, 0 = win for opponent
				if (score != -1)
				{
					parent->myStats[leaf->myAction].wins += score;
					parent->opponentStats[leaf->opponentAction].wins += 1 - score;
				}
				parent->myStats[leaf->myAction].attempts++;
				parent->opponentStats[leaf->opponentAction].attempts++;
				parent->totalPlays++;
				leaf = parent;
			}
			else
			{
				break;
			}
		}
	}

	/**
	* There are three different strategies in here.
	* The first is not random, the second more, the third most.
	*/
	int bestMove(const MonteTree &root)
	{
		//Select the move with the highest win rate.
		int best;
		double bestScore = -1;
		for (int i = 0; i < TOTAL_ACTIONS; i++)
		{
			if (root.myStats[i].attempts == 0)
			{
				continue;
			}

			double score = double(root.myStats[i].wins) / root.myStats[i].attempts;
			if (score > bestScore)
			{
				bestScore = score;
				best = i;
			}
		}

		return best;

		////Select a move weighted by the number of times it has won the game.
		//int totalScore = 0;
		//for (int i = 0; i < TOTAL_ACTIONS; i++)
		//{
		//  totalScore += root.myStats[i].wins;
		//}
		//int selection = Random(totalScore);
		//for (int i = 0; i < TOTAL_ACTIONS; i++)
		//{
		//  selection -= root.myStats[i].wins;
		//  if (selection < 0)
		//  {
		//      return i;
		//  }
		//}

		////Select a random move weighted by win ratio.
		//double totalScore = 0;
		//for (int i = 0; i < TOTAL_ACTIONS; i++)
		//{
		//  if (root.myStats[i].attempts == 0)
		//  {
		//      continue;
		//  }
		//  totalScore += double(root.myStats[i].wins) / root.myStats[i].attempts;
		//}
		//double selection = Random(totalScore);
		//for (int i = 0; i < TOTAL_ACTIONS; i++)
		//{
		//  if (root.myStats[i].attempts == 0)
		//  {
		//      continue;
		//  }
		//  selection -= double(root.myStats[i].wins) / root.myStats[i].attempts;
		//  if (selection < 0)
		//  {
		//      return i;
		//  }
		//}
	}

	//My own random functions.
	int Random(int max)
	{
		return rand() % max;
	}
	double Random(double max)
	{
		return double(rand()) / (RAND_MAX + 1) * max;
	}
};
//We have to initialize this here for some reason.
int MontePlayer::opponentHistory[MAX_PLAYERS][MAX_TURNS][MAX_TURNS][TOTAL_ACTIONS]{ { { { 0 } } } };

#endif // !__Monte_PLAYER_HPP__