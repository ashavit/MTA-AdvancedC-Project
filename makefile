All: main.o Board.o Interface.o PathPrices.o pathTree.o PositionArray.o
	clear
	gcc main.o Board.o Interface.o PathPrices.o pathTree.o PositionArray.o -o main
	./main
	make clear

main.o: main.c Commons.h Board.h PositionArray.h pathTree.h PathPrices.h
	gcc -c main.c

Board.o: Board.c Commons.h Board.h
	gcc -c Board.c

Interface.o: Commons.h Interface.c Interface.h Board.h
	gcc -c Interface.c

PositionArray.o: Commons.h PositionArray.c PositionArray.h Board.h
	gcc -c PositionArray.c

pathTree.o: Commons.h pathTree.c pathTree.h Board.h
	gcc -c pathTree.c

PathPrices.o: Commons.h PathPrices.c PathPrices.h Board.h pathTree.h
	gcc -c PathPrices.c

clear:
	rm *.o
	rm main
