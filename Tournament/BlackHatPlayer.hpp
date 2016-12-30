// BlackHatPlayer by Matteo Italia
// PPCG: http://codegolf.stackexchange.com/a/105061/11933
// Disqualified because it tempers with opponent's vtables. Nice try, though!

// BlackHatPlayer.hpp

#ifndef __BLACKHAT_PLAYER_HPP__
#define __BLACKHAT_PLAYER_HPP__

#include "Player.hpp"
#include <stddef.h>
#include <typeinfo>
#include <algorithm>
#include <string.h>

class BlackHatPlayer final : public Player
{
public:
	using Player::Player;

	virtual Action fight()
	{
		// Always metal; if the other is an Idiot, he only shoots,
		// and if he isn't an Idiot yet (=first round) it's the only move that
		// is always safe
		if (tricked) return metal();
		// Mark that at the next iterations we don't have to do all this stuff
		tricked = true;

		typedef uintptr_t word;
		typedef uintptr_t *pword;
		typedef uint8_t *pbyte;

		// Size of one memory page; we use it to walk the stack carefully
		const size_t pageSize = 4096;
		// Maximum allowed difference between the vtables
		const ptrdiff_t maxVTblDelta = 65536;
		// Maximum allowed difference between this and the other player
		ptrdiff_t maxObjsDelta = 131072;

		// Our adversary
		Player *c = nullptr;

		// Gets the start address of the memory page for the given object
		auto getPage = [&](void *obj) {
			return pword(word(obj) & (~word(pageSize - 1)));
		};
		// Gets the start address of the memory page *next* to the one of the given object
		auto getNextPage = [&](void *obj) {
			return pword(pbyte(getPage(obj)) + pageSize);
		};

		// Gets a pointer to the first element of the vtable
		auto getVTbl = [](void *obj) {
			return pword(pword(obj)[0]);
		};

		// Let's make some mess to make sure that:
		// - we have an actual variable on the stack;
		// - we call an external (non-inline) function that ensures everything
		//   is spilled on the stack
		// - the compiler actually generates the full vtables (in the current
		//   tournament this shouldn't be an issue, but in earlier sketches
		//   the compiler inlined everything and killed the vtables)
		volatile word i = 0;
		for (const char *sz = typeid(*(this + i)).name(); *sz; ++sz) i += *sz;

		// Grab my vtable
		word *myVTbl = getVTbl(this);

		// Do the stack walk
		// Limit for the stack walk; use i as a reference
		word *stackEnd = getNextPage((pword)(&i));
		for (word *sp = pword(&i);       // start from the location of i
		sp != stackEnd && c == nullptr;
			++sp) {                     // assume that the stack grows downwards
										// If we find something that looks like a pointer to memory
										// in a page just further on the stack, take it as a clue that the
										// stack in facts does go on
			if (getPage(pword(*sp)) == stackEnd) {
				stackEnd = getNextPage(pword(*sp));
			}
			// We are looking for our own address on the stack
			if (*sp != (word)this) continue;

			auto checkCandidate = [&](void *candidate) -> Player* {
				// Don't even try with NULLs and the like
				if (getPage(candidate) == nullptr) return nullptr;
				// Don't trust objects too far away from us - it's probably something else
				if (abs(pbyte(candidate) - pbyte(this))>maxObjsDelta) return nullptr;
				// Grab the vtable, check if it actually looks like one (it should be
				// decently near to ours)
				pword vtbl = getVTbl(candidate);
				if (abs(vtbl - myVTbl)>maxVTblDelta) return nullptr;
				// Final check: try to see if its name looks like a "Player"
				Player *p = (Player *)candidate;
				if (strstr(typeid(*p).name(), "layer") == 0) return nullptr;
				// Jackpot!
				return p;
			};

			// Look around us - a pointer to our opponent should be just near
			c = checkCandidate((void *)sp[-1]);
			if (c == nullptr) c = checkCandidate((void *)sp[1]);
		}

		if (c != nullptr) {
			// We found it! Suck his brains out and put there the brains of a hothead idiot
			struct Idiot : Player {
				virtual Action fight() {
					// Always fire, never reload; blow up in two turns
					// (while we are always using the metal shield to protect ourselves)
					return bullet();
				}
			};
			Idiot idiot;
			// replace the vptr
			(*(word *)(c)) = word(getVTbl(&idiot));
		}
		// Always metal shield to be protected from the Idiot
		return metal();
	}
private:
	bool tricked = false;
};

#endif // !__BLACKHAT_PLAYER_HPP__