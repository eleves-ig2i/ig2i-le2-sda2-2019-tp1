all : mainDames.exe mainChaine.exe mainTestLib.exe

INC = -I./include/
SRC = ./src/


mainDames.exe : libPile.o libElt.o
	gcc $(INC) *.o $(SRC)dames.c -o mainDames.exe

mainChaine.exe : libPile.o libElt.o
	gcc $(INC) *.o $(SRC)permut.c -o mainChaine.exe

mainTestLib.exe : libPile.o libElt.o
	gcc $(INC) libPile.o libElt.o $(SRC)testPile.c -o mainTestLib.exe

libPile.o : $(SRC)libPile.c 
	gcc $(INC) -c $(SRC)libPile.c

libElt.o : $(SRC)libElt.c 
	gcc $(INC) -c $(SRC)libElt.c

clean :
	rm *.o *.exe
