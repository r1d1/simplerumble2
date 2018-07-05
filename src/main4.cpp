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

#include "Entity.h"
#include "utils.h"
#include "SRConfig.h"
#include "Inventory.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char** argv)
{
	int gameState = 0;
	
	srand(time(NULL));
	// ================ Initialising ! ================
	// Create main window
	// Black screen
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SIMPLE RUMBLE !!!");
    App.setFramerateLimit(60);
	sf::Texture cursorTexture;

    sf::Sprite cursorSprite;
	//if (!cursorTexture.loadFromFile("media/images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	if (!cursorTexture.loadFromFile("media/images/npc2-full.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	else{ cursorSprite.setTexture(cursorTexture); }

    std::vector<Entity> entityList;

    for(int i = 0 ; i < 5 ; i++)
    {
        Entity e = Entity("entity"+std::to_string(i), &cursorTexture);
        float x = rand() % (WINDOW_WIDTH-50);
        float y = rand() % (WINDOW_HEIGHT-50);
        std::cout << x << ", " << y << std::endl;
        e.move(x, y);
        entityList.push_back(e);
    }
	cursorSprite.setScale(0.2f, 0.2f);
    int redval = 0;	
	// Start game loop
	float cumulativeTime = 0.0;
	float cursorPosX=0.0, cursorPosY=0.0;

    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, sf::Vector2f(0, 0));
    convex.setPoint(1, sf::Vector2f(150, 10));
    convex.setPoint(2, sf::Vector2f(120, 90));
    convex.setPoint(3, sf::Vector2f(30, 100));
    convex.setPoint(4, sf::Vector2f(0, 50));

	//cursorSprite.setPosition(cursorPosX, cursorPosY);
	sf::Clock clock;
	std::cout << "Loop:" << std::endl;
	while (App.isOpen())
	{
		// Process events
		sf::Event event;
		sf::Time elapsedTime = clock.getElapsedTime();
        float duration = elapsedTime.asSeconds();
		clock.restart();
		bool validatedChoice = false;
		int enemyChoice;
		cumulativeTime += elapsedTime.asSeconds(); 
        //std::cout << "Cum time: \033[32m"<< cumulativeTime << ", " << duration << "\033[39m" << std::endl;
        
        // Unit Factory:
        // Factory(bool activated);
        // Entity factory = Factory(false);
        // Unit lists
        // Entity 
        float dx = 0.0;
        float dy = 0.0;

		while (App.pollEvent(event))
		{
			// Event processing
			if(event.type == sf::Event::Closed){ App.close(); }
			if(event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape){ App.close(); }
                if (event.key.code == sf::Keyboard::Up){ dy = -5; }
                if (event.key.code == sf::Keyboard::Down){ dy = 5; }
                if (event.key.code == sf::Keyboard::Left){ dx = -5; }
                if (event.key.code == sf::Keyboard::Right){ dx = 5; }
				
            }
        }
        
        sf::Color bgColor = sf::Color(128, 0, 0);
		App.clear(bgColor);

        for(std::vector<Entity>::iterator e = entityList.begin() ; e != entityList.end() ; e++)
        {
            //e.animate(cumulativeTime);
            e->move(dx, dy);
        }

        App.draw(convex);
        for(auto e : entityList)
        {
            e.render(&App);
        }
		App.display();
    }
    return EXIT_SUCCESS;
}
