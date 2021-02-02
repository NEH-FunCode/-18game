#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "parser.h"
#include "solver.h"
#include "creator.h"

/* class to create a random grid with a single solution */

using namespace std;

Creator::Creator()
{

}

// takes two empty grids as input
int Creator::createRandomGrid(int** grid, int** initial_grid, int grid_size)
{

    generateRandomFilledGrid(grid, initial_grid, grid_size);
    //removeElements(...);

    return 1;    
}

// remove "n" elements from a valid filled grid "grid" of size "grid_size"
int Creator::removeElements(int** grid, int grid_size, int n)
{
    // TODO: implement this function
    return 1;    
}

int* Creator::genRandArray(int* array, int size)
{
    int cmp = 0;
    int randvalue;
    int exist = 0;
    std::random_device rd1;
    std::mt19937 mt1(rd1());
    std::uniform_real_distribution<double> randval(1, 10);
    
    while (cmp < size)
    {
	randvalue = (int)randval(mt1);
	for (int i=0; i<size; i++)
	    if (array[i] == randvalue)
		exist = 1;
	if (!exist)
	{
	    array[cmp]=randvalue;
	    cmp++;
	}
	exist = 0;
    }
}

int Creator::generateRandomFilledGrid(int** grid, int** initial_grid, int grid_size)
{
    int cmp = 0;
    int* randtable = (int*)calloc(grid_size, sizeof(int));
    genRandArray(randtable, grid_size);
    for (int i=0; i<3; i++)
	for (int j=0; j<3; j++)
	{
	    grid[i][j] = randtable[cmp];
	    cmp++;
	}
    cmp = 0;

    for (int i=0; i<grid_size; i++)
	randtable[i] = 0;

    genRandArray(randtable, grid_size);

    for (int i=3; i<6; i++)
	for (int j=3; j<6; j++)
	{
	    grid[i][j] = randtable[cmp];
	    cmp++;
	}
    cmp = 0;

    for (int i=0; i<grid_size; i++)
	randtable[i] = 0;

    genRandArray(randtable, grid_size);

    for (int i=6; i<9; i++)
	for (int j=6; j<9; j++)
	{
	    grid[i][j] = randtable[cmp];
	    cmp++;
	}

    for (int i=0; i<grid_size; i++)
        for (int j=0; j<grid_size; j++)
	    initial_grid[i][j] = grid[i][j];

    Solver solver(1);
    solver.solveGrid(grid, initial_grid, grid_size);

}

