#pragma once
#include <array>
#include "Global.h"
#include <SFML/Graphics.hpp>

using std::array;


void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window);