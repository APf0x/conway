#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;



float alivex(float x){
    int temp;
    temp = x/20;
    temp = floor(temp);
    x = temp * 20;
    return x;
}

float alivey(float y){
    int temp;
    temp = y/20;
    temp = floor(temp);
    y = temp * 20;
    return y;
}


int recompile(){
    system("g++ -c main.cpp");
    system("g++ main.o -o conway -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio");
    system("./conway");
    return 0;
}


int main(){
    float xpos, ypos;
    float clicx{};
    float clicy{};
    int xav, yav;
    const int columns = 30;
    const int rows = 30;
    const int xtot = 20;
    const int ytot = 20;
    sf::RenderWindow window(sf::VideoMode(580, 580), "conway");
    sf::RectangleShape grid[columns][rows];

    sf::RectangleShape rectangle[xtot][ytot];

    sf::RectangleShape temp;
    temp.setFillColor(sf::Color::Black);
    
    //rectangle.setPosition(sf::Vector2f(20.f,20.f));

    for(int f = 0; f <= columns; f++){
        for(int g = 0; g <= rows; g++){
            rectangle[f][g].setOutlineColor(sf::Color::White);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::MouseMoved){
                //std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                //std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                xpos = event.mouseMove.x;
                ypos = event.mouseMove.y;
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    //std::cout << "the left button was pressed" << std::endl;
                    clicx = alivex(xpos);
                    clicy = alivey(ypos);
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::S){
                    window.close();
                    return 0;
                }
                if (event.key.code == sf::Keyboard::C){
                    window.close();
                    recompile();
                    return 0;
                }
            }
        }
        window.clear();
        sf::Vector2f cellSize(20.0f, 20.0f);

        for(int i=0;i<columns;i++){
            for(int j=0;j<rows;j++){
                grid[i][j].setSize(cellSize);
                grid[i][j].setOutlineColor(sf::Color::Blue);
                grid[i][j].setOutlineThickness(1.0f);

                grid[i][j].setPosition(i*cellSize.x, j*cellSize.y);

                window.draw(grid[i][j]);

            }
        }
        cout << "if this doesnt go further youre fucked line 95 \n";
        //rectangle.setPosition(sf::Vector2f(xpos, ypos));
        sf::Vector2f position(clicx, clicy);
        cout << "line 98 working \n";
        xav = position.x / columns;
        yav = position.y / rows;
        cout << "line 102 working\n";


        rectangle[xav][yav].setSize(cellSize);
        rectangle[xav][yav].setFillColor(sf::Color::Black);
        
        rectangle[xav][yav].setPosition(position.x, position.y);
        for(int f = 0; f < columns; f++){
            for(int g = 0; g < rows; g++){
                if(rectangle[f][g].getFillColor() == temp.getFillColor()){
                    window.draw(rectangle[f][g]);
                }
            }
        }



        cout << "line 104 i guess working \n";
        //window.draw(rectangle[xav][yav]);
        cout << "line 106 it should work \n";
        window.display();
    }
    return 0;
}