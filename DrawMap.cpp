#pragma once
#include "DrawMap.h"
using std::array;


void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window)
{
    sf::RectangleShape rectangle_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    for (unsigned char b = 0; b < MAP_HEIGHT; b++)
    {
        for (unsigned char a = 0; a < MAP_WIDTH; a++)
        {
            switch (i_map[a][b])
            
            {
                case Cell::Wall:
                {
                    
                    rectangle_shape.setFillColor(sf::Color(36, 36, 255));
                    rectangle_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
                    i_window.draw(rectangle_shape);
                    break;
                }
                case Cell::Pellet:
                {
                    sf::CircleShape circle_shape;
                    circle_shape.setRadius(CELL_SIZE / 8);
                    circle_shape.setFillColor(sf::Color(255, 182, 255));
                    circle_shape.setPosition(CELL_SIZE * a + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 2 - circle_shape.getRadius()));
                    i_window.draw(circle_shape);
                    break;
                }
                case Cell::Energizer:
                {
                    sf::CircleShape circle_shape;
                    circle_shape.setRadius(CELL_SIZE / 4);
                    circle_shape.setFillColor(sf::Color(255, 182, 255));
                    circle_shape.setPosition(CELL_SIZE * a + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 2 - circle_shape.getRadius()));
                    i_window.draw(circle_shape);
                    break;
                }
                case Cell::Door:
                {
                
                    rectangle_shape.setFillColor(sf::Color(255, 255, 255));
                    rectangle_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
                    i_window.draw(rectangle_shape);
                    
                }
            }
            
        }
    }
}


