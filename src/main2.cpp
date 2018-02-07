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

#include "Agent.h"
#include "Entity.h"
#include "Map.h"
#include "Attack.h"
#include "utils.h"
#include "SRConfig.h"

#define SPEED 1000
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
	sf::Texture npcTexture;

    Map testMap(128,64);
    testMap.initRandMap();

	if (!npcTexture.loadFromFile("media/images/npc1-full.png")){ std::cout << "Error when loading npc image" << std::endl; return EXIT_FAILURE; }
    sf::Sprite cursorSprite;
	if (!cursorTexture.loadFromFile("media/images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	else{ cursorSprite.setTexture(cursorTexture); }

    std::vector<Entity> entityList;
    for(int i = 0 ; i < 5 ; i++)
    {
        Entity e = Entity("entity"+std::to_string(i), &npcTexture);
        float x = 250 + rand() % (WINDOW_WIDTH-50);
        float y = 150 + rand() % (WINDOW_HEIGHT-50);
        std::cout << x << ", " << y << std::endl;
        e.move(x, y);
        entityList.push_back(e);
    }
	cursorSprite.setScale(0.2f, 0.2f);
    int redval = 0;	
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
				
                if (event.key.code == sf::Keyboard::Space){ testMap.initGroundMap(); }
                if (event.key.code == sf::Keyboard::L){ testMap.initLayeredGroundMap(); }
				/*switch(gameState)
				{
                    case 0: 
                        std::cout << "GS0" << std::endl;
				        if (event.key.code == sf::Keyboard::Add){ redval+= 3; }
				        if (event.key.code == sf::Keyboard::Subtract){ redval -= 3; }
				        if (event.key.code == sf::Keyboard::Space){ gameState = 1; }
                        break;
                    case 1: 
                        std::cout << "GS1" << std::endl;
				        if (event.key.code == sf::Keyboard::Space){ gameState = 2; }
                        break;
                    case 2: 
                        std::cout << "GS2" << std::endl;
				        if (event.key.code == sf::Keyboard::Space){ gameState = 3; }
				        // Spawn a unit factory
                        // if (event.key.code == sf::Keyboard::Space){ gameState = 3; }
                        break;
                    case 3: 
                        std::cout << "GS3" << std::endl;
				        if (event.key.code == sf::Keyboard::Space){ gameState = 0; }
				        // Spawn units
				        // if (event.key.code == sf::Keyboard::Space){ gameState = 0; }
                        break;
                    default: 
                        std::cout << "DS" << std::endl;
				        if (event.key.code == sf::Keyboard::Space){ gameState = 0; }
                        break;
                }*/
            }
        }
        // Update entities :
        /*if(cumulativeTime > 1.)
        {
            for(std::vector<Entity>::iterator e = entityList.begin() ; e != entityList.end() ; e++)
            {
                float x = 0.1 * (rand() % (WINDOW_WIDTH -10) - 0.5 * WINDOW_WIDTH);
                float y = 0.1 * (rand() % (WINDOW_HEIGHT-10) - 0.5 * WINDOW_HEIGHT);
                //e.animate(cumulativeTime);
                e->move(x, y);
            }
            cumulativeTime = 0.;
        }*/
        for(std::vector<Entity>::iterator e = entityList.begin() ; e != entityList.end() ; e++)
        {
            //e.animate(cumulativeTime);
            e->move(dx, dy);
        }
        //for(auto e : entityList)
        for(std::vector<Entity>::iterator e = entityList.begin() ; e != entityList.end() ; e++)
        {
            //e.animate(cumulativeTime);
            e->animate(duration);
        }
        sf::Color bgColor = sf::Color(0+redval, 0, 0);
		App.clear(bgColor);
        testMap.render(&App);
		App.draw(cursorSprite);
        for(auto e : entityList)
        {
            //e.render(&App);
        }
		App.display();
    }
    return EXIT_SUCCESS;
}
