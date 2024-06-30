CFLAGS = -Iheaders/
CC = g++
LDFLAGS = `sdl2-config --libs --cflags` -lm

objects/%.o: src/%.cpp
	$(CC) -c $^ -o $@ $(CFLAGS)

compile: objects/main.o objects/visuals.o objects/physics.o objects/events.o objects/vec_geometry.o objects/particle_geometry.o
	$(CC) $^ -o fluid-simulator $(LDFLAGS)
