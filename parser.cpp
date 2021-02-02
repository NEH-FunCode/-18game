#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

using namespace std;

Parser::Parser()
{

}

void Parser::createGridFromFile(char* pathfile, int** grid, int grid_size)
{

    char current_char;
    int elem;
    int ind_grid = 0;

    std::ifstream is(pathfile); // open file

    while (is.get(current_char))
    {
	if (is.eof())
        {
	    is.close();
	    break;
	}
        if (current_char >= '1' && current_char <= '9')
	{
	    elem = current_char -'0';
	    grid[ind_grid/grid_size][ind_grid%grid_size] = elem;
	    ind_grid ++;
	}
        if (current_char == '_')
        {
	    ind_grid ++; 
        }
    }
}

void Parser::printGrid(int** grid, int grid_size)
{
    for (int i=0; i<grid_size; i++)
    {
        for (int j=0; j<grid_size; j++)
        {
            std::cout << grid[i][j];
	    std::cout << " ";
        }
        std::cout << endl;
    }
}

