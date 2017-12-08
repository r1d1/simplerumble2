VERSION = alpha
CXXFLAGS=-g -std=c++0x -pedantic #-Wall
PATHTOSFML=
all : SimpleRumble

#export LD_LIBRARY_PATH=${PATHTOSFML}/lib:$LD_LIBRARY_PATH

map: testMap.o
	g++ testMap.o -o testMap_${VERSION} -L${PATHTOSFML}/lib -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
	rm *.o

anim: testAnim.o
	g++ testAnim.o -o testAnim_${VERSION} -L${PATHTOSFML}/lib -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
	rm *.o
	
shape: testShape.o
	g++ testShape.o -o testShape_${VERSION} -L${PATHTOSFML}/lib -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
	rm *.o

main.o : main.cpp
	g++ src/main.cpp -c -I${PATHTOSFML}/include 

SimpleRumble : main.o Agent.o Attack.o utils.o Animator.o
	g++ *.o -o SimpleRumble2_${VERSION} -L${PATHTOSFML}/lib -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio -lsfml-window
	rm *.o

clean :
	rm -f *.o
	rm SimpleRumble2_${VERSION}
	rm testAnim_${VERSION}
	rm testShape_${VERSION}
