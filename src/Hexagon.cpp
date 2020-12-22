#include "Hexagon.h"

Hexagon::Hexagon() : m_ID(0), m_xc(0.0), m_yc(0.0), m_radius(25), m_type("None"){}

Hexagon::Hexagon(int id, float posX, float posY, float rad, std::string type) : m_ID(id), m_xc(posX), m_yc(posY), m_radius(rad), m_type(type){}

void Hexagon::display(sf::RenderWindow & app)
{
	sf::CircleShape hex(m_radius, 6);
	//sf::Color typeColor = sf::Color::White; 
	sf::Color typeColor = sf::Color::Black; 
	if( !m_type.compare("Water") ){ typeColor = sf::Color::Blue; }
	if( !m_type.compare("Grass") ){ typeColor = sf::Color::Green; }
	if( !m_type.compare("Lava") ){ typeColor = sf::Color::Red; }
	if( !m_type.compare("Field") ){ typeColor = sf::Color::Yellow; }
	if( !m_type.compare("Dirt") ){ typeColor = sf::Color(128,128,32); }
	if( !m_type.compare("Rock") ){ typeColor = sf::Color(128,128,128); }

	hex.setFillColor(typeColor);
	hex.setOutlineColor(sf::Color::Black);
	hex.setPosition(m_xc, m_yc);
	hex.setOutlineThickness(2);
	app.draw(hex);
}
