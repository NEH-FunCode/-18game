sudoku: main.o parser.o solver.o creator.o
	g++ -o sudoku main.o parser.o solver.o creator.o

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.cpp parser.h
	g++ -c parser.cpp

solver.o: solver.cpp solver.h
	g++ -c solver.cpp

creator.o: creator.cpp creator.h
	g++ -c creator.cpp

clean:
	rm *.o
