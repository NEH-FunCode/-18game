# Sudoku Solver and Creator

A linux C++ program to solve a sudoku grid passed in a text file or generate a random grid with a single solution ready to play.

How to use :

1) Download the project.
2) cd in the directory and type make
3) Three modes are available : first one to get a True/False answer to know if the grid passed in parameter has 1 or more solution(s), second one to solve a grid passed in parameter and last one to generate an easy/medium/hard grid ready to play.

./sudoku -s filename, for solving
./sudoku -g -e/m/h, for generating a random easy/medium/hard grid to solve
./sudoku -c filename, to know if the grid has a single solution, or more

Examples :

./sudoku -c empty_grid

The sudoku grid which we want to know if it has more that one solution :

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

_ _ _ _ _ _ _ _ _ 

Has the grid more than one solution (1 for y, 0 for n) ? : 1

./sudoku -s test_grid_3 

The initial sudoku grid :
_ 5 9 _ _ _ 6 _ _ 
_ _ _ 4 _ _ 5 _ _ 
_ _ _ 5 _ 9 _ 3 _ 
1 6 _ _ 3 4 9 _ _ 
_ 4 3 _ _ 7 _ _ _ 
5 9 _ 2 _ _ _ _ _ 
3 _ 4 _ _ _ _ 5 8 
_ _ _ 3 _ 5 _ 4 _ 
9 _ 5 _ _ 2 3 _ 1 

The grid solved : 

4 5 9 1 2 3 6 8 7 
6 3 1 4 7 8 5 9 2 
8 7 2 5 6 9 1 3 4 
1 6 7 8 3 4 9 2 5 
2 4 3 9 5 7 8 1 6 
5 9 8 2 1 6 4 7 3 
3 2 4 6 9 1 7 5 8 
7 1 6 3 8 5 2 4 9 
9 8 5 7 4 2 3 6 1


./sudoku -g -h

The generated random hard grid ready to play :

7 1 _ _ 3 _ _ _ _ 
_ 4 _ _ 8 6 1 7 _ 
_ _ _ 7 _ _ _ _ _ 
_ _ 7 4 6 _ _ 8 _ 
_ _ _ _ 9 _ 7 _ _ 
_ _ _ 3 _ _ _ _ _ 
_ 2 _ 8 5 _ 6 9 _ 
_ 5 _ _ 4 _ 3 _ 7 
4 _ _ _ 2 _ _ _ 1

Enjoy.
