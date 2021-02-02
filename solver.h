#ifndef SOLVER_H
#define SOLVER_H

class Solver
{
    public:
	Solver(int);
	void solveGrid(int**, int**, int);
	int moreThanOneSol(int**, int**, int);
	int getStatus(void);
	static int existsInColumn(int**, int, int, int);
	static int existsInLine(int**, int, int, int);
	static int existsInSquare(int**, int, int, int, int);
	static void resetGrid(int**, int**, int);
	int rec_status;

    private:	
	int solveGridRec(int**, int**, int, int);
	void setStatus(int);
	static int isEmpty(int**, int, int);
        static int gridIsFull(int**, int);
	static int nextEmpty(int**, int, int);
	static int previousEmpty(int**, int, int);
	static int firstEmpty(int**, int);
	static int lastEmpty(int**, int);
	static int isGridValid(int**, int);
};

#endif
