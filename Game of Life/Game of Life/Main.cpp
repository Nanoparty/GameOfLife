#include "Main.h"
#include <malloc.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);

    array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH> buffer1;
    array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH> buffer2;

    // set initial world state
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            bool spawn = (rand() % 100) <= 30;
            if (spawn)
            {
                buffer1[x][y] = 1;
            }
            else 
            {
                buffer1[x][y] = 0;
            }
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
                stepWorld(buffer1, buffer2);
        }

        window.clear();

        // draw world state
        for (unsigned int x = 0; x < MAP_WIDTH; x++)
        {
            for (unsigned int y = 0; y < MAP_HEIGHT; y++)
            {
                if (buffer1[x][y] == 1)
                {
                    sf::RectangleShape pixel(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    pixel.setPosition(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE));
                    pixel.setFillColor(sf::Color(255, 255, 255));
                    window.draw(pixel);
                }
            }
        }

        window.display();

        stepWorld(buffer1, buffer2);
    }

    return 0;
}

void stepWorld(array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer1, array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer2)
{
    // update world state
    isAlive(buffer1, buffer2);

    // swap buffers
    for (unsigned int x = 0; x < MAP_WIDTH; x++)
    {
        for (unsigned int y = 0; y < MAP_HEIGHT; y++)
        {
            buffer1[x][y] = buffer2[x][y];
        }
    }
}

void isAlive(array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer1, array<array<unsigned char, MAP_HEIGHT>, MAP_WIDTH>& buffer2)
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            int startState = buffer1[x][y];
            int endState = 0;

            int liveNeighbours = 0;

            if (x > 0) {
                liveNeighbours += buffer1[x - 1][y];
            }
            if (x < MAP_WIDTH - 1) {
                liveNeighbours += buffer1[x + 1][y];
            }
            if (y > 0) {
                liveNeighbours += buffer1[x][y - 1];
            }
            if (y < MAP_HEIGHT - 1) {
                liveNeighbours += buffer1[x][y + 1];
            }
            if (x > 0 && y > 0) {
                liveNeighbours += buffer1[x - 1][y - 1];
            }
            if (x > 0 && y < MAP_HEIGHT - 1) {
                liveNeighbours += buffer1[x - 1][y + 1];
            }
            if (x < MAP_WIDTH - 1 && y > 0) {
                liveNeighbours += buffer1[x + 1][y - 1];
            }
            if (x < MAP_WIDTH - 1 && y < MAP_HEIGHT - 1) {
                liveNeighbours += buffer1[x + 1][y + 1];
            }

            if (startState)
            {
                if (liveNeighbours < 2) endState = 0;
                if (liveNeighbours == 2 || liveNeighbours == 3) endState = 1;
                if (liveNeighbours > 3) endState = 0;
            }
            else {
                if (liveNeighbours == 3) endState = 1;
                else endState = 0;
            }

            buffer2[x][y] = endState;
        }
    }
}