#include "Entity.h"

//Entity::Entity(std::string entity_name, std::string texture_name)
Entity::Entity(std::string entity_name, sf::Texture * ptexture = NULL)
{
    pos_x = 0.;
    pos_y = 0.;
    facing = 'w';
    graphicsUpdated=false;
    dataUpdated=false;
    banaana = 0.;
    count = -1;
    // Should go in an animation class:
    animFrame = 0;
    cumulativeTime = 0.;
    texture = ptexture;
    sprite.setTexture(*ptexture);
	// to be done intelligently:
    //sprite.setScale(0.2f, 0.2f);
    sprite.setPosition(pos_x, pos_y);
}

Entity::~Entity(){}

bool Entity::getGraphicsFlag(){ return graphicsUpdated; }

bool Entity::getDataFlag(){ return dataUpdated; }

void Entity::move(float dx=0., float dy=0.)
{
    pos_x += dx;
    pos_y += dy;
    sprite.setPosition(pos_x, pos_y);
}

void Entity::animate(float elapsedTime)
{
    // Animator.play();
    if(cumulativeTime > 0.25)
    {
        animFrame = (animFrame + 1) % 4;
        cumulativeTime = 0.0;
    }
    else{ cumulativeTime += elapsedTime; }
}

void Entity::render(sf::RenderWindow * app)
{
    sprite.setTextureRect(sf::IntRect(animFrame*32, 48, 32, 48));
    app->draw(sprite);
}
