#include <iostream>
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

const int SIZE_X = 5;
const int SIZE_Y = 5;

int camino[SIZE_X][SIZE_Y];

void imprimir(int tablero[SIZE_X][SIZE_Y])
{
    for(int x = 0; x<SIZE_X; x++)
    {
        for(int y = 0; y<SIZE_Y; y++)
        {
            cout<<tablero[x][y];
        }
        cout<<endl;
    }
}

void reset()
{
   for(int x = 0; x<SIZE_X; x++)
    {
        for(int y = 0; y<SIZE_Y; y++)
        {
            camino[x][y] = 0;
        }
    }
}

bool puedoLLegar(int x_inicio,int y_inicio,
                 int x_final, int y_final,
                 int tablero[SIZE_X][SIZE_Y], int pasos)
{
    if(camino[y_inicio][x_inicio] == 1)
    {
        return false;
    }

    if(x_inicio < 0 || y_inicio<0 || x_inicio > (SIZE_X-1) || y_inicio > (SIZE_Y-1) ||
       x_final < 0 || y_final<0 || x_final > (SIZE_X-1) || y_final > (SIZE_Y-1))
       {
            return false;
       }

    if(tablero[y_final][x_final] == 1)
    {
       return false;
    }

    if(x_inicio==x_final && y_inicio==y_final)
    {
        return true;
    }

    if(tablero[y_inicio][x_inicio] == 1)
    {
        return false;
    }

    if(pasos <= 0)
    {
        return false;
    }

    camino[y_inicio][x_inicio] = 1;

    if(puedoLLegar(x_inicio,y_inicio-1,x_final,y_final,tablero,pasos-1))
    {
        return true;
    }

    if(puedoLLegar(x_inicio+1,y_inicio,x_final,y_final,tablero,pasos-1))
    {
        return true;
    }

    if(puedoLLegar(x_inicio,y_inicio+1,x_final,y_final,tablero,pasos-1))
    {
        return true;
    }

    if(puedoLLegar(x_inicio-1,y_inicio,x_final,y_final,tablero,pasos-1))
    {
        return true;
    }

    return false;
}

int main()
{
    int mapa[SIZE_X][SIZE_Y]={{0,1,0,0,0},
                            {0,1,0,1,0},
                            {0,1,0,1,0},
                            {0,1,0,1,0},
                            {0,0,0,1,0}};

    int speed = 5;
    int posx = 0;
    int posy = 0;
    bool hay = puedoLLegar(posx,posy,0,0,mapa,speed);

    RenderWindow window(VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);
    Event event;

    int tileSize = 32;
    Texture tile;
    tile.loadFromFile("tierra1.png");
    Sprite floor; floor.setTexture(tile);

    Texture tile2;
    tile2.loadFromFile("agua13.png");
    Sprite floor2; floor2.setTexture(tile2);

    Texture character;
    character.loadFromFile("ARCHER FRONT.png");
    Sprite p; p.setTexture(character);

    int cursor_x = 0;
    int cursor_y = 0;
    Texture cursort;
    cursort.loadFromFile("cursor.png");
    Sprite cursor; cursor.setTexture(cursort);

    int cont = 0;

    window.clear();

    while(true){

        while (window.pollEvent(event))
        {
           if (event.type == Event::Closed)
               window.close();

           if (Keyboard::isKeyPressed(Keyboard::Up))
           {
               cursor_y -= 1;
           }
           if (Keyboard::isKeyPressed(Keyboard::Down))
           {
               cursor_y += 1;
           }
           if (Keyboard::isKeyPressed(Keyboard::Left))
           {
               cursor_x -= 1;
           }
           if (Keyboard::isKeyPressed(Keyboard::Right))
           {
               cursor_x += 1;
           }
           if (Keyboard::isKeyPressed(Keyboard::Space))
           {
               cont++;
               if(cont%2 == 0)
                {
                    reset();
                    if(hay = puedoLLegar(posx,posy,cursor_x,cursor_y,mapa,speed))
                    {
                        posx = cursor_x;
                        posy = cursor_y;
                    }

                }
           }
        }

        for(int c = 0; c<SIZE_X; c++)
        {
            for(int f = 0; f<SIZE_Y; f++)
            {
                if(mapa[c][f] == 0)
                {
                    floor.setPosition(f*tileSize,c*tileSize);
                    window.draw(floor);
                }else{
                    floor2.setPosition(f*tileSize,c*tileSize);
                    window.draw(floor2);
                }

            }
        }

        p.setPosition(posx*tileSize,posy*tileSize);
        window.draw(p);

        cursor.setPosition(cursor_x*tileSize,cursor_y*tileSize);
        window.draw(cursor);

        window.display();

    }

    return 0;
}
