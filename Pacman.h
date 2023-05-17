#pragma once
#include <SFML/Graphics.hpp>
#pragma once
#include <array>
#include "Global.h"
using std::array;

class Pacman
{
	unsigned char direction;

	Position position;

	unsigned short energizer_timer;

	bool scare_ghost;

	bool energizer_eaten;

	bool dead;

	bool can_move;

public:
	Pacman();

	void draw( sf::RenderWindow& i_window);
	void set_position(unsigned short i_x, unsigned short i_y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

	Position get_position();

	unsigned char get_direction();
	unsigned short get_energizer_timer();


	bool map_collision_energizer(array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

	void set_dead(bool i_dead);

	bool get_dead();

	void reset();
};
