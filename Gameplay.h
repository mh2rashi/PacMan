#pragma once
#pragma once
#include <array>
#include <chrono>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "ConvertSketch.h"
#include "DrawMap.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"

using std::chrono::time_point;
using std::chrono::steady_clock;
using std::array;
using std::string;

void gameplay(sf::RenderWindow& window, array<string, MAP_HEIGHT>& map_sketch);