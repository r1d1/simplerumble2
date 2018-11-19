#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

/* This class hnadles sprite animations */
// Purpose :
// Replace Sprite (inherits from it) to handle texture, animation
// 4 first rows are for movement

//class describing one anim row
class AnimRow
{
    public:
        int width;
        int height;
        int nb_frames;
        float time_per_frame;
        AnimRow(int w=16, int h=16, int n=2, float t=0.25) : width(w), height(h), nb_frames(n), time_per_frame(t){}
    };

class Animator: public sf::Sprite
{
	public:
		Animator();
		void animate(sf::Sprite & s);
		void play(bool s);
		//void pause();
        void reset();
        void setAnimType(int t);
        int getAnimType(){ return currentRow; }

        void addDescription(AnimRow ar){ description.push_back(ar); }


	private:
        std::vector<AnimRow> description;
        sf::Clock timer;
        sf::Time elapsedTime;
	    float cumulativeTime = 0.0;
        sf::IntRect view;
        int currentRow;
        int currentFrame;
		//float bouh;
		// Where are we in the anim :
		//int animFrame;
		//int totalFrame;
		bool playing;

		sf::Vector2f subRectSize;
		sf::Texture texture;

};


#endif
