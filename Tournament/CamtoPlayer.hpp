#ifndef __CAMTO_HPP__
#define __CAMTO_HPP__

#include "Player.hpp"
#include <iostream>

class CamtoPlayer final : public Player
{
public:
	CamtoPlayer(size_t opponent = -1) : Player(opponent) {}
	int S = 1; // Switch between options. (like a randomness function without any randomness)
	bool ltb = false; // L.ast T.urn B.locked
	bool loop = false; // If there a loop going on.
	int histarray[10] = { 0,0,0,0,0,0,0,0,0,0 }; // The last ten turns.
	int appears(int number) { // How many times a number appears(); in histarray, used for checking for infinite loops.
		int things = 0; // The amount of times the number appears(); is stored in things.
		for (int count = 0; count < 10; count++) { // For(every item in histarray) {if its the correct number increment thing}.
			if (histarray[count] == number) { things++; }
		}
		return things; // Return the result
	}
	virtual Action fight()
	{
		int ammo = getAmmo(); // Ammo count.
		int bad_ammo = getAmmoOpponent(); // Enemy ammo count.
		int turn = getTurn(); // Turn count.
		int pick = 0; // This turn's weapon.

		if (appears(2) >= 4) { loop = true; } // Simple loop detection
		if (appears(3) >= 4) { loop = true; } // by checking if
		if (appears(4) >= 4) { loop = true; } // any weapong is picked a lot
		if (appears(5) >= 4) { loop = true; } // except for load();

		if (ammo == 0 && bad_ammo == 1) { pick = 4; } // Block when he can shoot me.
		if (ammo == 0 && bad_ammo >= 2) { S++; S % 2 ? (pick = 4) : (pick = 5); } // Block against whatever might come!
		if (ammo == 0 && bad_ammo >= 1 && ltb) { pick = 1; } // If L.ast T.urn B.locked, then reload instead.
		if (ammo == 1 && bad_ammo == 0) { pick = 2; } // Shoot when the opponent can't shoot.
		if (ammo == 1 && bad_ammo == 1) { S++; S % 2 ? (pick = 2) : (pick = 4); } // No risk here.
		if (ammo == 1 && bad_ammo >= 2) { S++; S % 2 ? (pick = 4) : (pick = 5); } // Block!
		if (ammo == 1 && bad_ammo >= 1 && ltb) { pick = 2; } // If ltb shoot instead.
		if (ammo >= 2) { S++; S % 2 ? (pick = 2) : (pick = 3); } // Shoot something!

																 /* debugging
																 cout << "Turn data: turn: ";
																 cout << turn;
																 cout << " loop: ";
																 cout << loop;
																 cout << " ";
																 cout << "ltb: ";
																 cout << ltb;
																 cout << " ";
																 */

																 // Attempt to break out of the loop. (hoping there is one)
		if (ammo == 0 && loop) { pick = 1; } // After many turns of waiting, just load();
		if (ammo == 1 && bad_ammo == 0 && loop) { loop = false; pick = 1; } // Get out of the loop by loading instead of shooting.
		if (ammo == 1 && bad_ammo == 1 && loop) { loop = false; pick = 4; } // Get out of the loop (hopefully) by blocking.
		if (ammo >= 2 && loop) { loop = false; S++; S % 2 ? (pick = 2) : (pick = 3); } // Just shoot.
		if (turn == 3 && (appears(1) == 2) && (appears(2) == 1)) { pick = 4; } // If it's just load();, shoot();, load(); then metal(); because it might be a loop.
																			   // End of loop breaking.

		if (turn == 1) { pick = 2; } // Shoot right after reloading!
		if (ammo == 0 && bad_ammo == 0) { pick = 1; } // Always load when no one can shoot.

		for (int count = 0; count < 10; count++) {
			histarray[count] = histarray[count + 1]; // Shift all values in histarray[] by 1.
		}
		histarray[9] = pick; // Add the picked weapon to end of histarray[].

							 /*  more debugging
							 cout << "history: ";
							 cout << histarray[0];
							 cout << histarray[1];
							 cout << histarray[2];
							 cout << histarray[3];
							 cout << histarray[4];
							 cout << histarray[5];
							 cout << histarray[6];
							 cout << histarray[7];
							 cout << histarray[8];
							 cout << histarray[9];

							 cout << " pick, ammo, bammo: ";
							 cout << pick;
							 cout << " ";
							 cout << ammo;
							 cout << " ";
							 cout << bad_ammo;
							 cout << "\n";
							 */
		switch (pick) {
		case 1:
			ltb = false; return load();
		case 2:
			ltb = false; return bullet();
		case 3:
			ltb = false; return plasma();
		case 4:
			ltb = true; return metal();
		case 5:
			ltb = true; return thermal();
		}

	}
};

#endif // !__CAMTO_HPP__