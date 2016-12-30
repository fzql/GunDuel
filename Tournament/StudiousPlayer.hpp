// StudiousPlayer by H Walters
// PPCG: http://codegolf.stackexchange.com/a/105066/11933

#ifndef __STUDIOUS_PLAYER_H__
#define __STUDIOUS_PLAYER_H__

#include "Player.hpp"
#include <unordered_map>

struct StudiousPlayer : Player
{
	using Player::GetRandomInteger;
	// Represents an opponent's action for a specific state.
	struct OpponentAction {
		OpponentAction() {}
		unsigned l = 0;
		unsigned b = 0;
		unsigned p = 0;
		unsigned m = 0;
		unsigned t = 0;
	};
	// StudiousPlayer models every opponent that it plays,
	// and factors said model into its decisions.
	//
	// There are 16 states, corresponding to
	// 4 inner states (0,1,2,3) and 4 outer states
	// (0,1,2,3). The inner states represent our
	// (SP's) ammo; the outer represents the
	// Opponent's ammo.  For the inner or outer
	// states, 0-2 represent the exact ammo; and
	// 3 represents "3 or more".
	//
	// State n is (4*outer)+inner.
	//
	// State 0 itself is ignored, since we don't care
	// what action the opponent takes (we always load);
	// thus, it's not represented here.
	//
	// os stores states 1 through 15 (index 0 through 14).
	struct Opponent {
		std::vector<OpponentAction> os;
		Opponent() : os(15) {}
	};
	StudiousPlayer(size_t opponent)
		: Player(opponent)
		, strat(storedLs()[opponent])
		, ammoOpponent()
	{
	}
	Player::Action fight() {
		// Compute the current "ammo state".
		// For convenience here (aka, readability in switch),
		// this is a two digit octal number.  The lso is the
		// inner state, and the mso the outer state.
		unsigned ss, os;
		switch (ammoOpponent) {
		default: os = 030; break;
		case 2: os = 020; break;
		case 1: os = 010; break;
		case 0: os = 000; break;
		}
		switch (getAmmo()) {
		default: ss = 003; break;
		case 2: ss = 002; break;
		case 1: ss = 001; break;
		case 0: ss = 000; break;
		}
		// Store the ammo state.  This has a side effect
		// of causing actn() to return an OpponentAction
		// struct, with the opponent's history during this
		// state.
		osa = os + ss;
		// Get the opponent action pointer
		const OpponentAction* a = actn(osa);
		// If there's no such action structure, assume
		// we're just supposed to load.
		if (!a) return load();
		// Apply ammo-state based strategies:
		switch (osa) {
		case 001:
			// If opponent's likely to load, shoot; else load
			if (a->l > a->m) return bullet();
			return load();
		case 002:
		case 003:
			// Shoot in the way most likely to kill (or randomly)
			if (a->t > a->m + a->l) return bullet();
			if (a->m > a->t + a->l) return plasma();
			if (GetRandomInteger(1)) return bullet();
			return plasma();
		case 010:
			// If opponent tends to load, load; else shoot
			if (a->l > a->b) return load();
			return metal();
		case 011:
			// Shoot if opponent tends to load
			if (a->l > a->b + a->m) return bullet();
			// Defend if opponent tends to shoot
			if (a->b > a->l + a->m) return metal();
			// Load if opponent tends to defend
			if (a->m > a->b + a->l) return load();
			// Otherwise randomly respond
			if (!GetRandomInteger(2)) return metal();
			if (!GetRandomInteger(1)) return load();
			return bullet();
		case 012:
		case 013:
			// If opponent most often shoots, defend
			if (a->b > a->l + a->m + a->t) return metal();
			// If opponent most often thermals, use bullet
			if (a->t > a->m) return bullet();
			// If opponent most often metals, use plasma
			if (a->m > a->t) return plasma();
			// Otherwise use a random weapon
			return (GetRandomInteger(1)) ? bullet() : plasma();
		case 020:
			// If opponent most often loads or defends, load
			if (a->l + a->m + a->t > a->b + a->p) return load();
			// If opponent most often shoots bullets, raise metal
			if (a->b > a->p) return metal();
			// If opponent most often shoots plasma, raise thermal
			if (a->p > a->b) return thermal();
			// Otherwise raise random defense
			return (GetRandomInteger(1)) ? metal() : thermal();
		case 021:
		case 031:
			// If opponent loads more often than not,
			if (a->l > a->m + a->b + a->p) {
				// Tend to shoot (67%), but possibly load (33%)
				return (GetRandomInteger(2)) ? bullet() : load();
			}
			// If opponent metals more often than loads or shoots, load
			if (a->m > a->l + a->b + a->p) return load();
			// If opponent thermals (shrug) more often than loads or shoots, load
			if (a->t > a->l + a->b + a->p) return load();
			// If opponent tends to shoot bullets, raise metal
			if (a->b > a->p) return metal();
			// If opponent tends to shoot plasma, raise thermal
			if (a->p > a->b) return thermal();
			// Raise random shield
			return (GetRandomInteger(2)) ? metal() : thermal();
		case 022:
			// If opponent loads or thermals more often than not, shoot bullet
			if (a->l + a->t > a->b + a->p + a->m) return bullet();
			// If opponent loads or metals more often than not, shoot plasma
			if (a->l + a->m > a->b + a->p + a->t) return plasma();
			// If opponent shoots more than loads or defends, defend
			if (a->b + a->p > a->l + a->m + a->t) {
				if (a->b > a->p) return metal();
				if (a->p > a->b) return thermal();
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			// If opponent defends more than opponent shoots, load
			if (a->m + a->t > a->b + a->p) return load();
			// Use random substrategy;
			// load(33%)
			if (GetRandomInteger(2)) return load();
			// defend(33%)
			if (GetRandomInteger(1)) {
				if (a->b > a->p) return metal();
				if (a->b > a->b) return thermal();
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			// Shoot in a way that most often kills (or randomly)
			if (a->m > a->t) return plasma();
			if (a->t > a->m) return bullet();
			return (GetRandomInteger(1)) ? bullet() : plasma();
		case 023:
			// If opponent loads or raises thermal more often than not, shoot bullets
			if (a->l + a->t > a->b + a->p + a->m) return bullet();
			// If opponent loads or raises metal more often than not, shoot plasma
			if (a->l + a->m > a->b + a->p + a->t) return plasma();
			// If opponent shoots more than loads or defends, defend
			if (a->b + a->p > a->l + a->m + a->t) {
				if (a->b > a->p) return metal();
				if (a->p > a->b) return thermal();
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			// If opponent defends more than shoots, shoot
			if (a->m + a->t > a->b + a->p) {
				if (a->m > a->t) return plasma();
				if (a->t > a->m) return bullet();
				return GetRandomInteger(1) ? bullet() : plasma();
			}
			// 50% defend
			if (GetRandomInteger(1)) {
				if (a->b > a->p) return metal();
				return thermal();
			}
			// 50% shoot
			if (a->m > a->t) return plasma();
			if (a->t > a->m) return bullet();
			return (GetRandomInteger(1)) ? bullet() : plasma();
		case 030:
			// If opponent loads or shields more often than not, load
			if (a->l + a->m + a->t > a->b + a->p) return load();
			// If opponent tends to shoot, defend
			if (a->b + a->p >= a->l + a->m + a->t) {
				if (a->b > a->p) return metal();
				if (a->p > a->b) return thermal();
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			// Otherwise, randomly shield (50%) or load
			if (GetRandomInteger(1)) {
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			return load();
		case 032:
			// If opponent loads or thermals more often than not, shoot bullets
			if (a->l + a->t > a->b + a->p + a->m) return bullet();
			// If opponent loads or metals more often than not, shoot plasma
			if (a->l + a->m > a->b + a->p + a->t) return plasma();
			// If opponent shoots more often than loads or shields, defend
			if (a->b + a->p > a->l + a->m + a->t) {
				if (a->b > a->p) return metal();
				if (a->p > a->b) return thermal();
				return (GetRandomInteger(1)) ? metal() : thermal();
			}
			// If opponent shields more often than shoots, load
			if (a->m + a->t > a->b + a->p) return load();
			// Otherwise use random strategy
			if (GetRandomInteger(2)) return load();
			if (GetRandomInteger(1)) {
				if (a->b > a->p) return metal();
				return thermal();
			}
			if (a->m > a->t) return plasma();
			if (a->t > a->m) return bullet();
			return (GetRandomInteger(1)) ? bullet() : plasma();
		case 033:
		{
			// At full 3 on 3, apply random strategy
			// weighted by opponent's histogram of this state...
			// (the extra 1 weights towards plasma)
			unsigned sr =
				GetRandomInteger
				(a->l + a->t + a->p + a->b + a->m + 1);
			// Shoot bullets proportional to how much
			// opponent loads or defends using thermal
			if (sr < a->l + a->t) return bullet();
			sr -= (a->l + a->t);
			// Defend with thermal proportional to how
			// much opponent attacks with plasma (tending to
			// waste his ammo)
			if (sr < a->p) return thermal();
			// Shoot plasma proportional to how
			// much opponent shoots bullets or raises metal
			return plasma();
		}
		}
		// Should never hit this; but rather than ruin everyone's fun,
		// if we do, we just load
		return load();
	}
	// Complete override; we use our opponent's model, not history.
	void perceive(Player::Action action) {
		// We want the ammo but not the history; since
		// the framework (Player::perceive) is "all or nothing", 
		// StudiousPlayer just tracks the ammo itself
		switch (action) {
		default: break;
		case Player::LOAD:   ++ammoOpponent; break;
		case Player::BULLET: --ammoOpponent; break;
		case Player::PLASMA: ammoOpponent -= 2; break;
		}
		// Now we get the opponent's action based
		// on the last (incoming) ammo state
		OpponentAction* a = actn(osa);
		// ...if it's null just bail
		if (!a) return;
		// Otherwise, count the action
		switch (action) {
		case Player::LOAD: ++a->l; break;
		case Player::BULLET: ++a->b; break;
		case Player::PLASMA: ++a->p; break;
		case Player::METAL: ++a->m; break;
		case Player::THERMAL: ++a->t; break;
		}
	}
private:
	Opponent& strat;
	OpponentAction* actn(unsigned octalOsa) {
		unsigned ndx = (octalOsa % 4) + 4 * (octalOsa / 8);
		if (ndx == 0) return 0;
		--ndx;
		if (ndx<15) return &strat.os[ndx];
		return 0;
	}
	unsigned osa;
	unsigned ammoOpponent;
	// Welcome, non-C++ persons, to the "Meyers style singleton".
	// "theMap" is initialized the first time it's executed.
	static std::unordered_map<size_t, Opponent>& storedLs() {
		static std::unordered_map<size_t, Opponent> theMap;
		return theMap;
	}
};

#endif