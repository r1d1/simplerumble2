#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>

/* This class hnadles sprite animations */
// Purpose :
// Replace Sprite (inherits from it) to handle texture, animation
// 4 first rows are for movement

class Animator: public sf::Sprite
{
	public:
		Animator();
		void animate();
		void play();
		void pause();

	private:
		float bouh;
		// Where are we in the anim :
		int animFrame;
		int totalFrame;
		bool playing;

		sf::Vector2f subRectSize;
		sf::Texture texture;

};


#endif
