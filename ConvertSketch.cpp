#pragma once
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "ConvertSketch.h"
#include "Pacman.h"
#include "Ghost.h"

using std::array;
using std::string;


std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& i_map_sketch, array<Position, 4>& i_ghost_positions, Pacman& i_pacman)
{
	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

	for (unsigned char a = 0; a < MAP_HEIGHT; a++)
	{
		for (unsigned char b = 0; b < MAP_WIDTH; b++)
		{
			switch (i_map_sketch[a][b])
			{
			case '#':
			{
				output_map[b][a] = Cell::Wall;
				break;
			}
			case 'P':
			{
				i_pacman.set_position(CELL_SIZE * b, CELL_SIZE * a);
				output_map[b][a] = Cell::Empty;
				break;
			}
			case ' ':
			{
				output_map[b][a] = Cell::Empty;
				break;

			}
			case '.':
			{
				output_map[b][a] = Cell::Pellet;
				break;

			}
			case '=':
			{
				output_map[b][a] = Cell::Door;
				break;
			}

			case '0':
			{
				i_ghost_positions[0].x = CELL_SIZE * b;
				i_ghost_positions[0].y = CELL_SIZE * a;
				output_map[b][a] = Cell::Empty;

				break;
			}
			case '1':
			{
				i_ghost_positions[1].x = CELL_SIZE * b;
				i_ghost_positions[1].y = CELL_SIZE * a;
				output_map[b][a] = Cell::Empty;

				break;
			}
			case '2':
			{
				i_ghost_positions[2].x = CELL_SIZE * b;
				i_ghost_positions[2].y = CELL_SIZE * a;
				output_map[b][a] = Cell::Empty;
				break;
			}
			case '3':
			{
				i_ghost_positions[3].x = CELL_SIZE * b;
				i_ghost_positions[3].y = CELL_SIZE * a;
				output_map[b][a] = Cell::Empty;
				break;
			}
			case 'o':
			{
				output_map[b][a] = Cell::Energizer;
				break;
			}
			}
			}
		}

		return output_map;
	}
