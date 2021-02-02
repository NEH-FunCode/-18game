#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "parser.h"
#include "solver.h"
#include "creator.h"

using namespace std;

void usage()
{
    std::cout <<"Usage: ./sudoku -s filename for solving"<< endl;
    std::cout <<"Usage: ./sudoku -g for generating a random grid to solve"<< endl;
    std::cout <<"Usage: ./sudoku -c filename to know if the grid has a single solution, or more"<< endl;
}

int main(int argc, char* argv[])
{

    if (argc < 2 || argc > 3)
    {
	usage();
	exit(0);
    }

    int genmode = 0;
    int countmode = 0;
    int solvemode = 0;

    char* pathfile;

    char* opt = argv[1];

    std::string count ("-c");
    std::string gen ("-g");
    std::string solve ("-s");

    if (gen.compare(opt) == 0)
	genmode = 1;
    else if (count.compare(opt) == 0)
	countmode = 1;
    else if (solve.compare(opt) == 0)
	solvemode = 1;
    else
    {
	usage();
	exit(0);
    }
    
    if (!genmode)
    	pathfile = argv[2];

    // init variables used for solving and generating
    int grid_size = 9;

    int** grid = (int**)malloc(sizeof(int*)*grid_size);
    for (int i = 0; i<grid_size; i++)
    {
        grid[i] = (int*)calloc(grid_size, sizeof(int));
    }

    // copy of initial grid, will not be changed, useful for solving (or generating)
    int** initial_grid = (int**)malloc(grid_size*sizeof(int*));
    for (int i = 0; i<grid_size; i++)
    {
        initial_grid[i] = (int*)calloc(grid_size, sizeof(int));
    }

    Parser parser;

    if (countmode)
    {
	Solver solver(1);
        parser.createGridFromFile(pathfile, grid, grid_size);
        parser.createGridFromFile(pathfile, initial_grid, grid_size);
        std::cout << endl << "The initial sudoku grid (0 states for empty square) :"<< endl;
        parser.printGrid(grid, grid_size);
        std::cout << endl;
	std::cout <<"Has the grid more than one solution (1 for y, 0 for n) ? : "<< solver.moreThanOneSol(grid, initial_grid, grid_size) << endl;
    }

    if (solvemode)
    {
	Solver solver(1);
        parser.createGridFromFile(pathfile, grid, grid_size);
        parser.createGridFromFile(pathfile, initial_grid, grid_size);
        std::cout << endl << "The initial sudoku grid (0 states for empty square) :"<< endl;
        parser.printGrid(grid, grid_size);
        std::cout << endl;
	solver.solveGrid(grid, initial_grid, grid_size);
	std::cout <<"The grid solved : " << endl;
	parser.printGrid(grid, grid_size);
    }

    if (genmode)
    {
	// TODO : add argument (easy, medium, hard) to know how many elements should be removed from the fully generated valid random grid
	std::cout <<"For now it only generates valid random filled grid :" << endl;
	Creator creator;
        creator.createRandomGrid(grid, initial_grid, grid_size);
	std::cout <<"The generated filled random grid :" << endl;
	parser.printGrid(grid, grid_size);
    }
    return 0;
}
