CC = g++
CFLAGS = -Wall -g
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: ./src/$(TARGET).cpp
	$(CC) $(CFLAGS) -c ./src/$(TARGET).cpp

clean:
	rm $(TARGET) $(TARGET).o