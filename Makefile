VERSION = alpha
CXXFLAGS=-g -std=c++0x -pedantic #-Wall
PATHTOSFML=
all : SimpleRumble

#export LD_LIBRARY_PATH=${PATHTOSFML}/lib:$LD_LIBRARY_PATH

SimpleRumble : main.o Agent.o Attack.o utils.o
	g++ *.o -o SimpleRumble2_${VERSION} -L${PATHTOSFML}/lib -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
	rm *.o

#main.o : main.cpp
#	g++ -c main.cpp -I${PATHTOSFML}/include 

*.o : *.cpp
	g++ -c *.cpp -I${PATHTOSFML}/include 

displaypath :
	@echo ${PATHTOSFML}/include

clean :
	rm -f *.o
	rm -f SimpleRumble2_${VERSION}
