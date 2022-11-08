SRC = ./src/
LIBDIR = ./lib/

CC = g++
CFLAGS = -Wall -g
INC = -I/usr/include -I./lib/glad/include
LIB = -lGL -lglfw
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) 

$(TARGET): $(TARGET).o board.o tile.o window.o shader.o VBO.o
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(TARGET).o board.o tile.o window.o shader.o VBO.o $(LIB) ./lib/glad/src/glad.c

$(TARGET).o: $(SRC)$(TARGET).cpp
	$(CC) $(CFLAGS) $(INC) -c $(SRC)$(TARGET).cpp

tile.o: $(SRC)tile.cpp
	$(CC) $(CFLAGS) -c $(SRC)tile.cpp

board.o: $(SRC)board.cpp $(SRC)tile.h
	$(CC) $(CFLAGS) -c $(SRC)board.cpp

window.o: $(SRC)window.cpp $(SRC)board.h
	$(CC) $(CFLAGS) -c $(SRC)window.cpp

shader.o: $(SRC)shader.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)shader.cpp

VBO.o: $(SRC)VBO.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)VBO.cpp


clean:
	rm $(TARGET) *.o