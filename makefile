Cube.o: Cube.cpp Cube.hpp
	g++ -c Cube.cpp

Rubik.o: Rubik.cpp Rubik.hpp
	g++ -c Rubik.cpp

Interface.o: Interface.cpp Interface.hpp
	g++ -c Interface.cpp

main.o: main.cpp
	g++ -c main.cpp

Magic_Cube: Cube.o Rubik.o Interface.o main.o
	g++ -o Magic_Cube main.o Interface.o Rubik.o Cube.o resources.o -lglut32cu -lglu32 -lopengl32 -static-libgcc -static-libstdc++ -mwindows && Magic_Cube
#	g++ -o Magic_Cube main.o Interface.o Rubik.o Cube.o resources.o -lglut32cu -lglu32 -lopengl32 -static-libgcc -static-libstdc++ && Magic_Cube
	