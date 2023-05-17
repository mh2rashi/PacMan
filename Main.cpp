
 
 //Code to generate map
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Global.h"
#include<array>
#include "Gameplay.h"
using std::vector;
using std::cout;
using std::array;

void CreateMap(sf::RenderWindow& window)
{
    // Define constants for the size of the window and the grid system.
    const int cellSize = 16 * SCREEN_RESIZE;
    const int gridSize = 21;

    sf::Vector2u newSize(gridSize * cellSize * 1.5, gridSize * cellSize); // set the new window size her
    // Set the new view for the window.
    window.setSize(newSize);

    // Create a new view for the new screen.
    sf::View newView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    // Set the new view for the window.
    window.setView(newView);


    

    // Create the grid system.
    vector<vector<sf::RectangleShape>> grid(gridSize, vector<sf::RectangleShape>(gridSize));
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
            grid[i][j].setPosition(i * cellSize, j * cellSize);
            grid[i][j].setFillColor(sf::Color::Black);
            grid[i][j].setOutlineThickness(1); // Set outline thickness to 1 pixel.
            grid[i][j].setOutlineColor(sf::Color(128, 128, 128)); // Set outline color to gray.
        }
    }

    sf::Rect<float> gridBounds(0, 0, gridSize * cellSize, gridSize * cellSize);

    // Load the font for the menu buttons.
    sf::Font font;
    font.loadFromFile("pac-font-text.ttf");

    sf::Font font1;
    font1.loadFromFile("pac-font.ttf");

    // Create the title.
    sf::Text title;
    title.setFont(font);
    title.setString("Instructions");
    title.setCharacterSize(18);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition((gridBounds.width + window.getSize().x) / 2, 50);

    // Center the title.
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f -50);

    // Create "Instruction 1"
    sf::Text Instruction1;
    Instruction1.setFont(font);
    Instruction1.setString("1.Click Left Mouse Key \n + Scroll to draw walls");
    Instruction1.setCharacterSize(12);
    Instruction1.setFillColor(sf::Color::White);
    Instruction1.setPosition(gridBounds.width + 15, 150);

    // Create "Instruction 2"
    sf::Text Instruction2;
    Instruction2.setFont(font);
    Instruction2.setString("2.Click Right Mouse Key \n + Scroll to delete walls");
    Instruction2.setCharacterSize(12);
    Instruction2.setFillColor(sf::Color::White);
    Instruction2.setPosition(gridBounds.width + 15, 200);

    // Create "Instruction 3"
    sf::Text Instruction3;
    Instruction3.setFont(font);
    Instruction3.setString("3.Press Enter button \n to visualize grid");
    Instruction3.setCharacterSize(12);
    Instruction3.setFillColor(sf::Color::White);
    Instruction3.setPosition(gridBounds.width + 15, 250);

    // Create "Instruction 4"
    sf::Text Instruction4;
    Instruction4.setFont(font);
    Instruction4.setString("4.Press Delete button \n to clear grid");
    Instruction4.setCharacterSize(12);
    Instruction4.setFillColor(sf::Color::White);
    Instruction4.setPosition(gridBounds.width + 15, 300);


    //Create the "Play Game" button.
    sf::Text playButton;
    playButton.setFont(font1);
    playButton.setString("Play Game");
    playButton.setCharacterSize(26);
    playButton.setFillColor(sf::Color::White);
    playButton.setPosition(gridBounds.width + 15, 400);


    // Calculate position of "Play Game" button.
    sf::FloatRect playBounds = playButton.getLocalBounds();
    playButton.setOrigin(playBounds.width / 2.0f, playBounds.height / 2.0f);
    playButton.setPosition(title.getPosition().x, title.getPosition().y + titleBounds.height / 2.0f + 450);


    // Create the "Previous Menu" button.
    sf::Text PreviousMenu;
    PreviousMenu.setFont(font1);
    PreviousMenu.setString("Previous Menu");
    PreviousMenu.setCharacterSize(26);
    PreviousMenu.setFillColor(sf::Color::White);
    PreviousMenu.setPosition(gridBounds.width + 15, 475);

    // Calculate position of "Quit Game" button.
    sf::FloatRect PeviousBounds = PreviousMenu.getLocalBounds();
    PreviousMenu.setOrigin(PeviousBounds.width / 2.0f, PeviousBounds.height / 2.0f);
    PreviousMenu.setPosition(title.getPosition().x, PreviousMenu.getPosition().y + playBounds.height / 2.0f + 75);

    // Output Map Sketch
    std::array<std::string, 21> map_sketch;

    // Run the main loop.
    while (window.isOpen()) {
        // Handle events.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                int x = event.mouseMove.x / cellSize;
                int y = event.mouseMove.y / cellSize;
                if (gridBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                    grid[x][y].setFillColor(sf::Color::White);
                }
            }
            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                int x = event.mouseMove.x / cellSize;
                int y = event.mouseMove.y / cellSize;
                if (gridBounds.contains(event.mouseMove.x, event.mouseMove.y)) {
                    grid[x][y].setFillColor(sf::Color::Black);
                }
            }
            //If user presses "Delete" we clear grid
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete) {
                for (int i = 0; i < gridSize; i++) {
                    for (int j = 0; j < gridSize; j++) {
                        grid[i][j].setFillColor(sf::Color::Black);
                    }
                }
            }
            // Check if the user clicked on the "Draw Map" button.
            if (event.mouseButton.button == sf::Mouse::Left && playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                gameplay(window, map_sketch);
            }
            // Check if the user clicked on the "Draw Map" button.
            else if (event.mouseButton.button == sf::Mouse::Left && PreviousMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                return;
            }
           
            // Check if the user clicked on the finish button "Enter"
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::vector<std::vector<std::string>> pacmanMap(gridSize, std::vector<std::string>(gridSize));
                for (int i = 0; i < gridSize; i++) {
                    for (int j = 0; j < gridSize; j++) {
                        if (grid[i][j].getFillColor() == sf::Color::White) {
                            pacmanMap[i][j] = "#";
                        }
                        else {
                            pacmanMap[i][j] = ".";
                        }
                    }
                }
                // Add Pacman and the dots.
                pacmanMap[gridSize / 2][gridSize / 2] = "P";
                for (int i = 1; i < gridSize / 2; i++) {
                    pacmanMap[gridSize / 2 + i][gridSize / 2] = ".";
                }
                // Add Ghosts
                pacmanMap[4][10] = "0";
                pacmanMap[5][9] = "1";
                pacmanMap[5][10] = "2";
                pacmanMap[5][11] = "3";
                //// Print out the final map.
                //for (int i = 0; i < gridSize; i++) {
                //    for (int j = 0; j < gridSize; j++) {
                //        std::cout << pacmanMap[i][j];
                //    }
                //    std::cout << std::endl;
                //}
                // Create the array `map_sketch` based on `pacmanMap`.
                int const MAP_HEIGHT = pacmanMap.size();
                int const MAP_WIDTH = pacmanMap[0].size();
                
                for (int i = 0; i < MAP_HEIGHT; i++) {
                    std::string line;
                    for (int j = 0; j < MAP_WIDTH; j++) {
                        line += pacmanMap[i][j];
                    }
                    map_sketch[i] = line;
                }
                // Print out the final map.
                for (int i = 0; i < MAP_HEIGHT; i++) {
                    std::cout << map_sketch[i] << std::endl;
                }


            }
            // Check if the user closed the window.
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
 


        window.clear();
        
        
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                window.draw(grid[i][j]);
            }
        }
        window.draw(title);
        window.draw(Instruction1);
        window.draw(Instruction2);
        window.draw(Instruction3);
        window.draw(Instruction4);
        window.draw(playButton);
        window.draw(PreviousMenu);
        window.display();
    }

    return;
}




void secondWindow(sf::RenderWindow& window){

    array<string, MAP_HEIGHT> map_sketch = {
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
    };

    // Create a new view for the new screen.
    sf::View newView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    // Load the font for the menu buttons.
    sf::Font font;
    font.loadFromFile("pac-font.ttf");

    // Set the new view for the window.
    window.setView(newView);

    // Create the "Draw Map" button.
    sf::Text DrawMap;
    DrawMap.setFont(font);
    DrawMap.setString("Draw Map");
    DrawMap.setCharacterSize(48);
    DrawMap.setFillColor(sf::Color::White);

    // Create the "Classic Map" button.
    sf::Text ClassicMap;
    ClassicMap.setFont(font);
    ClassicMap.setString("Classic Map");
    ClassicMap.setCharacterSize(48);
    ClassicMap.setFillColor(sf::Color::White);

    // Create the "Previous Menu" button.
    sf::Text PreviousMenu;
    PreviousMenu.setFont(font);
    PreviousMenu.setString("Previous Menu");
    PreviousMenu.setCharacterSize(48);
    PreviousMenu.setFillColor(sf::Color::Yellow);

    // Create the title.
    sf::Text title;
    title.setFont(font);
    title.setString("PAC-MAN");
    title.setCharacterSize(72);
    title.setFillColor(sf::Color::Yellow);

    // Center the title.
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2.0f, 100.0f);

    // Center the buttons around the title.
    sf::FloatRect DrawMapBounds = DrawMap.getLocalBounds();
    DrawMap.setOrigin(DrawMapBounds.width / 2.0f, DrawMapBounds.height / 2.0f);
    DrawMap.setPosition(window.getSize().x / 2.0f, title.getPosition().y + titleBounds.height / 2.0f + 85.0f);

    sf::FloatRect ClassicMapBounds = ClassicMap.getLocalBounds();
    ClassicMap.setOrigin(ClassicMapBounds.width / 2.0f, ClassicMapBounds.height / 2.0f);
    ClassicMap.setPosition(window.getSize().x / 2.0f, DrawMap.getPosition().y + DrawMapBounds.height / 2.0f + 60.0f);

    sf::FloatRect PreviousMenuBounds = PreviousMenu.getLocalBounds();
    PreviousMenu.setOrigin(PreviousMenuBounds.width / 2.0f, PreviousMenuBounds.height / 2.0f);
    PreviousMenu.setPosition(window.getSize().x / 2.0f, ClassicMap.getPosition().y + ClassicMapBounds.height / 2.0f + 85.0f);



    // Process events for the new screen.
    while (window.isOpen())
    {
        // Process events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Check if the user clicked on the "Draw Map" button.
                    if (DrawMap.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        CreateMap(window);
                         
                    }
                    // Check if the user clicked on the "Draw Map" button.
                    else if (ClassicMap.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        gameplay(window, map_sketch);
                        sf::Vector2u newSize(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, CELL_SIZE * MAP_HEIGHT * SCREEN_RESIZE); // set the new window size her
                        window.setSize(newSize);
                        sf::View newView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
                        window.setView(newView);
                    }
                    else if (PreviousMenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        return;
                    }
                }
                break;
            }
        }

        // Clear the window.
        window.clear(sf::Color::Black);

        // Draw the buttons and their perimeter.
        window.draw(title);
        window.draw(ClassicMap);
        window.draw(DrawMap);
        window.draw(PreviousMenu);

        // Display the window.
        window.display();
    }

    
};

int main()
{
    // Create the window.
    sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, CELL_SIZE * MAP_HEIGHT * SCREEN_RESIZE), "Pacman");

    // Load the font for the menu buttons.
    sf::Font font;
    font.loadFromFile("pac-font.ttf");

    // Create the "Play Game" button.
    sf::Text playButton;
    playButton.setFont(font);
    playButton.setString("Play Game");
    playButton.setCharacterSize(48);
    playButton.setFillColor(sf::Color::White);

    // Create the "Quit Game" button.
    sf::Text quitButton;
    quitButton.setFont(font);
    quitButton.setString("Quit Game");
    quitButton.setCharacterSize(48);
    quitButton.setFillColor(sf::Color::White);

    // Create the title.
    sf::Text title;
    title.setFont(font);
    title.setString("PAC-MAN");
    title.setCharacterSize(72);
    title.setFillColor(sf::Color::Yellow);

    // Center the title.
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(window.getSize().x / 2.0f, 100.0f);

    // Center the buttons around the title.
    sf::FloatRect playButtonBounds = playButton.getLocalBounds();
    playButton.setOrigin(playButtonBounds.width / 2.0f, playButtonBounds.height / 2.0f);
    playButton.setPosition(window.getSize().x / 2.0f, title.getPosition().y + titleBounds.height / 2.0f + 85.0f);

    sf::FloatRect quitButtonBounds = quitButton.getLocalBounds();
    quitButton.setOrigin(quitButtonBounds.width / 2.0f, quitButtonBounds.height / 2.0f);
    quitButton.setPosition(window.getSize().x / 2.0f, playButton.getPosition().y + playButtonBounds.height / 2.0f + 60.0f);


    // Main loop.
    while (window.isOpen())
    {
        // Process events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Check if the user clicked on the "Play Game" button.
                    if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        secondWindow(window);
                    }
                    // Check if the user clicked on the "Quit Game" button.
                    else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                    {
                        window.close();
                    }
                }
                break;
            }
        }

        // Clear the window.
        window.clear(sf::Color::Black);

        // Draw buttons & title.
        window.draw(playButton);
        window.draw(quitButton);
        window.draw(title);

        // Display the window.
        window.display();
    }

    return 0;
}



