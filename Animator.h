#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>

/* This class hnadles sprite animations */
// Purpose :
// Replace Sprite (inherits from it) to handle texture, animation

class Animator: public sf::Sprite
{
	public:
		Animator();
		void animate();

	private:
		float bouh;
		// Where are we in the anim :
		int animFrame;
		int totalFrame;
		sf::Vector2f subRectSize;

		sf::Texture texture;

};


#endif
