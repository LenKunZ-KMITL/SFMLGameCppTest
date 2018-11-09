#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class SpriteObject
{
    public:
        enum direction { dr,dl,wr,wl,jr,jl};
        int x[6] = {0};
        int y = wr ;
        const int moveSpeed = 1 ;
        const int jumpSpeed = 1 ;
        const float g = 1 ;

        /**************************************************************************************/
        const sf::Sprite picturePlayerPath(string whichCha) // know which is picture of player
        {
            string filePath = "pic/character/" + whichCha + ".png" ;
            sf::Texture playerTexture ;
            playerTexture.loadFromFile(filePath);
            sf::Sprite playerSprite (playerTexture);
            return playerSprite ;
        }
        const sf::Sprite updateDrawing(const sf::Sprite &playerSprite , const sf::Keyboard key  )
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                if(y != jr && y!= jr)
                    y = wr ;
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                if(y == wr && (y != jr || y != jl))
                    y = dr;
                else if(y == wl && (y != jr || y != jl))
                    y = dl;
        }
        SpriteObject();

    protected:

    private:
};

#endif // SPRITEOBJECT_H
