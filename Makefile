SRC = ./src/
LIBDIR = ./lib/

CC = g++
CFLAGS = -Wall -g
INC = -I/usr/include -I./lib/glad/include
LIB = -lGL -lglfw
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) 

$(TARGET): $(TARGET).o board.o tile.o
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(TARGET).o board.o tile.o $(LIB) ./lib/glad/src/glad.c

$(TARGET).o: $(SRC)$(TARGET).cpp
	$(CC) $(CFLAGS) $(INC) -c $(SRC)$(TARGET).cpp

tile.o: $(SRC)tile.cpp
	$(CC) $(CFLAGS) -c $(SRC)tile.cpp

board.o: $(SRC)board.cpp $(SRC)tile.h
	$(CC) $(CFLAGS) -c $(SRC)board.cpp

clean:
	rm $(TARGET) *.o