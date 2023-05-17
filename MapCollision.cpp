#include <array>
#include <cmath>
#include <iostream>

#include "Global.h"
#include "MapCollision.h"
using std::array;

int map_collision(bool i_collect_energizer, bool i_collect_pellets, short i_x, short i_y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	bool output = 0;

	//Getting the exact position.
	float cell_x = i_x / static_cast<float>(CELL_SIZE);
	float cell_y = i_y / static_cast<float>(CELL_SIZE);

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
			if (Cell::Wall == i_map[x][y])
			{
				output = 1;
			}
			else
			{
				if (i_collect_pellets == 1 && Cell::Pellet == i_map[x][y] &&
					abs(cell_x - x - 0.3f) < 0.5f &&
					abs(cell_y - y - 0.3f) < 0.5f)
				{
					i_map[x][y] = Cell::Empty;
				}
				//// Here pacman collides with an energizer
				//else if (i_collect_energizer == 1 && Cell::Energizer == i_map[x][y] && // When pacman eats the energizer
				//	abs(cell_x - x - 0.3f) < 0.5f &&
				//	abs(cell_y - y - 0.3f) < 0.5f)
				//{

				//	i_map[x][y] = Cell::Empty;
				//	output = 2;
				//}
			}
		}
	}

	return output;
}
