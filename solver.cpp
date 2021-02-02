#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "solver.h"
#include "parser.h"

using namespace std;

Solver::Solver(int rec_status)
{
    rec_status = rec_status;
}

void Solver::setStatus(int status)
{
    rec_status = status;
}

int Solver::getStatus()
{
    return rec_status;
}

void Solver::solveGrid(int** grid, int** initial_grid, int grid_size)
{
    if (!isGridValid(grid, grid_size))
    {
	std::cout << "Invalid grid !" << endl <<endl;
	exit(0);
    }
    int firstempty = firstEmpty(initial_grid, grid_size);
    solveGridRec(grid, initial_grid, grid_size, firstempty);
}

// returns -1 if there is no sol to the grid in input, 0 for one solution and 1 if there are more than one solution
int Solver::moreThanOneSol(int** grid, int** initial_grid, int grid_size)
{

    if (!isGridValid(grid, grid_size))
    {
	std::cout << "Invalid grid !" << endl <<endl;
	exit(0);
    }


    Parser parser;
    int exists = 0;
    int ret_rec = 1;
    int indfirstempty = firstEmpty(initial_grid, grid_size);

    // finding first sol if exist
    solveGridRec(grid, initial_grid, grid_size, indfirstempty);


    if (getStatus() == -1)
	return -1; // no sol


    int lastempty = lastEmpty(initial_grid, grid_size);

    while (grid[lastempty/grid_size][lastempty%grid_size] == grid_size)
    {
	lastempty = previousEmpty(grid, grid_size, lastempty);
    }


    int vallastempty = grid[lastempty/grid_size][lastempty%grid_size];

    resetGrid(grid, initial_grid, grid_size);


    for (int k=vallastempty+1; k <= grid_size; k++)
	if (!existsInLine(grid, grid_size, k, lastempty/grid_size) && !existsInColumn(grid, grid_size, k, lastempty%grid_size) && !existsInSquare(grid, grid_size, k, lastempty/grid_size, lastempty%grid_size))
	{
	    grid[lastempty/grid_size][lastempty%grid_size] = k;
	    exists = 1;
	    break;
	}
    
    if (!exists)
	return 0; // only one sol


    solveGridRec(grid, initial_grid, grid_size, indfirstempty);

    if (getStatus() == 1) // 2nd sol found
    {
	return 1;
    }

    return 0;
}

int Solver::solveGridRec(int** grid, int** initial_grid, int grid_size, int indelem)
{
    Parser parser;

    if (getStatus() == -1)
	return -1;    


    int exists = 0;
    int elem = grid[indelem/grid_size][indelem%grid_size]+1;

    if (elem > grid_size) // go back further
    {
	grid[indelem/grid_size][indelem%grid_size] = 0;
	
	int indprevious = previousEmpty(initial_grid, grid_size, indelem);

	if (indprevious == -1)
	{
	    setStatus(-1);
	    return -1; // error : no sol
	}
	else
            solveGridRec(grid, initial_grid, grid_size, indprevious);
    }


    for (int k=elem; k<=grid_size; k++)
    {
	if (!existsInLine(grid, grid_size, k, indelem/grid_size) && !existsInColumn(grid, grid_size, k, indelem%grid_size) && !existsInSquare(grid, grid_size, k, indelem/grid_size, indelem%grid_size))
	{
	    grid[indelem/grid_size][indelem%grid_size] = k;
	    exists = 1;
	    break;
	}
    }

    if (gridIsFull(grid, grid_size)) // a sol has been found
    {
	return 1; // success
    }
    
    if (exists)
    {
	int nextelem = nextEmpty(initial_grid, grid_size, indelem);
	if (nextelem == -1)
	{
	    setStatus(-1);
	    return -1; // error
	}
	
        else
	{
	    solveGridRec(grid, initial_grid, grid_size, nextelem);
	}
    }

	    
    else
    {
	grid[indelem/grid_size][indelem%grid_size] = 0;
	int indprevious = previousEmpty(initial_grid, grid_size, indelem);
	if (indprevious == -1)
	{
	    setStatus(-1);
	    return -1; // error : no sol
	}
	    
	else
	{
	    solveGridRec(grid, initial_grid, grid_size, indprevious);
	}  
    }
}


int Solver::existsInLine(int** grid, int grid_size, int elem, int i)
{
    for (int j=0; j<grid_size; j++)
    {
	if (grid[i][j] == elem)
	{
	    return 1;
	}
    }
    return 0;
}


int Solver::existsInColumn(int** grid, int grid_size, int elem, int j)
{
    for (int i=0; i<grid_size; i++)
    {
	if (grid[i][j] == elem)
	{
	    return 1;
	}
    }
    return 0;
}


int Solver::existsInSquare(int** grid, int grid_size, int elem, int i, int j)
{   
    // top left square
    if (i < 3 && j < 3)
    {
	for (int m = 0; m < 3; m++)
	{
	    for (int n = 0; n < 3; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // top middle square
    if (i < 3 && j < 6)
    {
	for (int m = 0; m < 3; m++)
	{
	    for (int n = 3; n < 6; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }
    
    // top right square
    if (i < 3 && j < 9)
    {
	for (int m = 0; m < 3; m++)
	{
	    for (int n = 6; n < 9; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // middle left square
    if (i < 6 && j < 3)
    {
	for (int m = 3; m < 6; m++)
	{
	    for (int n = 0; n < 3; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // middle middle square
    if (i < 6 && j < 6)
    {
	for (int m = 3; m < 6; m++)
	{
	    for (int n = 3; n < 6; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // middle right square
    if (i < 6 && j < 9)
    {
	for (int m = 3; m < 6; m++)
	{
	    for (int n = 6; n < 9; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // bottom left square
    if (i < 9 && j < 3)
    {
	for (int m = 6; m < 9; m++)
	{
	    for (int n = 0; n < 3; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // bottom middle square
    if (i < 9 && j < 6)
    {
	for (int m = 6; m < 9; m++)
	{
	    for (int n = 3; n < 6; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }

    // bottom right square
    if (i < 9 && j < 9)
    {
	for (int m = 6; m < 9; m++)
	{
	    for (int n = 6; n < 9; n++)
	    {
		if (grid[m][n] == elem)
		    return 1;
	    }
	}
	return 0;
    }
}


int Solver::isEmpty(int** grid, int i, int j)
{
    if (grid[i][j] == 0)
	return 1;
    return 0;
}




int Solver::gridIsFull(int** grid, int grid_size)
{
    for (int i = 0; i < grid_size; i++)
    {
	for (int j = 0; j < grid_size; j++)
	{
	    if (grid[i][j] == 0) // found empty square
		return 0;
	}
    }
    return 1;
}


int Solver::nextEmpty(int** grid, int grid_size, int i)
{
    if (i == grid_size*grid_size-1)
	return -1;

    for (int k=i+1; k<grid_size*grid_size; k++)
    {
	if (grid[k/grid_size][k%grid_size] == 0)
	{
	    return k;
	}
    }
    return -1;
}


int Solver::previousEmpty(int** grid, int grid_size, int i)
{
    if (i == 0)
	return -1;

    for (int k=i-1; k>=0; k--)
    {
	if (grid[k/grid_size][k%grid_size] == 0)
	{
	    return k;
	}
    }
    return -1;
}


int Solver::firstEmpty(int** grid, int grid_size)
{
    for (int i=0; i<grid_size*grid_size; i++)
    {
	if (grid[i/grid_size][i%grid_size] == 0)
	    return i;
    }
    return -1;
}


int Solver::lastEmpty(int** grid, int grid_size)
{
    for (int i=grid_size*grid_size-1; i>=0; i--)
    {
	if (grid[i/grid_size][i%grid_size] == 0)
	    return i;
    }
    return -1;
}


void Solver::resetGrid(int** grid, int** initial_grid, int grid_size)
{
    for (int i=0; i < grid_size*grid_size; i++)
	if (initial_grid[i/grid_size][i%grid_size] == 0)
	    grid[i/grid_size][i%grid_size] = 0;
 
}


int Solver::isGridValid(int** grid, int grid_size)
{
   for (int i=0; i < grid_size*grid_size; i++)
	if (!isEmpty(grid, i/9, i%9))
	{
	    int val = grid[i/9][i%9];
	    grid[i/9][i%9] = 0;
	    if (existsInLine(grid, grid_size, val, i/grid_size) || existsInColumn(grid, grid_size, val, i%grid_size) || existsInSquare(grid, grid_size, val, i/grid_size, i%grid_size))
	    {
		grid[i/9][i%9] = val;
		return 0; // invalid grid
	    }
	    grid[i/9][i%9] = val;
	}
    return 1;
}

/*

etapes backtracking sudoku :

0) si la grille est pleine, on sort de la fonction; on sait que la grille est valide
1) sinon prendre le 1er element vide
2) tester si un nombre entre 1 et 9 peut etre mis en respectant les regles du sudoku
	3) si oui, mettre le plus petit element valide et appeler la fonction récursivement pour passer à l'élèment libre suivant
	4) si non, remettre à vide l'élèment courant. Prendre le précédent élèment qui était vide et essayer avec un nombre valide supérieur en appelant récursivement la fonction. Si on est au premier élèment qui était vide, c'est qu'il n'y a pas de solution

*/



