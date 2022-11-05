SRC = ./src/

CC = g++
CFLAGS = -Wall -g
LIB = -lglut -lGLU -lGL
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) 

$(TARGET): $(TARGET).o board.o tile.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o board.o tile.o $(LIB)

$(TARGET).o: $(SRC)$(TARGET).cpp
	$(CC) $(CFLAGS) $(INC) -c $(SRC)$(TARGET).cpp

tile.o: $(SRC)tile.cpp
	$(CC) $(CFLAGS) -c $(SRC)tile.cpp

board.o: $(SRC)board.cpp $(SRC)tile.h
	$(CC) $(CFLAGS) -c $(SRC)board.cpp

clean:
	rm $(TARGET) *.o