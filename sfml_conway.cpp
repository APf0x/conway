// the original version was written is sfml 2 it was outdated and pretty badly written its a shame taht i half assed it it couldve been a nice project
// since i half assed it once i wont do it again this has been done trought at my best skill, with minimal ai, exept when in studying or if i encounter bugs, all of it is written by me.
// i know it does not matter to result oriented people but results are not everything, if the goal is the experience everything is a win.
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>


const int screen_size = 800;

// i just copied it from the console version i lowk forgot what it even does, idk how i was able to build this w out ai
// nvm i had to re do it because i wanted to
void print_vector(std::vector<bool> grid, int grid_size){
    for (int y = 0; y < grid_size; ++y) {
        for (int x = 0; x < grid_size; ++x) {
                std::cout << std::boolalpha << ((grid[y * grid_size + x]) ? "1" : "0") << " ";
            }
        std::cout << std::endl;
        }
    std::cout << std::endl;
}


std::vector<bool> tick(std::vector<bool> grid, int grid_size){
    int neighbours = 0;
    std::vector<bool> next_grid = grid;
    for(int y = 1; y < grid_size-1; y++){
        for(int x = 1; x < grid_size-1; x++){
            // im not doing two extra for loops becuase i dont feel like it even if everyone keep on telling me to, spaghetti code never hurt anyone.
            neighbours = 0;
            neighbours += grid[y * grid_size + x + 1];
            neighbours += grid[y * grid_size + x - 1];
            neighbours += grid[(y-1) * grid_size + x + 1];
            neighbours += grid[(y-1) * grid_size + x];
            neighbours += grid[(y-1) * grid_size + x -1];
            neighbours += grid[(y+1) * grid_size + x + 1];
            neighbours += grid[(y+1) * grid_size + x];
            neighbours += grid[(y+1) * grid_size + x - 1];      

            if (neighbours < 2){
                next_grid[y * grid_size + x ] = 0;
            }
            if (grid[y * grid_size + x ] != 0 && (neighbours == 3 || neighbours ==2)){
                next_grid[y * grid_size + x ] = grid[y * grid_size + x ]; 
            }
            if (neighbours > 3){
                next_grid[y * grid_size + x ] = 0;
            }
            if (grid[y * grid_size + x ] == 0 && neighbours == 3){
             
               next_grid[y * grid_size + x] = 1;
            }
            // found this other more elegant way to do it actually makes a whole lot more of senso doing it like this butt ill keep both versions since i came up with the one above first
            // it would feel like cheating to remove it even if less elegant it is my solution
            //if (grid[i][j]){
            //    next_grid[i][j] = (neighbours == 2 || neighbours == 3);
            //}else{
            //    next_grid[i][j] = neighbours == 3;
            //}
        }   
    }
    return next_grid;
}

int main(){
    int grid_size = 100; // pls lets make everything a square.
    int xcord, ycord; // dont mind it youll see later why i put it

    unsigned int controls_bar = 30; // use even numbers i dont feel like handling floating point logic


    // so ai is telling me that to optimize it its better to have a linear vector, cool but i still like being able to understand my own code
    // well im actually exaerating it this code is pretty simple to understand, simply people give functions scary names that make no sense
    std::vector<bool> grid (grid_size*grid_size, 0);

    sf::RenderWindow window(sf::VideoMode({screen_size, screen_size+controls_bar}), "My window");
    window.setFramerateLimit(60); 

    sf::Clock simulationClock;
    float updateInterval = 0.1f;
    float speedMultiplier = 1.0f;



    bool isRunning = false;

    //gotta play with the position to get it right if you were to change screen size
    sf::CircleShape start((controls_bar-4)/2, 3);
    start.setPosition({controls_bar, screen_size+2});
    start.setRotation(sf::degrees(90));

    sf::RectangleShape going({controls_bar-10, controls_bar-10});
    going.setPosition({10, screen_size+5});

    // yet another un necessary tool
    sf::RectangleShape sliderTrack({200, 5});
    sliderTrack.setPosition({200, 18});
    sliderTrack.setFillColor(sf::Color(100, 100, 100));
    
    sf::RectangleShape sliderKnob({10, 20});
    sliderKnob.setPosition({200 + speedMultiplier * 180, 10}); 
    sliderKnob.setFillColor(sf::Color::White);



    
    std::vector<sf::RectangleShape> cells;

    std::vector<sf::Vertex> vertical = {};
    std::vector<sf::Vertex> horizontal = {};

    float separator = float(screen_size)/float(grid_size);


    for(float i = 0; i<=screen_size; i+=separator){
        vertical.push_back(sf::Vertex{sf::Vector2f(i, 0.f), sf::Color(255,255,255,100)});
        vertical.push_back(sf::Vertex{sf::Vector2f(i, 800.f), sf::Color(255,255,255,100)});
    }

    for(float i = 0; i<=screen_size; i+=separator){
        horizontal.push_back(sf::Vertex{sf::Vector2f(0.f, i), sf::Color(255,255,255,100)});
        horizontal.push_back(sf::Vertex{sf::Vector2f(800.f, i), sf::Color(255,255,255,100)});
    }

        

    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f worldPos = window.mapPixelToCoords(mouseButtonPressed->position);
                    // std::cout << "mouse x: " << int(worldPos.x)/separator << std::endl;
                    // std::cout << "mouse y: " << int(worldPos.y)/separator << std::endl;
                    xcord = int(worldPos.x)/separator;

                    ycord = int(worldPos.y)/separator;
                    if(xcord > 0 && xcord < grid_size-1 && ycord > 0 && ycord < grid_size-1){
                        int pos = ycord*grid_size+xcord;
                        grid[pos] = !grid[pos];
                        print_vector(grid, grid_size);
                    }
                    if (start.getGlobalBounds().contains(worldPos)) {
                        isRunning = !isRunning;
                    }
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if (keyPressed->scancode == sf::Keyboard::Scan::Space){
                    isRunning = !isRunning;
                    grid = tick(grid, grid_size);
                }
            }

        } 


        
        cells.clear();
        cells.reserve(grid_size*grid_size);

        for (int y = 1; y < grid_size; ++y) {
            for (int x = 1; x < grid_size; ++x) {
                if (grid[y * grid_size + x]) {
                    sf::RectangleShape square({separator, separator});
                    square.setPosition({x * separator, y * separator});
                    cells.push_back(std::move(square));
                }
            }
        }
        window.clear();
        if (isRunning) {
            float currentInterval = updateInterval / speedMultiplier;
            if (simulationClock.getElapsedTime().asSeconds() >= currentInterval) {
                grid = tick(grid, grid_size);
                simulationClock.restart();
            }
            window.draw(going);
        }else{
            window.draw(start);
        }
        for (const auto& shape : cells) {
            window.draw(shape);
        }
        
        window.draw(vertical.data(), vertical.size(), sf::PrimitiveType::Lines);
        window.draw(horizontal.data(), horizontal.size(), sf::PrimitiveType::Lines);

        window.display();
    }

}