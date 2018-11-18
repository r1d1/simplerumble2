#include "Animator.h"

Animator::Animator()
{
    cumulativeTime = 0.0;
    currentFrame = currentRow = 0;
    elapsedTime = timer.getElapsedTime();
    timer.restart();
    //timer.restart();
}

void Animator::animate(sf::Sprite & s)
{
    //std::cout << "a" << std::flush;
    std::cout << "cumtime: " << cumulativeTime << ", " << elapsedTime.asMicroseconds() << ", " << currentFrame << std::endl;
    auto row = description.at(currentRow);
    if(playing)
    {
        //std::cout << " ----- a" << std::endl;
        elapsedTime = timer.getElapsedTime();
		timer.restart();
        if ( cumulativeTime > row.time_per_frame )
        {
            currentFrame = (currentFrame+1) % row.nb_frames;
            cumulativeTime = 0.0;
        }
        else
        {
            cumulativeTime += elapsedTime.asSeconds();
        }
	    //animatedSprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
        view.left = currentFrame * row.width;
        view.top = currentRow * row.height;
        view.width = row.width;
        view.height = row.height;
        //std::cout << "View: " << view.left << ", " << view.top << ", " << view.width << ", " << view.height << " -- " << row.time_per_frame << std::endl;
        s.setTextureRect(view);
    }
    else
    {
        //std::cout << " ----- P" << std::endl;
    }
}

void Animator::play(bool p){ playing = p; }

void Animator::reset(){}
//void Animator::pause(){}
