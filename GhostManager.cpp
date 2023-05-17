#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"


GhostManager::GhostManager() :
	current_wave(0),
	wave_timer(LONG_SCATTER_DURATION),
	ghosts{Ghost(0, sf::Color(255, 0, 0)), Ghost(1,sf::Color(255, 182, 255)),
	Ghost(2,sf::Color(0, 255, 255)), Ghost(3, sf::Color(255, 182, 85))}
{}

void GhostManager::draw(sf::RenderWindow& i_window)
{
	for (Ghost& ghost : ghosts)
	{
		ghost.draw(i_window);
	}
}


void GhostManager::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman)
{

	if (0 == i_pacman.get_energizer_timer()) //We won't update the wave timer when Pacman is energized.
	{
		if (wave_timer == 0)
		{
			if (current_wave < 7)
			{
				current_wave++;

				for (Ghost& ghost : ghosts)
				{
					ghost.switch_mode();
				}
			}

			//I took the rules from the website.
			if (current_wave % 2 == 1)
			{
				wave_timer = CHASE_DURATION;
			}
			else if (current_wave == 2)
			{
				wave_timer = LONG_SCATTER_DURATION;
			}
			else
			{
				wave_timer = SHORT_SCATTER_DURATION;
			}
		}
		else
		{
			wave_timer--;
		}

	}
	
	
	for (Ghost& ghost : ghosts)
	{
		ghost.update(i_map, ghosts[0], i_pacman);
	}
}



void GhostManager::reset(const std::array<Position, 4>& i_ghost_positions)
{
	current_wave = 0;

	for (auto i = 0; i < 4; i++)
	{
		ghosts[i].set_position(i_ghost_positions[i].x, i_ghost_positions[i].y);

	}


	for (Ghost& ghost : ghosts)
	{
		ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
	}
}