#include <iostream>
#include <vector>
#include <unistd.h> 
using namespace std;

//***
// the rules of conway
// 1) any live cell with fewer than two live neighbours dies, as if by underpopulation.
// 2) any live celle with two or three live neighbours lives on the next generation
// 3) any live cell with more than three live neighbours dies, as if by overpopulation
// 4) any dead cell with exactly 3 live neighbours becomes a live cell, as if by reproduction. */

void clearScreen(){
    std::cout << "\033[2J\033[1;H";
}



void print_vector(const std::vector<std::vector<bool>> &grid){
        for (auto &row : grid){
        for (bool cell : row){
            std::cout << std::boolalpha << ((cell) ? "1" : "0") << " ";
        }
        std::cout << endl;
    }
}


std::vector<std::vector<bool>> tick(std::vector<std::vector<bool>> &grid){
    int neighbours = 0;
    std::vector<std::vector<bool>> next_grid = grid;
    for(int i = 1; i < grid.size()-1; i++){
        for(int j = 1; j < grid[i].size()-1; j++){
            // im not doing two extra for loops becuase i dont feel like it even if everyone keep on telling me to, spaghetti code never hurt anyone.
            neighbours = 0;
            neighbours += grid[i][j-1];
            neighbours += grid[i][j+1];
            neighbours += grid[i-1][j];
            neighbours += grid[i+1][j];
            neighbours += grid[i-1][j-1];
            neighbours += grid[i+1][j-1];
            neighbours += grid[i-1][j+1];
            neighbours += grid[i+1][j+1];

            if (neighbours < 2){
                next_grid[i][j] = 0;
            }
            if (grid[i][j] != 0 && (neighbours == 3 || neighbours ==2)){
                next_grid[i][j] = grid[i][j]; 
            }
            if (neighbours > 3){
                next_grid[i][j] = 0;
            }
            if (grid[i][j] == 0 && neighbours == 3){
             
               next_grid[i][j] = 1;
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

    int grid_size = 12;
    std::vector<std::vector<bool>> grid;
    grid = {
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}
    };
    // i forgot completely c++ im actually surprised i remember this much its as if my hands know this code better than me
    // ts is weirding me out its like knowing without knowing
    // shoutout chat gpt  for helping me out on the for loop never knew for loops didnt need the standard 3 parameters, makes it look fancy, plus i learned a new thing


    print_vector(grid);
    while(true){
        grid = tick(grid);
        clearScreen();
        print_vector(grid);
        usleep(200000);
        
    }
    // we did it hurray now i can go back and doom scroll.
    // next i need to create the sfml version that i started back in like 2022 but never finished because of school
    return 0;
}