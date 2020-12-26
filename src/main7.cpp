////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
/*
SIMPLE RUMBLE !
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Animator.h"
#include "utils.h"
#include "SRConfig.h"

#define SPEED 1000
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

std::string default_texture_path = "media/images/";
std::string default_texture = "blob_stand_move_rev.png";

int main(int argc, char** argv)
{
	int gameState = 0;
	int sprite1_x = 32;
    int sprite1_y = 32;
    int sprite1_w = 32;
    int sprite1_h = 32;
    int sprite1_ox = 0;
    int sprite1_oy = 1;

    bool do_we_play = true;
	srand(time(NULL));

	// ================ Setting textures ================
    std::vector<std::string> texture_list;
    texture_list.push_back(default_texture);
    texture_list.push_back("animation_grid.png");
	sf::Text titleText;
	std::string titleString = "SIMPLE RUMBLE 2 !\n\t\t\t\tv" + std::to_string(Simplerumble_VERSION_MAJOR) + "." +  std::to_string(Simplerumble_VERSION_MINOR);
    /*texture_list.push_back();
    texture_list.push_back();
    texture_list.push_back();
    texture_list.push_back();*/
	// ================ Initialising ! ================
	// Create main window
	// Black screen
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Animation tester");
    App.setFramerateLimit(60);

	sf::Texture animTexture;
    sf::Sprite animatedSprite;
	animatedSprite.setScale(4.0f, 4.0f);
	animatedSprite.setPosition(WINDOW_WIDTH / 2 - 16, WINDOW_HEIGHT / 2 - 16);

    //std::string current_texture = default_texture;
    int current_texture = 0;
    int previous_texture = current_texture;
    //if (!animTexture.loadFromFile("media/images/npc1-full.png"))
    if (!animTexture.loadFromFile(default_texture_path + texture_list.at(current_texture)))
    {
        std::cout << "Error when loading opponent image" << std::endl;
        return EXIT_FAILURE;
    }
	else{ animatedSprite.setTexture(animTexture); }
    
	animatedSprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
    Animator anim1;
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
    anim1.addDescription(AnimRow(32, 32, 4, 0.25));
	int animFrame = 0;

	int menuChoice = 0;
	int maxMenuChoices = 5;
	// 0 : attack ; 1 : defend ; 2 : surrender ; 3 : do nothing ; 4 : quit game
	// ----------------------------------------
	
    // Start game loop
	float cumulativeTime = 0.0;
	float cursorPosX=0.0, cursorPosY=0.0;
	//cursorSprite.setPosition(cursorPosX, cursorPosY);
	sf::Clock clock;
	std::cout << "Loop:" << std::endl;
	while (App.isOpen())
	{
		// Process events
		sf::Event event;
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();
		bool validatedChoice = false;
		int enemyChoice;
        previous_texture = current_texture;

		while (App.pollEvent(event))
		{
			// Event processing
			if(event.type == sf::Event::Closed){ App.close(); }
			if(event.type == sf::Event::KeyPressed)
			{
				// DEBUG :
                if (event.key.code == sf::Keyboard::Escape){ App.close(); }
               
                // Switching on options :
                if (event.key.code == sf::Keyboard::Space){ do_we_play = !do_we_play; anim1.play(do_we_play); }
                //if (event.key.code == sf::Keyboard::B){ anim1.play(do_we_play); }
                if (event.key.code == sf::Keyboard::Down){ anim1.setAnimType(anim1.getAnimType()+1); }
                if (event.key.code == sf::Keyboard::Up){ anim1.setAnimType(anim1.getAnimType()-1); }
                if (event.key.code == sf::Keyboard::N){ current_texture = (current_texture + 1 < texture_list.size() ? current_texture + 1 : current_texture); }
                if (event.key.code == sf::Keyboard::B){ current_texture = (current_texture - 1 > 0 ? current_texture - 1 : 0); }

                std::cout << "Anim type: " << anim1.getAnimType() << std::endl;
			}
		
        }

        if( current_texture != previous_texture )
        { 
            if (!animTexture.loadFromFile(default_texture_path + texture_list.at(current_texture)))
            {
                std::cout << "Error when loading opponent image" << std::endl;
                return EXIT_FAILURE;
            }
            else{ animatedSprite.setTexture(animTexture); }
        }
        // End of pollEvent
        //if(cumulativeTime > 0.25)
        //{
        //    animFrame = (animFrame + 1) % 4;
        //    cumulativeTime = 0.0;
        //}
        //else{ cumulativeTime += elapsedTime.asSeconds(); }
        //sprite1_x = animFrame * sprite1_w;
	    //animatedSprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
		//cursorSprite.setPosition(cursorPosX, cursorPosY);
		sf::Color bgColor = sf::Color::Black;
        bgColor = sf::Color(128, 0, 0);

		App.clear(bgColor);

        anim1.animate(animatedSprite);
		App.draw(animatedSprite);

        /*if( state_select )
        {
            App.draw();
        }*/
		App.display();
        //std::cout << "animframe: " << animFrame << ", " << cumulativeTime << std::endl;
	}

	// Reseting pointers (not useful ?)
	//player = opponent = 0;

	return EXIT_SUCCESS;
}

