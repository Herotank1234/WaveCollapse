SRC = ./src/

CC = g++
CFLAGS = -Wall -g
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) tile.o board.o

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(SRC)$(TARGET).cpp
	$(CC) $(CFLAGS) -c $(SRC)$(TARGET).cpp

tile.o: $(SRC)tile.cpp
	$(CC) $(CFLAGS) -c $(SRC)tile.cpp

board.o: $(SRC)board.cpp $(SRC)tile.h
	$(CC) $(CFLAGS) -c $(SRC)board.cpp

clean:
	rm $(TARGET) *.o