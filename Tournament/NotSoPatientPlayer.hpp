// NotSoPatientPlayer.hpp

#ifndef __NOT_SO_PATIENT_PLAYER_HPP__
#define __NOT_SO_PATIENT_PLAYER_HPP__

#include "Player.hpp"
#include <iostream>

class NotSoPatientPlayer final : public Player
{
	static const int TOTAL_PLAYERS = 50;
	static const int TOTAL_ACTIONS = 5;
	static const int MAX_TURNS = 100;
public:
	NotSoPatientPlayer(size_t opponent = -1) : Player(opponent)
	{
		this->opponent = opponent;
	}

public:
	virtual Action fight()
	{
		/*Part which is shamelessly copied from MontePlayer.*/
		int turn = getTurn(),
			ammo = getAmmo(),
			opponentAmmo = getAmmoOpponent();
		int turnsRemaining = MAX_TURNS - turn;
		//The bot starts to shoot when there is enough ammo to fire plasma at least (turnsRemaining-2) times.
		//Did you know that you cannot die when you shoot plasma?
		//Also chooses 1 or 2 move(s) in which will shoot bullet(s) or none if there is plenty of ammo.
		//Also check !burstMode because it needs to be done only once.
		if (!burstMode && ammo + 2 >= turnsRemaining * 2)
		{
			burstMode = true;
			if (!(ammo == turnsRemaining * 2)) {
				turnForBullet1 = GetRandomInteger(turnsRemaining - 1) + turn;
				if (ammo + 2 == turnsRemaining * 2) {
					//turnForBullet1 should be excluded in range for turnForBullet2
					turnForBullet2 = GetRandomInteger(turnsRemaining - 2) + turn;
					if (turnForBullet2 >= turnForBullet1) turnForBullet2++;
				}
			}
		}
		if (burstMode) {
			if (turn == turnForBullet1 || turn == turnForBullet2) {
				return bullet();
			}
			else return plasma();
		}

		//if opponent defended last 3 turns, the bot tries to go with something different
		if (turn >= 3) {
			auto historyOpponent = getHistoryOpponent();
			//if opponent used metal last 3 turns
			if (METAL == historyOpponent[turn - 1] && METAL == historyOpponent[turn - 2] && METAL == historyOpponent[turn - 3]) {
				if (ammo >= 2) return plasma();
				else return load();
			}
			//if opponent used thermal last 3 turns
			if (THERMAL == historyOpponent[turn - 1] && THERMAL == historyOpponent[turn - 2] && THERMAL == historyOpponent[turn - 3]) {
				if (ammo >= 1) return bullet();
				else return load();
			}
			//if the opponent defends, but not consistently
			if ((historyOpponent[turn - 1] == METAL || historyOpponent[turn - 1] == THERMAL)
				&& (historyOpponent[turn - 2] == METAL || historyOpponent[turn - 2] == THERMAL)
				&& (historyOpponent[turn - 3] == METAL || historyOpponent[turn - 3] == THERMAL)) {
				if (ammo >= 2) return plasma();
				else if (ammo == 1) return bullet();
				else return load();
			}
		}

		/*else*/ {
			if (opponentAmmo == 0) return load();
			if (opponentAmmo == 1) return metal();
			//if opponent prefers bullets or plasmas, choose the appropriate defence
			if (opponentMoves[opponent][BULLET] * 2 >= opponentMoves[opponent][PLASMA]) return metal();
			else return thermal();
		}
	}

	virtual void perceive(Action action)
	{
		Player::perceive(action);
		opponentMoves[opponent][action]++;
	}

	/*virtual void declared(Result result)
	{
		currentRoundResults[opponent][result]++;
		totalResults[opponent][result]++;
		int duels = 0;
		for (int i = 0; i < 3; i++) duels += currentRoundResults[opponent][i];
		if (duels == 100) {
			std::cout << "Score against P" << opponent << ": " <<
				currentRoundResults[opponent][WIN] << "-" << currentRoundResults[opponent][DRAW] << "-" << currentRoundResults[opponent][LOSS] << "\n";
			for (int i = 0; i < 3; i++) currentRoundResults[opponent][i] = 0;
		}
	};*/

private:
	static long opponentMoves[TOTAL_PLAYERS][TOTAL_ACTIONS];
	int opponent;
	//When it becomes true, the bot starts shooting.
	bool burstMode = false;
	//turnForBullet1 and turnForBullet2,
	//the 2 turns in which the bot will shoot bullets
	int turnForBullet1 = -1, turnForBullet2 = -1;
	//For debugging purposes
	//Reminder: enum Result { DRAW, WIN, LOSS };
	static int currentRoundResults[TOTAL_PLAYERS][3], totalResults[TOTAL_PLAYERS][3];
};
long NotSoPatientPlayer::opponentMoves[TOTAL_PLAYERS][TOTAL_ACTIONS] = { { 0 } };
int NotSoPatientPlayer::currentRoundResults[TOTAL_PLAYERS][3] = { { 0 } };
int NotSoPatientPlayer::totalResults[TOTAL_PLAYERS][3] = { { 0 } };
#endif // !__NOT_SO_PATIENT_PLAYER_HPP__
