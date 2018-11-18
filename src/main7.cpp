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

int main(int argc, char** argv)
{
	int gameState = 0;
	int sprite1_x = 32;
    int sprite1_y = 32;
    int sprite1_w = 32;
    int sprite1_h = 32;
    int sprite1_ox = 0;
    int sprite1_oy = 1;
	
	srand(time(NULL));
	// ================ Initialising ! ================
	// Create main window
	// Black screen
	sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SIMPLE RUMBLE !!!");

	sf::Texture animTexture;
    sf::Sprite animatedSprite;
	animatedSprite.setScale(2.0f, 2.0f);
	animatedSprite.setPosition(WINDOW_WIDTH / 2 - 16, WINDOW_HEIGHT / 2 - 16);
    if (!animTexture.loadFromFile("media/images/blob_stand_move.png"))
    {
        std::cout << "Error when loading opponent image" << std::endl;
        return EXIT_FAILURE;
    }
	else{ animatedSprite.setTexture(animTexture); }
    
	animatedSprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
    Animator anim1;
    anim1.addDescription(AnimRow(32,32, 4, 0.25));
    anim1.addDescription(AnimRow(32,32, 4, 0.25));
    anim1.addDescription(AnimRow(32,32, 4, 0.25));
    anim1.addDescription(AnimRow(32,32, 4, 0.25));
    anim1.addDescription(AnimRow(32,32, 4, 0.1));
    anim1.addDescription(AnimRow(32,32, 4, 0.1));
    anim1.addDescription(AnimRow(32,32, 4, 0.1));
    anim1.addDescription(AnimRow(32,32, 4, 0.1));
	int animFrame = 0;

	int characterChoice = 0;
	int maxCharacterChoices = 2;
	int menuChoice = 0;
	int maxMenuChoices = 5;
	// 0 : attack ; 1 : defend ; 2 : surrender ; 3 : do nothing ; 4 : quit game
	int endMenuChoice = 0;
	int maxEndMenuChoices = 2;
    /*
	sf::Sprite * opponentSprite;
	sf::Sprite * playerSprite;
	
	std::cout << "Texture sprite : " << (character1Sprite.getTexture())->getSize().x << " " <<  (character1Sprite.getTexture())->getSize().y << std::endl;

	character1Sprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
	std::cout << "Texture sprite : " << (character1Sprite.getTexture())->getSize().x << " " <<  (character1Sprite.getTexture())->getSize().y << std::endl;
	//character2Sprite.setTextureRect(sf::IntRect(32, 48, 32, 48));
	sprite1_x = 128;
    sprite1_y = 64;
    sprite1_w = 64;
    sprite1_h = 64;
	character1Sprite.setTextureRect(sf::IntRect(sprite1_x, sprite1_y, sprite1_w, sprite1_h));
	character1Sprite.setScale(2.0f, 2.0f);
	character2Sprite.setScale(2.0f, 2.0f);
	character1Sprite.setPosition(WINDOW_WIDTH * 0.8 / 3, WINDOW_HEIGHT / 4);
	character2Sprite.setPosition(WINDOW_WIDTH * 1.8 / 3, WINDOW_HEIGHT / 4);
	int animFrame_p1 = 0;
	
	bool posOne = true;

	sf::Texture axeTexture;
	sf::Sprite axeSprite;
	sf::Texture swordTexture;
	sf::Sprite swordSprite;
	if (!axeTexture.loadFromFile("media/images/axe.png")){ std::cout << "Error when loading axe image" << std::endl; return EXIT_FAILURE; }
	else{ axeSprite.setTexture(axeTexture); }
	if (!swordTexture.loadFromFile("media/images/sword.png")){ std::cout << "Error when loading sword image" << std::endl; return EXIT_FAILURE; }
	else{ swordSprite.setTexture(swordTexture); }

	// ##### TITLE Interface #####
	// State 0
	sf::Font fontTitle;
	sf::Font fontNormal;
	if( !fontTitle.loadFromFile("media/fonts/BlackChancery.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	if( !fontNormal.loadFromFile("media/fonts/arial.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	//if( !font.loadFromFile("arial.ttf") ){ std::cout << "Font cannot be loaded !" << std::endl; }
	sf::Text titleText;
	std::string titleString = "SIMPLE RUMBLE 2 !\n\t\t\t\tv" + std::to_string(Simplerumble_VERSION_MAJOR) + "." +  std::to_string(Simplerumble_VERSION_MINOR);
	std::cout << "SIMPLE RUMBLE 2 ! v" << Simplerumble_VERSION_MAJOR << "." << Simplerumble_VERSION_MINOR << std::endl;
	titleText.setString(titleString);
	titleText.setCharacterSize(36);
	//titleText.setRotation(20);
	titleText.setPosition(WINDOW_WIDTH * 1.0/5, WINDOW_HEIGHT * 1.5/5);
	titleText.setFont(fontTitle);

	// ##### MENU Interface #####
	std::cout << "Done." << std::endl << "Init Menu ..." << std::endl;

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
	if (!cursorTexture.loadFromFile("media/images/menuSelect2.png")){ std::cout << "Error when loading cursor image" << std::endl; return EXIT_FAILURE; }
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

	std::cout << "Atacks:" << std::endl;

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

	std::cout << "Characters:" << std::endl;
	Agent character1("", 70 + rand() % 30);
	Agent character2("", 70 + rand() % 30);


	// ----------------------------------------
	std::vector<Agent> characters;

	// ----------------------------------------
    // */
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

		while (App.pollEvent(event))
		{
			// Event processing
			if(event.type == sf::Event::Closed){ App.close(); }
			if(event.type == sf::Event::KeyPressed)
			{
				// DEBUG :
                if (event.key.code == sf::Keyboard::Escape){ App.close(); }
               
                //if (event.key.code == sf::Keyboard::Left){ characterChoice = ( ((characterChoice-1)>0)? characterChoice-1 : 0); }
                //if (event.key.code == sf::Keyboard::Right){ characterChoice = ( ((characterChoice+1) < maxCharacterChoices-1)? characterChoice+1 : maxCharacterChoices-1); }
                
                // Switching on options :
                if (event.key.code == sf::Keyboard::Z){ sprite1_y = 0*sprite1_h; }
                if (event.key.code == sf::Keyboard::Q){ sprite1_y = 3*sprite1_h; }
                if (event.key.code == sf::Keyboard::S){ sprite1_y = 2*sprite1_h; }
                if (event.key.code == sf::Keyboard::D){ sprite1_y = 1*sprite1_h; }
                if (event.key.code == sf::Keyboard::Space){ anim1.play(true); }
                if (event.key.code == sf::Keyboard::B){ anim1.play(false); }
			}
		
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
		App.display();
        //std::cout << "animframe: " << animFrame << ", " << cumulativeTime << std::endl;
	}

	// Reseting pointers (not useful ?)
	//player = opponent = 0;

	return EXIT_SUCCESS;
}

