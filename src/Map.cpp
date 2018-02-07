#include "Map.h"
#include <iostream>

Map::Map(int w=32, int h=16)
{
    width = w;
    height = h;
    occupancy.resize(width);
    //visibleMap.setPrimitiveType(sf::Quads);
    for(int i = 0 ; i < width ; i++)
    {
        occupancy[i].resize(height);
        for(int j = 0 ; j < height ; j++)
        {
            occupancy[i][j] = 'a';
        }
    }
}

void Map::initRandMap()
{
    for(int i = 0 ; i < width ; i++)
    {
        for(int j = 0 ; j < height ; j++)
        {
            occupancy[i][j] = getRandType();
        }
    }
}

void Map::initGroundMap()
{
    for(int i = 0 ; i < width ; i++)
    {
        for(int j = 0 ; j < height ; j++)
        {
            if(j + (rand() % 3) < (0.4 * height) ){ occupancy[i][j] = 'a'; }
            else
            {
                if(j + (rand() % 3) > (0.8 * height))
                {
                    occupancy[i][j] = 'r';
                }
                else
                {
                    occupancy[i][j] = getRandType();
                }
            }
        }
    }
}

void Map::initLayeredGroundMap()
{
    float period_air = (rand() % 100)/ 110.;
    float period_grass = (rand() % 100)/ 110.;
    float period_dirt = (rand() % 100)/ 110.;
    for(int i = 0 ; i < width ; i++)
    {
        for(int j = 0 ; j < height ; j++)
        {
            int threshold_air = (0.45 + 0.3 * std::sin(period_air*i)) * height; // (rand() % int(0.0 * height)) + 
            int threshold_grass = (rand() % int(0.2 * height)) + (0.6 + 0.2 * std::sin(period_grass*i)) * height;
            int threshold_dirt = (rand() % int(0.2 * height)) + (0.8 + 0.2 * std::sin(period_dirt*i)) * height;
            //std::cout << "th: " << threshold << ", " << std::flush;
            if(j < threshold_air ){ occupancy[i][j] = 'a'; }
            else
            {
                if(j < threshold_grass ){ occupancy[i][j] = 'g'; }
                else
                {
                    if(j < threshold_dirt )
                    {
                        if( (rand() % 1000) / 1000. < 0.98 ){ occupancy[i][j] = 'd'; }
                        else{ occupancy[i][j] = 'i'; }
                    }
                    else
                    {
                        if( (rand() % 1000) / 1000. < 0.95 ){ occupancy[i][j] = 'r'; }
                        else{ occupancy[i][j] = 'i'; }
                    }
                }
            }
        }
    }
}

char Map::getRandType()
{
    char chartype = 'a';
    int val = rand() % 5;
    switch(val)
    {
        case 0:
            // dirt
            chartype = 'd';
        break;
        case 1:
            // grass
            chartype = 'g';
        break;
        case 2:
            // rock
            chartype = 'r';
        break;
        case 3:
            // iron
            chartype = 'i';
        break;
        case 4:
            // void
            chartype = 'v';
        break;
        default:
            // air
        break;
    }
    return chartype;
}

void Map::addColumn()
{
    char newCol[32];
    for(int i = 0 ; i < width ; i++)
    {
        int val = rand() % 4;
        switch(val)
        {
            case 0:
                // dirt
                newCol[i] = 'd';
            break;
            case 1:
                // grass
                newCol[i] = 'g';
            break;
            case 2:
                // rock
                newCol[i] = 'r';
            break;
            case 3:
                // iron
                newCol[i] = 'i';
            break;
            default:
                // air
                newCol[i] = 'a';
            break;

        }
    }
}

void Map::render(sf::RenderWindow * app)
{
    /*
    int width=occupancy.size();
    sf::Vector2u tileSize = sf::Vector2u(32,32);
    visibleMap.resize(width * 32);
    int c = 0;
    for (std::vector<char[32]>::iterator it = occupancy.begin() ; it != occupancy.end() ; it++)
    {
        for (int j = 0; j < 32; j++)
        {
            // get the current tile number
            char tileNumber = *it[j];
            // find its position in the tileset texture
            // int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            // int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &visibleMap[(c + j * width) * 4];
            // define its 4 corners
            quad[0].position = sf::Vector2f(c * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((c + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((c + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(c * tileSize.x, (j + 1) * tileSize.y);
            
            // define its 4 texture coordinates
            sf::Color qColor = (tileNumber == 'a' ? sf::Color(0,128, 255) :
                               (tileNumber == 'i' ? sf::Color(192,192,192) :
                               (tileNumber == 'g' ? sf::Color(128, 255, 128) :
                               (tileNumber == 'd' ? sf::Color(128,128,64) :
                               (tileNumber == 'r' ? sf::Color(64,64,64) : sf::Color(0,255,0))))));
            quad[0].color = qColor;
            quad[1].color = qColor;
            quad[2].color = qColor;
            quad[3].color = qColor;
        }
        c+=1;
    }*/
    int c = 0;
    int tileWidth=8;
    //for (std::vector<char[32]>::iterator it = occupancy.begin() ; it != occupancy.end() ; it++)
    //{
    for (int i = 0 ; i < width ; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // create an array of 3 vertices that define a triangle primitive
            sf::VertexArray quads(sf::Quads, 4);
            //std::cout << occupancy[i][j] << ", " << std::flush;
            
            // define the position of the triangle's points
            quads[0].position = sf::Vector2f(0 + i * tileWidth, 0 + j * tileWidth);
            quads[1].position = sf::Vector2f(tileWidth + i * tileWidth, 0 + j * tileWidth);
            quads[2].position = sf::Vector2f(tileWidth + i * tileWidth, tileWidth + j * tileWidth);
            quads[3].position = sf::Vector2f(0 + i * tileWidth, tileWidth + j * tileWidth);

            //sf::Color qColor = sf::Color::Red;
            sf::Color qColor = (occupancy[i][j] == 'a' ? sf::Color(0,128, 255) :
                               (occupancy[i][j] == 'i' ? sf::Color(255,255,255) :
                               (occupancy[i][j] == 'g' ? sf::Color(128, 255, 128) :
                               (occupancy[i][j] == 'd' ? sf::Color(128,96,64) :
                               (occupancy[i][j] == 'v' ? sf::Color(128,96,128) :
                               (occupancy[i][j] == 'r' ? sf::Color(64,64,64) : sf::Color(0,0,0)))))));
            // define the color of the triangle's points
            quads[0].color = qColor;
            quads[1].color = qColor;
            quads[2].color = qColor;
            quads[3].color = qColor;
    
            // app->draw(visibleMap);
            app->draw(quads);
        }
        c+=1;
    }
}
