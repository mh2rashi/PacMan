#pragma once
#include <array>
#include <string>
#include "Global.h"
#include "Pacman.h"
#include "Ghost.h"

using std::array;
using std::string;

array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& i_map_sketch, array<Position, 4>& i_ghost_positions, Pacman& i_pacman);
