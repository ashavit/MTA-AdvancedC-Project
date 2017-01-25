All: main.o Board.o Interface.o PathPrices.o PathTree.o PositionArray.o PositionList.o TestClass.o
	clear
	gcc main.o Board.o Interface.o PathPrices.o PathTree.o PositionArray.o PositionList.o TestClass.o -o main
	./main
#	make clear

main.o: main.c Interface.h TestClass.h
	gcc -c main.c

Board.o: Board.c Board.h Commons.h
	gcc -c Board.c

Interface.o: Interface.c Interface.h Commons.h Board.h
	gcc -c Interface.c

PositionArray.o: PositionArray.c PositionArray.h Commons.h Board.h
	gcc -c PositionArray.c

PathTree.o: PathTree.c PathTree.h Commons.h Board.h
	gcc -c PathTree.c

PathPrices.o: PathPrices.c PathPrices.h Commons.h Board.h PathTree.h
	gcc -c PathPrices.c

PositionList.o: PositionList.c PositionList.h Commons.h Board.h
	gcc -c PositionList.c

TestClass.o: TestClass.c TestClass.h Commons.h Board.h PositionArray.h PathTree.h PathPrices.h PositionList.h
	gcc -c TestClass.c

clear:
	rm *.o
	rm main
