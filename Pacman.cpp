#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

#include "Global.h"
#include "Pacman.h"
#include "MapCollision.h"

using std::array;


Pacman::Pacman() :
	direction(3),
	energizer_timer(0),
	scare_ghost(false),
	energizer_eaten(false),
	dead(0),
	can_move(1)
{
	//I just realized that I already explained everything in the Ghost class.
	//And I don't like to repeat myself.
}

void Pacman::reset()
{
	 direction = 3,
	energizer_timer = 0,
	energizer_eaten = false,
	dead = 0,
	can_move = 1;
}

bool Pacman::get_dead()
{
	return dead;
}

void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;

	//if (1 == dead)
	//{
	//	//Making sure that the animation starts from the beginning.
	//	animation_timer = 0;
	//}
}


void Pacman::draw(sf::RenderWindow& i_window)
{
	sf::CircleShape circle(CELL_SIZE / 2);

	if (get_dead() == 1)
	{
		circle.setFillColor(sf::Color(255, 0, 0));
		can_move = 0;
	
	}

	else
	{
		circle.setFillColor(sf::Color(255, 255, 0));
	}

	
	
	circle.setPosition(position.x, position.y);
	i_window.draw(circle);
}

void Pacman::set_position(unsigned short i_x, unsigned short i_y)
{
	position.x = i_x;
	position.y = i_y;
}

unsigned char Pacman::get_direction()
{
	return direction;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}



bool Pacman::map_collision_energizer(array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	bool output = 0;

	//Getting the exact position.
	float cell_x = position.x / static_cast<float>(CELL_SIZE);
	float cell_y = position.y / static_cast<float>(CELL_SIZE);

	//A ghost/Pacman can intersect 4 cells at most.
	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0: //Bottom left cell
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 1: //Bottom right cell
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 2: //Top left cell
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));

			break;
		}
		case 3: //Top right cell
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_y));
		}
		}

		//Making sure that the position is inside the map.
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{

			if (Cell::Energizer == i_map[x][y] && // When pacman eats the energizer
				abs(cell_x - x - 0.3f) < 0.5f &&
				abs(cell_y - y - 0.3f) < 0.5f)

			{
				i_map[x][y] = Cell::Empty;
				output = 1;
			}
		}
	}

	return output;
}


void Pacman::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{

	std::array<bool, 4> walls{};
	walls[0] = map_collision(1,1, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(1,1, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(1,1, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(1,1, position.x, PACMAN_SPEED + position.y, i_map);


	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
		{
			direction = 0;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction] && can_move)
	{
		switch (direction)
		{
		case 0:
		{
			position.x += PACMAN_SPEED;

			break;
		}
		case 1:
		{
			position.y -= PACMAN_SPEED;

			break;
		}
		case 2:
		{
			position.x -= PACMAN_SPEED;

			break;
		}
		case 3:
		{
			position.y += PACMAN_SPEED;
		}
		}
	}

	if (position.x < -CELL_SIZE)
	{
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (position.x > CELL_SIZE * MAP_WIDTH)
	{
		position.x = PACMAN_SPEED - CELL_SIZE;
	}


	if (map_collision_energizer(i_map))
	{
		energizer_timer = ENERGIZER_DURATION;
		
	}
	else
	{
		energizer_timer = std::max(0, energizer_timer - 1);
	}
}

Position Pacman::get_position()
{
	return position;
}

