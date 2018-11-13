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
        int tileWidth;
        int tileHeight;
        //char occupancy[width][height];
        std::vector<std::vector<char> > occupancy;
        sf::VertexArray visibleMap;

    public:
        //Map();
        Map(int w, int h, int tw, int th);

        int getWidth(){ return width; }
        int getHeight(){ return height; }
        int getTileWidth(){ return tileWidth; }
        int getTileHeight(){ return tileHeight; }

        void render(sf::RenderWindow * app);
        void initRandMap();
        void initGroundMap();
        void initLayeredGroundMap();
        char getRandType();
        char getTileType(int x, int y);
        void setTileType(int x, int y, char t);

        void addColumn();

};

#endif
