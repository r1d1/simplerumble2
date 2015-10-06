#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "utils.h"
#include "Animator.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

int main(int argc, char** argv)
{
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Animation test");
	//sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Animation test", sf::Style::Fullscreen);
	//sf::Style::Fullscreen
	std::cout << "Bouh" << std::endl;
	
	sf::Texture character1Texture;
	sf::Sprite character1Sprite;
	sf::Sprite character2Sprite;
	sf::Sprite character3Sprite;
	sf::Sprite character4Sprite;
	if (!character1Texture.loadFromFile("images/npc1-full.png")){ std::cout << "Error when loading opponent image" << std::endl; return EXIT_FAILURE; }
	//if (!character1Texture.loadFromFile("images/movement-grid.png")){ std::cout << "Error when loading opponent image" << std::endl; return EXIT_FAILURE; }
	//if (!character1Texture.loadFromFile("images/basic-sheet.png")){ std::cout << "Error when loading opponent image" << std::endl; return EXIT_FAILURE; }
	else
	{
		character1Sprite.setTexture(character1Texture);
		character2Sprite.setTexture(character1Texture);
		character3Sprite.setTexture(character1Texture);
		character4Sprite.setTexture(character1Texture);
	}
	int animFrameX = 0;
	int animFrameY = 0;
	int spriteRows = 4;
	int spriteCols = 4;
	int animPos = 0;
 	float radius = 64.0;
 	float offsetX = 128.0;
 	float offsetY = 128.0;
 	int angleNb = 360.0;
	
//	character1Sprite.setTextureRect(sf::IntRect(32, 96, 32, 48));
//	std::cout << "Texture sprite : " << (character1Sprite.getTexture())->getSize().x << " " <<  (character1Sprite.getTexture())->getSize().y << std::endl;
	//character1Sprite.setTextureRect(sf::IntRect(0, animFrameY*48, 128, 48));
	character1Sprite.setScale(2.0f, 2.0f);
	character1Sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
	character1Sprite.setPosition(256, 128);
	
	character2Sprite.setScale(2.0f, 2.0f);
	character2Sprite.setTextureRect(sf::IntRect(0, 48, 32, 48));
	character2Sprite.setPosition(128, 128);
	
	character3Sprite.setScale(2.0f, 2.0f);
	character3Sprite.setTextureRect(sf::IntRect(0, 96, 32, 48));
	character3Sprite.setPosition(128, 256);
	
	character4Sprite.setScale(2.0f, 2.0f);
	character4Sprite.setTextureRect(sf::IntRect(0, 144, 32, 48));
	character4Sprite.setPosition(256, 256);
	//character1Sprite.setPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
	//if (sf::Joystick::isConnected(0))
	//{
	//	std::cout << "Joystick 0 connected!" << std::endl;
	//}
	//else{ std::cout << "No joystick detected!" << std::endl; }
//	while ( !sf::Joystick::isConnected(0) )
//	{
//		std::cout << "No Joystick connected!" << std::endl;
//		sf::Joystick::update();
//	}
	// check how many buttons joystick number 0 has
//	unsigned int buttonCount = sf::Joystick::getButtonCount(0);

	// check if joystick number 0 has a Z axis
//	bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);
//	std::cout << "Joy prop : " << buttonCount << " " << hasZ << std::endl;


//	sf::Texture character2Texture;
//	sf::Sprite character2Sprite;
//	if (!character2Texture.loadFromFile("images/npc2-full.png")){ std::cout << "Error when loading player image" << std::endl; return EXIT_FAILURE; }
//	else{ character2Sprite.setTexture(character2Texture); }
	
//	character2Sprite.setTextureRect(sf::IntRect(32, 48, 32, 48));
//	character2Sprite.setScale(2.0f, 2.0f);
//	character2Sprite.setPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);

	sf::Clock clock;
	sf::Time elapsedTime = clock.getElapsedTime();
	clock.restart();
	float cumulativeTime = 0.0;
	float cumulativeTime2 = 0.0;
	
	while (App.isOpen())
	{
		// Process events
		sf::Event event;
		bool validatedChoice = false;
		int enemyChoice;

		while (App.pollEvent(event))
		{
			// Event processing
			if(event.type == sf::Event::Closed){ App.close(); }
			if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape){ App.close(); }
		//		if (event.key.code == sf::Keyboard::Down){ animFrameY = (animFrameY+1) % spriteRows; }

			//	if (event.key.code == sf::Keyboard::Up){ animFrameY = (animFrameY ? animFrameY-1 : spriteRows-1); }
			//	if (event.key.code == sf::Keyboard::Down){ animFrameY = (animFrameY+1) % spriteRows; }
			//	if (event.key.code == sf::Keyboard::Left){ animFrameX = (animFrameX ? animFrameX-1 : spriteCols-1); }
			//	if (event.key.code == sf::Keyboard::Right){ animFrameX = (animFrameX+1) % spriteCols; }
				
				//if (event.key.code == sf::Keyboard::Up){ animFrameY = (animFrameY-1) % spriteRows; }
				//if (event.key.code == sf::Keyboard::Down){ animFrameY = (animFrameY+1) % spriteRows; }
				//if (event.key.code == sf::Keyboard::Left){ animFrameX = (animFrameX-1) % spriteCols; }
				//if (event.key.code == sf::Keyboard::Right){ animFrameX = (animFrameX+1) % spriteCols; }
			}
			// is button 1 of joystick number 0 pressed?
	//		for(int i=0 ; i < buttonCount ; i++)
	//		{
	//			if (sf::Joystick::isButtonPressed(0, i))
	//			{
	//				// yes: shoot!
	//				std::cout << "Button " << i << std::endl;
	//				//gun.fire();
	//			}
	//		}
	//		// what's the current position of the X and Y axes of joystick number 0?
	//		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	//		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	//		std::cout << "Position : " << x << ", " << y << std::endl;
	//		//character.move(x, y);

		}

		elapsedTime = clock.getElapsedTime();
		cumulativeTime += elapsedTime.asSeconds();
		cumulativeTime2 += elapsedTime.asSeconds();
		clock.restart();
	//	std::cout << "Cumtime: " << cumulativeTime << std::endl;
//		if (cumulativeTime > 0.25){ animPos = (animPos+1) % angleNb; } 
		if(cumulativeTime > 0.2){ animFrameX = (animFrameX+1) % spriteCols; cumulativeTime = 0.0; }
		if(cumulativeTime2 > 0.01){ animPos = (animPos+1) % (angleNb); cumulativeTime2 = 0.0; }
		//if( elapsedTime.asSeconds() ){animPos = (animPos+1) % (30*angleNb);
		
	//	character1Sprite.setTextureRect(sf::IntRect(animFrameX*32, animFrameY*48, 32, 48));
	//	character1Sprite.setTextureRect(sf::IntRect(0, animFrameY*48, 128, 48));
		character1Sprite.setTextureRect(sf::IntRect(animFrameX*32, 0, 32, 48));
		character2Sprite.setTextureRect(sf::IntRect(animFrameX*32, 48, 32, 48));
		character3Sprite.setTextureRect(sf::IntRect(animFrameX*32, 96, 32, 48));
		character4Sprite.setTextureRect(sf::IntRect(animFrameX*32, 144, 32, 48));
//		float x = sin(3.14159265/180.0*animPos);
//		float y = cos(3.14159265/180.0*animPos);
		float x = radius * sin(3.14159265/180.0*animPos);
		float y = radius * cos(3.14159265/180.0*animPos);
		//float x = offsetX + radius * sin(3.14159265/180.0*animPos);
		//float y = offsetY + radius * cos(3.14159265/180.0*animPos);
//		std::cout << "Pos: " << x << " " << y << " " << animPos << " " << animPos * 360.0 / angleNb << std::endl;
		character1Sprite.setPosition(256+x, 128+y);
		character2Sprite.setPosition(128+x, 128+y);
		character3Sprite.setPosition(128+x, 256+y);
		character4Sprite.setPosition(256+x, 256+y);
//		std::cout << "AnimFrame: " << animFrameX << " " << animFrameY << " et: " << elapsedTime.asSeconds() << std::endl; 
		//std::cout << "AnimFrame: " << animFrameX << " " << animFrameY << " " << event.key.code << std::endl; 
		App.clear();
		App.draw(character1Sprite);
		App.draw(character2Sprite);
		App.draw(character3Sprite);
		App.draw(character4Sprite);
		App.display();
	}

	return EXIT_SUCCESS;
}
