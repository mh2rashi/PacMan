#include <SFML/Graphics.hpp>
#include <array>
#include <random>

#include "Global.h"
#include "Pacman.h"
#include "MapCollision.h"
#include "Ghost.h"

using std::array;


//Ghost::Ghost():
//	direction(1),
//	movement_mode(true)
//{
//}

Ghost::Ghost(unsigned char i_id, sf::Color i_color):
	id(i_id), color(i_color)
{
	//I keep writing "gohst" instead of "gohst" (THERE! I did it again!).
	//So in this file I'll write only "gohst".
	//Enjoy!
}

bool Ghost::pacman_collision(const Position& i_pacman_position)
{
	{
		//I used the ADVANCED collision checking algorithm.
		//Only experts like me can understand this.
		if (position.x > i_pacman_position.x - CELL_SIZE && position.x < CELL_SIZE + i_pacman_position.x)
		{
			if (position.y > i_pacman_position.y - CELL_SIZE && position.y < CELL_SIZE + i_pacman_position.y)
			{
				return 1;
			}
		}

		return 0;
	}
}

void Ghost::draw(sf::RenderWindow& i_window)
{
	sf::CircleShape ghost_circle(CELL_SIZE / 2);
	sf::RectangleShape ghost_rectangle(sf::Vector2f(CELL_SIZE, CELL_SIZE /2));


	ghost_rectangle.setPosition(position.x, position.y + CELL_SIZE / 2);
	ghost_circle.setPosition(position.x, position.y);
	
	
	if (frightened_mode != 0)
	{
		ghost_circle.setFillColor(sf::Color(255, 255, 255));
		ghost_rectangle.setFillColor(sf::Color(255, 255, 255));
	}
	else
	{
		ghost_circle.setFillColor(color);
		ghost_rectangle.setFillColor(color);
	}

	

	i_window.draw(ghost_circle);
	i_window.draw(ghost_rectangle);
}

void Ghost::switch_mode()
{
	movement_mode = 1 - movement_mode;
}

void Ghost::set_position(unsigned short i_x, unsigned short i_y)
{
	position.x = i_x;
	position.y = i_y;
}

void Ghost::set_target(unsigned short i_x, unsigned short i_y)
{
	target.x = i_x;
	target.y = i_y;
}


void Ghost::reset(const Position& i_home, const Position& i_home_exit)
{
	movement_mode = 0;
	//Everyone can use the door except the red gohst.
	//Because I hate the red gohst.
	use_door = 0 < id;

	direction = 0;
	frightened_mode = 0;
	frightened_speed_timer = 0;

	//animation_timer = 0;

	been_eaten = 0;

	home = i_home;
	home_exit = i_home_exit;
	target = i_home_exit;
}

void Ghost::update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position)
{
	if (1 == use_door) //If the gohst can use the door.
	{
		if (position == target)
		{
			if (home_exit == target) //If the gohst has reached the exit.
			{
				use_door = 0; //It can no longer use the door.
			}
			else if (home == target) //If the gohst has reached its home.
			{
				if (frightened_mode == 2)
				{
					been_eaten = 1;
				}
				frightened_mode = 0; //It stops being frightened.

				target = home_exit; //And starts leaving the house.
			}
		}
	}

	else
	{
		if (movement_mode == false) //The scatter mode
		{
			//Each gohst goes to the corner it's assigned to.
			switch (id)
			{
			case 0:
			{
				target = { CELL_SIZE * (MAP_WIDTH - 1), 0 };

				break;
			}
			case 1:
			{
				target = { 0, 0 };

				break;
			}
			case 2:
			{
				target = { CELL_SIZE * (MAP_WIDTH - 1), CELL_SIZE * (MAP_HEIGHT - 1) };

				break;
			}
			case 3:
			{
				target = { 0, CELL_SIZE * (MAP_HEIGHT - 1) };
			}
			}
		}
		else //The chase mode
		{
			switch (id)
			{
			case 0: //The red gohst will chase Pacman.
			{
				target = i_pacman_position;

				break;
			}
			case 1: //The pink gohst will chase the 4th cell in front of Pacman.
			{
				target = i_pacman_position;

				switch (i_pacman_direction)
				{
				case 0:
				{
					target.x += CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 1:
				{
					target.y -= CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 2:
				{
					target.x -= CELL_SIZE * GHOST_1_CHASE;

					break;
				}
				case 3:
				{
					target.y += CELL_SIZE * GHOST_1_CHASE;
				}
				}

				break;
			}
			case 2: //The blue gohst.
			{
				target = i_pacman_position;

				//Getting the second cell in front of Pacman.
				switch (i_pacman_direction)
				{
				case 0:
				{
					target.x += CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 1:
				{
					target.y -= CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 2:
				{
					target.x -= CELL_SIZE * GHOST_2_CHASE;

					break;
				}
				case 3:
				{
					target.y += CELL_SIZE * GHOST_2_CHASE;
				}
				}

				//We're sending a vector from the red gohst to the second cell in front of Pacman.
				//Then we're doubling it.
				target.x += target.x - i_ghost_0_position.x;
				target.y += target.y - i_ghost_0_position.y;

				break;
			}
			case 3: //The orange gohst will chase Pacman until it gets close to him. Then it'll switch to the scatter mode.
			{
				//Using the Pythagoras' theorem again.
				if (CELL_SIZE * GHOST_3_CHASE <= sqrt(pow(position.x - i_pacman_position.x, 2) + pow(position.y - i_pacman_position.y, 2)))
				{
					target = i_pacman_position;
				}
				else
				{
					target = { 0, CELL_SIZE * (MAP_HEIGHT - 1) };
				}
			}
			}
		}
	}
}




Position Ghost::get_position()
{
	return position;
}


float Ghost::get_target_distance(unsigned char i_direction)
{
	short x = position.x;
	short y = position.y;

	//We'll imaginarily move the gohst in a given direction and calculate the distance to the target.
	switch (i_direction)
	{
	case 0:
	{
		x += GHOST_SPEED;

		break;
	}
	case 1:
	{
		y -= GHOST_SPEED;

		break;
	}
	case 2:
	{
		x -= GHOST_SPEED;

		break;
	}
	case 3:
	{
		y += GHOST_SPEED;
	}
	}

	//I used the Pythagoras' theorem.
	//Because I know math.
	//Are you impressed?
	return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}



void Ghost::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman)
{
	bool move = 0;
	unsigned char speed = GHOST_SPEED;
	//Here the gohst starts and stops being frightened.
	
	if (i_pacman.get_energizer_timer() == ENERGIZER_DURATION)
	{
		frightened_mode = 1;
		frightened_speed_timer = GHOST_FRIGHTENED_SPEED;
		been_eaten = 0;
	}
	
	else if (frightened_mode == 0 && i_pacman.get_energizer_timer() > 0 && been_eaten == 0)
	{
		frightened_mode = 1;
		frightened_speed_timer = GHOST_FRIGHTENED_SPEED;
	}
	else if (i_pacman.get_energizer_timer() > 0 && been_eaten == 1)
	{
		frightened_mode = 0;
	}
	else if (i_pacman.get_energizer_timer() == 0)
	{
		frightened_mode = 0;
		been_eaten = 0;
	}


	//I used the modulo operator in case the gohst goes outside the grid.
	if (2 == frightened_mode && 0 == position.x % GHOST_ESCAPE_SPEED && 0 == position.y % GHOST_ESCAPE_SPEED)
	{
		speed = GHOST_ESCAPE_SPEED;
	}


	// Update the target cell to chase Pacman.
	update_target(i_pacman.get_direction(), i_ghost_0.get_position(), i_pacman.get_position());

	// Check for collisions with walls and determine available directions.
	std::array<bool, 4> walls{};
	walls[0] = map_collision(0,0, speed + position.x, position.y, i_map);
	walls[1] = map_collision(0,0, position.x, position.y - speed, i_map);
	walls[2] = map_collision(0,0, position.x - speed, position.y, i_map);
	walls[3] = map_collision(0,0, position.x, speed + position.y, i_map);

	//If this is greater than 1, that means that the ghost has reached the intersection.
	//We don't consider the way back as an available way.
	unsigned char available_ways = 0;
	

	if (frightened_mode != 1)
	{
		//I used 4 because using a number between 0 and 3 will make the ghost move in a direction it can't move.
		unsigned char optimal_direction = 4;

		move = 1;

		for (unsigned char a = 0; a < 4; a++)
		{
			//Ghosts can't turn back! (Unless they really have to)
			if (a == (2 + direction) % 4)
			{
				continue;
			}
			else if (walls[a] == false)
			{
				if (optimal_direction == 4)
				{
					optimal_direction = a;
				}

				available_ways++;

				if (get_target_distance(a) < get_target_distance(optimal_direction))
				{
					//The optimal direction is the direction that's closest to the target.
					optimal_direction = a;
				}
			}
		}

		if (available_ways > 1)
		{
			direction = optimal_direction;
		}

		else if (4 == optimal_direction)
		{
			direction = (2 + direction) % 4;
		}

		else
		{
			direction = optimal_direction;
		}

	}

	else
	{
		//I used rand() because I figured that we're only using randomness here, and there's no need to use a whole library for it.
		unsigned char random_direction = rand() % 4;

		if (0 == frightened_speed_timer)
		{
			move = 1;

			frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

			for (unsigned char a = 0; a < 4; a++)
			{
				//They can't turn back even if they're frightened.
				if (a == (2 + direction) % 4)
				{
					continue;
				}
				else if (0 == walls[a])
				{
					available_ways++;
				}
			}

			if (0 < available_ways)
			{
				while (1 == walls[random_direction] || random_direction == (2 + direction) % 4)
				{
					//We keep picking a random direction until we can use it.
					random_direction = rand() % 4;
				}

				direction = random_direction;
			}
			else
			{
				//If there's no other way, it turns back.
				direction = (2 + direction) % 4;
			}
		}
		else
		{
			move = 0;
			frightened_speed_timer--;
		}
	}

	if (move == 1)
	{
		switch (direction)
		{
			case 0:
			{
				position.x += speed;
				break;
			}
			case 1:
			{
				position.y -= speed;
				break;
			}
			case 2:
			{
				position.x -= speed;
				break;
			}
			case 3:
			{
				position.y += speed;
			}

		}

		//Warping.
		//When the gohst leaves the map, we move it to the other side.
		if (position.x < -CELL_SIZE / 2)
			{
				position.x = CELL_SIZE * MAP_WIDTH - speed;
			}
		else if (position.x >= CELL_SIZE * MAP_WIDTH)
			{
				position.x = speed - CELL_SIZE/2;
			}


		if (pacman_collision(i_pacman.get_position()))
		{
			if (frightened_mode == 0)
			{
				i_pacman.set_dead(1);
			}
			else
			{
				use_door = 1;
				frightened_mode = 2;
				target = home;
			}
		}

	}
} 

