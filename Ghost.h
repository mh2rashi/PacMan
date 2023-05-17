#pragma once
#include "Global.h"
#include <SFML/Graphics.hpp>

class Ghost
{

	bool use_door = 1;

	//It can be the scatter mode or the chase mode
	bool movement_mode;

	unsigned char direction;


	//0 - I'm not frightened
	//1 - Okay, maybe I am
	//2 - AAAAAAAH!!! I'M GOING TO MY HOUSE!
	unsigned char frightened_mode;

	//To make the ghost move more slowly, we'll move it after a certain number of frames. So we need a timer.
	unsigned char frightened_speed_timer;

	bool been_eaten;

	//0 - Red
	//1 - Pink
	//2 - Blue (It's actually cyan, but the website said it's blue. And I didn't wanna argue.)
	//3 - Orange
	unsigned char id;

	sf::Color color;

	Position home;

	Position position;
	// Current target.
	Position target;

	Position home_exit;



public:

	Ghost(unsigned char i_id, sf::Color i_color);

	void draw(sf::RenderWindow& i_window);
	void set_position(unsigned short i_x, unsigned short i_y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman);

	void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position);

	Position get_position();

	float get_target_distance(unsigned char i_direction);

	void set_target(unsigned short i_x, unsigned short i_y);

	void switch_mode();

	bool pacman_collision(const Position& i_pacman_position);

	void reset(const Position& i_home, const Position& i_home_exit);

};