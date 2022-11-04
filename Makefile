CC = g++
CFLAGS = -Wall -g
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) tile.o

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: ./src/$(TARGET).cpp
	$(CC) $(CFLAGS) -c ./src/$(TARGET).cpp

tile.o: ./src/tile.cpp
	$(CC) $(CFLAGS) -c ./src/tile.cpp

clean:
	rm $(TARGET) $(TARGET).o