#ifndef CREATOR_H
#define CREATOR_H

class Creator
{
    public:
	Creator();
        int createRandomGrid(int**, int**, int);
    private:
	int* genRandArray(int*, int);
	int generateRandomFilledGrid(int**, int**, int);
	int removeElements(int**, int, int);
};

#endif
