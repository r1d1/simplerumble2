#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

// should it be an Entity ?
class Map
{
    private:
        //std::vector<std::vector<char> > occupancy;
        //std::vector<char[32] > occupancy;
        int width;
        int height;
        //char occupancy[width][height];
        std::vector<std::vector<char> > occupancy;
        sf::VertexArray visibleMap;

    public:
        //Map();
        Map(int w, int h);
        void render(sf::RenderWindow * app);
        void initRandMap();
        void initGroundMap();
        void initLayeredGroundMap();
        char getRandType();

        void addColumn();

};

#endif
