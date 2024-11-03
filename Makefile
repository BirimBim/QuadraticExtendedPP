all: compile

compile: 
	g++ -std=c++11 *.cpp -o exe $(shell pkg-config --cflags --libs sdl2 SDL2_ttf)
	./exe
