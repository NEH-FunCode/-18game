#include <stdlib.h>
#include <stdio.h>

int grid_size = 9;

static void usage (int status)
{
  
  if (status == EXIT_SUCCESS)
    {
      fputs ("Usage: sudoku [OPTION] FILE \n "
             "Solve Sudoku puzzle's of variable size (1-4) \n\n"
             "-o, --output=FILE write result to FILE \n"
             "-v --verbose verbose output \n"
             "-V --version display version and exit \n"
             "-h --help display this help \n", stdout);
    }
  
  else
    {
      fputs ("Try 'sudoku --help' for more information \n", stderr);
    }
  
  exit(0);

}

void print_grid(char** grid)
{
    for (int i=0; i<grid_size; i++)
    {
        for (int j=0; j<grid_size; j++)
        {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void parse_grid(char* filename, char** grid)
{
  char current_char;
  int ind_grid = 0;

  FILE* fp;
  fp = fopen(filename, "r");

  if (fp == NULL)
    usage(EXIT_FAILURE);

  while (current_char = fgetc(fp) != EOF)
  {
    if ((current_char >= '1' && current_char <= '9')
	  || (current_char == '_'))
    {
        grid[ind_grid/9][ind_grid%9] = current_char;
        ind_grid ++;
    }
  }
}

int main(int argc, char* argv)
{
    char** grid = malloc(sizeof(char*)*grid_size);
    for (int i=0; i<grid_size; i++)
    {
        grid[i] = malloc(grid_size*sizeof(char));
    }
    parse_grid("grid-03-size_9", grid);
    print_grid(grid);
    
    return 1;
}