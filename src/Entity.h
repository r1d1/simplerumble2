#ifndef ENTITY_H
#define ENTITY_H

/*
 * @author: r1d1
 * @creation : 29/06/2017
 * @description : This class manage the game and visual part of entities in the game
 *
 * */

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
    private:
        std::string name;
        float pos_x;
        float pos_y;
        char facing; // n, e, s, w, m

        int count;

        bool graphicsUpdated;
        bool dataUpdated;

        int animFrame;
        float cumulativeTime;
        float banaana;
        sf::Sprite sprite;
        // use pointer for texture to avoid loading the texture for each entity
        sf::Texture * texture;

    public:
        //Entity();
        Entity(std::string entity_name, sf::Texture * texture_name);
        ~Entity();

        bool getGraphicsFlag();
        bool getDataFlag();
        // update entity location
        //void move();
        void move(float dx, float dy);
        // update graphical part
        void animate(float elapsedTime);
        void render(sf::RenderWindow * app);
};

#endif
