#pragma once
#include "Gameplay.h"


void gameplay(sf::RenderWindow& window, array<string, MAP_HEIGHT>& map_sketch)
{

	//Is the game won?
	bool game_won = 0;

	unsigned lag = 0;

	time_point<steady_clock> previous_time;

	/*array<string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #..#.....P.....#..# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #o######.#.######o# ",
		" #.................# ",
		" ################### "
	};*/


	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	
	
	sf::Event event;


	//window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT)));

	sf::Vector2u newSize(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, CELL_SIZE * MAP_HEIGHT * SCREEN_RESIZE); // set the new window size her
	window.setSize(newSize);
	sf::View newView(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, CELL_SIZE * MAP_HEIGHT));
	window.setView(newView);

	Pacman pacman;

	std::array<Position, 4> ghost_positions;
	GhostManager ghost_manager;

	map = convert_sketch(map_sketch, ghost_positions, pacman);

	ghost_manager.reset(ghost_positions);

	previous_time = steady_clock::now();

	while (window.isOpen())
	{

		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);

		while (FRAME_DURATION <= lag)
		{

			lag -= FRAME_DURATION;

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
					{
						window.close();
						break;
					}
					case sf::Event::KeyPressed:
					{
						if (event.key.code == sf::Keyboard::Escape)
						{
							return;
						}
						break;
					}
				}
			}


			if (0 == game_won && 0 == pacman.get_dead())
			{
				game_won = 1;

				pacman.update(map);

				ghost_manager.update(map, pacman);

				//We're checking every cell in the map.
				for (const std::array<Cell, MAP_HEIGHT>& column : map)
				{
					for (const Cell& cell : column)
					{
						if (Cell::Pellet == cell) //And if at least one of them has a pellet.
						{
							game_won = 0; //The game is not yet won.

							break;
						}
					}

					if (0 == game_won)
					{
						break;
					}
				}
			}

			else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Restarting the game.
			{
				game_won = 0;

				map = convert_sketch(map_sketch, ghost_positions, pacman);

				ghost_manager.reset(ghost_positions);
				
				pacman.reset();
			}



			if (FRAME_DURATION > lag)
			{
				window.clear();

				if (0 == pacman.get_dead() && game_won == 0)
				{
					draw_map(map, window);
					ghost_manager.draw(window);

				}

				
				pacman.draw(window);

				window.display();
			}

		}
	}

}
 