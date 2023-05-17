#pragma once
#include <array>
#include "Ghost.h"
#include "Pacman.h"

class GhostManager
{
	std::array<Ghost, 4> ghosts;

	unsigned char current_wave;

	unsigned short wave_timer;

public:

	GhostManager();

	void draw(sf::RenderWindow& i_window);
	void reset(const std::array<Position, 4>& i_ghost_positions);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman);
};