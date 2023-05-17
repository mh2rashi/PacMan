#pragma once
#include <array>
#include "Global.h"
using std::array;

int map_collision(bool i_collect_energizer, bool i_collect_pellets, short i_x, short i_y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);