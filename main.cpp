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
#include "Attack.h"
#include "utils.h"

#define APP_VERSION 0.1
#define APP_STATUS "b"

#define SPEED 1000
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

int main(int argc, char** argv)
{
	int gameState = 0;
	
	srand(time(NULL));
	// ================ Initialising ! ================
	// Create main window
	// Black screen
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SIMPLE RUMBLE !!!");
	
	sf::Sprite * opponentSprite;
	sf::Sprite * playerSprite;
	
	sf::Texture character1Texture;
	sf::Sprite character1Sprite;
	sf::Texture character2Texture;
	sf::Sprite character2Sprite;
	if (!character1Texture.loadFromFile("images/npc1-full.png")){ std::cout << "Error when loading opponent image" << std::endl; return EXIT_FAILURE; }
	else{ character1Sprite.setTexture(character1Texture); }
	if (!character2Texture.loadFromFile("images/npc2-full.png")){ std::cout << "Error when loading player image" << std::endl; return EXIT_FAILURE; }
	else{ character2Sprite.setTexture(character2Texture); }

	std::cout << "Texture sprite : " << (character1Sprite.getTexture())->getSize().x << " " <<  (character1Sprite.getTexture())->getSize().y << std::endl;

	character1Sprite.setTextureRect(sf::IntRect(32, 96, 32, 48));
	std::cout << "Texture sprite : " << (character1Sprite.getTexture())->getSize().x << " " <<  (character1Sprite.getTexture())->getSize().y << std::endl;
	character2Sprite.setTextureRect(sf::IntRect(32, 48, 32, 48));
	character1Sprite.setScale(2.0f, 2.0f);
	character2Sprite.setScale(2.0f, 2.0f);
	character1Sprite.setPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
	character2Sprite.setPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
	int animFrame = 0;
	
	bool posOne = true;

	sf::Texture axeTexture;
	sf::Sprite axeSprite;
	sf::Texture swordTexture;
	sf::Sprite swordSprite;
	if (!axeTexture.loadFromFile("images/axe.png")){ std::cout << "Error when loading axe image" << std::endl; return EXIT_FAILURE; }
	else{ axeSprite.setTexture(axeTexture); }
	if (!swordTexture.loadFromFile("images/sword.png")){ std::cout << "Error when loading sword image" << std::endl; return EXIT_FAILURE; }
	else{ swordSprite.setTexture(swordTexture); }

	// ##### TITLE Interface #####
	// State 0
	sf::Font fontTitle;
	sf::Font fontNormal;
	if( !fontTitle.loadFromFile("fonts/BlackChancery.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	if( !fontNormal.loadFromFile("fonts/arial.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	//if( !font.loadFromFile("arial.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	sf::Text titleText;
	std::string titleString = "SIMPLE RUMBLE 2 !"; // + std::string(APP_STATUS) + std::to_string(APP_VERSION);
	titleText.setString(titleString);
	titleText.setCharacterSize(36);
	titleText.setRotation(20);
	titleText.setPosition(WINDOW_WIDTH * 1.0/5, WINDOW_HEIGHT * 2.5/5);
	titleText.setFont(fontTitle);

	// ##### MENU Interface #####
	std::cout << "Done." << std::endl << "Init Menu ..." << std::endl;

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
	if (!cursorTexture.loadFromFile("images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
	else{ cursorSprite.setTexture(cursorTexture); }

	cursorSprite.setScale(0.2f, 0.2f);

	sf::Text choice0;

	choice0.setPosition(WINDOW_WIDTH *4.5/ 10, WINDOW_HEIGHT * 6 / 10);
	choice0.setColor(sf::Color::Red);
	bool startColorState=true;

	sf::Text choice1;
	sf::Text choice2;
	sf::Text choice3;
	sf::Text choice4;
	sf::Text choice5;
	sf::Text choice6;
	sf::Text choice7;

	choice0.setString("Start");
	choice0.setCharacterSize(32);
	choice0.setFont(fontTitle);

	choice1.setString("Attack");
	choice1.setCharacterSize(16);
	choice1.setFont(fontNormal);
	
	choice2.setString("Defend");
	choice2.setCharacterSize(16);
	choice2.setFont(fontNormal);
	
	choice3.setString("Surrender");
	choice3.setCharacterSize(16);
	choice3.setFont(fontNormal);
	
	choice4.setString("Do nothing");
	choice4.setCharacterSize(16);
	choice4.setFont(fontNormal);
	
	choice5.setString("Quit");
	choice5.setCharacterSize(16);
	choice5.setFont(fontTitle);
	
	choice6.setString("End of the Game !");
	choice6.setCharacterSize(32);
	choice6.setFont(fontTitle);

	choice7.setString("Play again !");
	choice7.setCharacterSize(16);
	choice7.setFont(fontNormal);
	
	choice1.setPosition(25.0f, WINDOW_HEIGHT * 4.5 / 5);
	choice2.setPosition(25.0f + WINDOW_WIDTH * 1 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice3.setPosition(25.0f + WINDOW_WIDTH * 2 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice4.setPosition(25.0f + WINDOW_WIDTH * 3 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice5.setPosition(25.0f + WINDOW_WIDTH * 4 / 5, WINDOW_HEIGHT * 4.5 / 5);
	choice6.setPosition(25.0f + WINDOW_WIDTH * 0.5 / 2, WINDOW_HEIGHT / 4);
	choice7.setPosition(WINDOW_WIDTH * 1.05 / 3, WINDOW_HEIGHT * 4.5 / 5);
	
	// -------------------------------------------------------------
	int menuChoice = 0;
	int maxMenuChoices = 5;
	// 0 : attack ; 1 : defend ; 2 : surrender ; 3 : do nothing ; 4 : quit game
	int characterChoice = 0;
	int maxCharacterChoices = 2;
	int endMenuChoice = 0;
	int maxEndMenuChoices = 2;

	// -------------------------------------------------------------
	Attack sword("Sword", 3, 450);
	Attack axe("Axe", 10, 350);
	// Attack type :
	// Moon
	// Feather
	// Light
	std::vector<std::string> attackTypes;
	attackTypes.push_back("Moon");
	attackTypes.push_back("Feather");
	attackTypes.push_back("Light");

	std::vector<Attack> attackList;
	Attack attackOne("Blade", attackTypes.at(0), 2);
	Attack attackTwo("Blade", attackTypes.at(1), 1);
	Attack attackThree("Blade", attackTypes.at(2), 1);
	attackList.push_back(attackOne);
	attackList.push_back(attackTwo);
	attackList.push_back(attackThree);

	Agent * opponent;
	Agent * player;

	Agent character1("", 70 + rand() % 30);
	Agent character2("", 70 + rand() % 30);

	// For debugging purpose only :
//	player = &character2;
//	opponent = &character2;
//	playerSprite = &character1Sprite;
//	opponentSprite = &character1Sprite;

	// ----------------------------------------
	std::vector<Agent> characters;

	// ----------------------------------------
	// Start game loop
	float cumulativeTime = 0.0;
	float cursorPosX=0.0, cursorPosY=0.0;
	cursorSprite.setPosition(cursorPosX, cursorPosY);
	sf::Clock clock;
	while (App.isOpen())
	{
		// Process events
		sf::Event event;
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();
		bool validatedChoice = false;
		int enemyChoice;

		while (App.pollEvent(event))
		{
			// Event processing
			if(event.type == sf::Event::Closed){ App.close(); }
			if(event.type == sf::Event::KeyPressed)
			{
				// DEBUG : if (event.key.code == sf::Keyboard::Escape){ App.close(); }
				
				switch(gameState)
				{
					// Titlescreen
					case 0 : 
						if (event.key.code == sf::Keyboard::Return){ gameState = 1; }
					break;
					// Character Selection
					case 1 : 
						if (event.key.code == sf::Keyboard::Left){ characterChoice = ( ((characterChoice-1)>0)? characterChoice-1 : 0); }
						if (event.key.code == sf::Keyboard::Right){ characterChoice = ( ((characterChoice+1) < maxCharacterChoices-1)? characterChoice+1 : maxCharacterChoices-1); }
						player = ((!characterChoice) ? &character1 : &character2);
						opponent = ((!characterChoice) ? &character2 : &character1);
						playerSprite = ((characterChoice) ? &character1Sprite : &character2Sprite);
						opponentSprite = ((characterChoice) ? &character2Sprite : &character1Sprite);

					//	std::cout << "character choice " << characterChoice << std::endl;
						if (event.key.code == sf::Keyboard::Return)
						{
							gameState = 2;
							opponentSprite->setPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
							playerSprite->setPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
						}
					break;
					case 2 :
						if( !player->isAlive() || !opponent->isAlive() ){ gameState = 3; }
						else
						{
							// Switching on options :
							if (event.key.code == sf::Keyboard::Return){ validatedChoice = true; }
							if (event.key.code == sf::Keyboard::Left){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
							if (event.key.code == sf::Keyboard::Right){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
							if (event.key.code == sf::Keyboard::Up){ menuChoice = ( ((menuChoice-1)>0)? menuChoice-1 : 0); }
							if (event.key.code == sf::Keyboard::Down){ menuChoice = ( ((menuChoice+1) < maxMenuChoices-1)? menuChoice+1 : maxMenuChoices-1); }
							if (event.key.code == sf::Keyboard::A){ player->changeAttack(&attackOne); opponent->changeAttack(&attackTwo); std::cout << "You got the Axe !" << std::endl; }
						}
					break;
					case 3 :
						std::cout << "End state !" << std::endl;
							// Switching on options :
						if (event.key.code == sf::Keyboard::Left){ endMenuChoice = ( ((endMenuChoice-1)>0)? endMenuChoice-1 : 0); }
						if (event.key.code == sf::Keyboard::Right){ endMenuChoice = ( ((endMenuChoice+1) < maxEndMenuChoices-1)? endMenuChoice+1 : maxEndMenuChoices-1); }
						std::cout << "character choice " << endMenuChoice << std::endl;

						if (event.key.code == sf::Keyboard::Return)
						{
							if(endMenuChoice == 0)
							{
								// If play again, back to character selection screen
								gameState = 1; 
								// Reset if we already finished a game :
								character1.resetCharacter();
								character2.resetCharacter();
								character1Sprite.setPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
								character2Sprite.setPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
							} 
							else{ App.close(); } // if quit
						}
					break;
					default :
						std::cout << "Should not happen in the final game." << std::endl;
						std::cout << "Unexpected display state !" << std::endl;
						App.close();
					break;
				}
				std::cout << "Menu choice : " << menuChoice << std::endl;
			}
			
			switch(gameState)
			{
				case 1 :
					cursorSprite.setScale(0.17f, 0.17f);
					cursorPosX = (WINDOW_WIDTH * (characterChoice + 0.84))  / 3;
					cursorPosY = 20.0f;
				break;
				case 2 :
					cursorSprite.setScale(0.1f, 0.1f);
					cursorPosX = (WINDOW_WIDTH * (menuChoice)) / maxMenuChoices;
					cursorPosY = WINDOW_HEIGHT - 45.0f;
				break;
				case 3 :
					cursorSprite.setScale(0.1f, 0.1f);
					cursorPosX = (WINDOW_WIDTH * (endMenuChoice + 0.6)) / maxEndMenuChoices + 0.5;
					//std::cout << "cursor x : " << cursorPosX << std::endl;
					cursorPosY = WINDOW_HEIGHT - 45.0f;
				break;
				default:
					cursorPosX = -100; 
					cursorPosY = -100;
				break;
			}
			if(validatedChoice) // should go in config variable fightState = 2;
			{
				enemyChoice = rand() % maxMenuChoices;
				switch(menuChoice)
				{
					case 0:
						std::cout << "Attacking !" << std::endl;
						player->attack(*opponent);
					break;
					case 1:
						std::cout << "Defending !" << std::endl;
						player->defend();
					break;
					case 2:
						std::cout << "Surrender !" << std::endl;
						player->surrender();
					break;
					case 3:
						std::cout << "You coward !" << std::endl;
						player->takeDamage(rand() % 10);
					break;
					case 4:
						App.close();
					break;
					default:
						std::cout << "Unknown choice" << std::endl;
					break;
				}
				validatedChoice = false;
				switch(enemyChoice)
				{
					case 0:
						std::cout << "Attacking !" << std::endl;
						opponent->attack(*player);
					break;
					case 1:
						std::cout << "Defending !" << std::endl;
						opponent->defend();
					break;
					case 2:
						std::cout << "Surrender !" << std::endl;
						opponent->surrender();
					break;
					default:
						std::cout << "Wrong choice !" << std::endl;
						opponent->takeDamage(2);
					break;
				}
				std::cout << "Player state : " << std::endl;
				player->displayState();
				std::cout << "Opponent state : " << std::endl;
				opponent->displayState();
			}
	      	}
		// End of pollEvent
		cursorSprite.setPosition(cursorPosX, cursorPosY);
		sf::Color bgColor = sf::Color::Black;
		switch(gameState)
		{
			case 1 :
				bgColor = sf::Color::Black;
			break;
			case 2:
				bgColor = sf::Color(0, 192, 255);
			default:
			break;
		}

	//	std::cout << "Segfault ?" << std::endl;
		App.clear(bgColor);

		sf::Text char1Name;
		sf::Text char1MaxLife;
		sf::Text char1Shield;
		sf::Text char2Name;
		sf::Text char2MaxLife;
		sf::Text char2Shield;
		
		char1Name.setFont(fontTitle);
		char1Name.setString(character1.getName());
		char1MaxLife.setFont(fontTitle);
		char1MaxLife.setString("Life : " + std::to_string(character1.getMaxLife()));
		char1Shield.setString("Shield : " + std::to_string(character1.getShield()));
		char1Shield.setFont(fontTitle);

		char2Name.setFont(fontTitle);
		char2Name.setString(character2.getName());
		char2MaxLife.setFont(fontTitle);
		char2MaxLife.setString("Life : " + std::to_string(character2.getMaxLife()));
		char2Shield.setString("Shield : " + std::to_string(character2.getShield()));
		char2Shield.setFont(fontTitle);

		char1Name.setPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 0.8 / 4);
		char1Name.setCharacterSize(24);
		char1MaxLife.setPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 1.7 / 4);
		char1MaxLife.setCharacterSize(24);
		char1Shield.setPosition(WINDOW_WIDTH * 0.3 / 3, WINDOW_HEIGHT * 2 / 4);
		char1Shield.setCharacterSize(24);
			
		char2Name.setPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 0.8 / 4);
		char2Name.setCharacterSize(24);
		char2MaxLife.setPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 1.7 / 4);
		char2MaxLife.setCharacterSize(24);
		char2Shield.setPosition(WINDOW_WIDTH * 2.3 / 3, WINDOW_HEIGHT * 2 / 4);
		char2Shield.setCharacterSize(24);
		
//		std::cout << "Segfault 2 ?" << std::endl;
//		cumulativeTime += elapsedTime.asSeconds(); 
		//std::cout << "Cum time:" << cumulativeTime << std::endl;

		float playerRatio = 0.0;
		float opponentRatio = 0.0;
		if( player && (player->getMaxLife() != 0) ){ playerRatio = float(player->getLife()) / player->getMaxLife(); }
		if( opponent && (opponent->getMaxLife() !=0) ){ opponentRatio = float(opponent->getLife()) / opponent->getMaxLife(); }
		sf::Text playerLifeDisplay;
		playerLifeDisplay.setFont(fontTitle);
		playerLifeDisplay.setString("0");
		if( player ){ playerLifeDisplay.setString(std::to_string(player->getLife())); }
		playerLifeDisplay.setPosition(10, 10);

		sf::Text opponentLifeDisplay;
		opponentLifeDisplay.setString("0");
		opponentLifeDisplay.setFont(fontTitle);
		if( opponent ){ opponentLifeDisplay.setString(std::to_string(opponent->getLife())); }
		opponentLifeDisplay.setPosition(WINDOW_WIDTH-40, 10);
				
		// Life slot
	//	sf::CircleShape life;
	//	sf::CircleShape shape(50);
	//	life.setFillColor(sf::Color((1.0 - playerRatio) * 255, playerRatio * 255, 0));
		//, 5, sf::Color(255, 255, 255))
		//10, 10, 50, sf::Color((1.0 - playerRatio) * 255, playerRatio * 255, 0), 5, sf::Color(255, 255, 255))

//		std::cout << playerRatio << " " << opponentRatio << std::endl;
		switch(gameState)
		{
			case 0:
				// State : Title 
				if(cumulativeTime > 0.3)
				{
					// Animation of Sprites
					if( posOne ){ choice0.setColor(sf::Color::Red); }
					else{ choice0.setColor(sf::Color::White); }
					cumulativeTime = 0.0;
					posOne = !posOne;
				}
				else{ cumulativeTime += elapsedTime.asSeconds(); }
				titleText.setColor(sf::Color(192, 64, 0));
				titleText.setScale(1.1f,1.1f);
				App.draw(titleText);
				titleText.setColor(sf::Color(255, 255, 0));
				App.draw(titleText);
				
				startColorState = !startColorState;
				
				App.draw(choice0);
			break;
			case 1 :
				// This animation code should be factored: 
				if(cumulativeTime > 0.25)
				{
					animFrame = (animFrame + 1) % 4;
					cumulativeTime = 0.0;
				}
				else{ cumulativeTime += elapsedTime.asSeconds(); }
				character1Sprite.setTextureRect(sf::IntRect(animFrame*32, 0, 32, 48));
				character2Sprite.setTextureRect(sf::IntRect(animFrame*32, 0, 32, 48));
				App.draw(char1Name);
				App.draw(char1MaxLife);
				App.draw(char1Shield);
				App.draw(char2Name);
				App.draw(char2MaxLife);
				App.draw(char2Shield);
				App.draw(character1Sprite);
				App.draw(character2Sprite);
			break;
			case 2 :
				
				playerSprite->setTextureRect(sf::IntRect(animFrame*32, 48, 32, 48));
				opponentSprite->setTextureRect(sf::IntRect(animFrame*32, 96, 32, 48));
				if(cumulativeTime > 0.25)
				{
					animFrame = (animFrame + 1) % 4;
					cumulativeTime = 0.0;
				}
				else{ cumulativeTime += elapsedTime.asSeconds(); }
					
		//		App.draw(life); //, sf::Color::Black, 0, sf::Color::Red);
				App.draw(playerLifeDisplay);
				
			//	App.draw(sf::Shape::Circle(WINDOW_WIDTH-10, 10, 50, sf::Color((1.0 - opponentRatio) * 255, opponentRatio * 255, 0), 5, sf::Color(255, 255, 255))); //, sf::Color::Black, 0, sf::Color::Red);
				App.draw(opponentLifeDisplay);
			//	
			//	// BG :
			//	App.draw(sf::Shape::Rectangle(0, WINDOW_HEIGHT * 0.8/2, WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(192, 128, 64), 0, sf::Color(128,128,0))); //, sf::Color::Black, 0, sf::Color::Red);
			//	// Menu : 
			//	App.draw(sf::Shape::Rectangle(0, WINDOW_HEIGHT * 4.2/5, WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color(192, 0, 0), 5, sf::Color(64, 0, 0))); //, sf::Color::Black, 0, sf::Color::Red);
				App.draw(*opponentSprite);
				App.draw(*playerSprite);
				App.draw(choice1);
				App.draw(choice2);
				App.draw(choice3);
				App.draw(choice4);
				App.draw(choice5);
			break;
			case 3 :
				// End state :
				App.draw(choice5);
				App.draw(choice6);
				App.draw(choice7);
			break;
			default:
				std::cout << "Unexpected display state !" << std::endl;
				App.close();
			break;
		}
		App.draw(cursorSprite);
		App.display();
	}

	// Reseting pointers (not useful ?)
	player = opponent = 0;

	return EXIT_SUCCESS;
}

