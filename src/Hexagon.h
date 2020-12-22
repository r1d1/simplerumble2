#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>

//#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>

class Hexagon
{
	private:
		int m_ID;
	//	Hexagon * neighbour[6];
		float m_xc;
		float m_yc;
		float m_radius;
		std::string m_type;
		//center / position
	public:
		Hexagon();
		Hexagon(int id, float posX, float posY, float rad, std::string type);
		void display(sf::RenderWindow & app);
};
