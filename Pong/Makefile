CC=g++
CFLAGS=-std=c++20 -L/usr/local/Cellar/sfml/2.5.1_2/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
SOURCE1=pong.cpp menu.cpp initialization.cpp
SOURCE2=pong_server.cpp
HEADERS=pong.hpp
EXECUTABLE1=pong
EXECUTABLE2=pong_server

all: server pong

pong: $(SOURCE1)
	$(CC) $(SOURCE1) -o $(EXECUTABLE1) $(CFLAGS)

server: $(SOURCE2)
	$(CC) $(SOURCE2) -o $(EXECUTABLE2) $(CFLAGS)

rebuild: clean server pong

clean: 
	rm $(EXECUTABLE1) $(EXECUTABLE2)
