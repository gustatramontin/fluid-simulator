
main:
	g++ -o fluid-simulator main.cpp visuals.cpp physics.cpp events.cpp `sdl2-config --libs --cflags` -lm 
