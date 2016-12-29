// CustomPlayer.hpp
// Derived class in a nutshell. Don't forget to rename CustomPlayer!

#ifndef __CUSTOM_PLAYER_HPP__
#define __CUSTOM_PLAYER_HPP__

#include "Player.hpp"
// Custom header files go here. You can write extra headers to include.
// You most *NOT* declare or initialize any extra global things.

class CustomPlayer final : public Player
{
public:
	// [Optionally Customize] Obtain identifier of opponent.
	CustomPlayer(size_t opponent = -1) : Player(opponent)
		/* Your custom initialization list goes here */
	{
		/* Your code goes here */

		/* Your code ends here */
	}

public:
	// [Must Customize] Fight others!
	virtual Action fight()
	{
		/* Your code goes here */

		// Returns LOAD, BULLET, PLASMA, METAL or THERMAL.
		// You can return load(), bullet(), plasma(), metal(), thermal()
		// which help you keep track of your history and ammo count.

		/* Your code ends here */
	}

	// [Optionally Customize] Notified of opponent action in after turn.
	virtual void perceive(Action action)
	{
		Player::perceive(action);
		/* Your code goes here */

		// You can choose not to inherit this method.
		// Do not delete the Player::perceive below if you choose to inherit.

		/* Your code ends here */
	}

	// [Optionally Customize] Notified of win / loss / draw status.
	virtual void declared(Result result)
	{
		/* Your code goes here */

		// You can choose not to inherit this method

		/* Your code ends here */
	};

private:

	/* Private stuff goes here */

};

#endif // !__CUSTOM_PLAYER_HPP__