SRC = ./src/
LIBDIR = ./lib/

CC = g++
CFLAGS = -Wall -g
INC = -I/usr/include -I./lib/glad/include
LIB = -lGL -lglfw 
TARGET = waveFunctionCollapse

.PHONY: all clean

all: $(TARGET) 

$(TARGET): $(TARGET).o board.o tile.o window.o shader.o VBO.o EBO.o VAO.o structs.o texture.o
	$(CC) $(CFLAGS) $(INC) -o $(TARGET) $(TARGET).o board.o tile.o window.o shader.o VBO.o EBO.o VAO.o structs.o texture.o $(LIB) ./lib/glad/src/glad.c

$(TARGET).o: $(SRC)$(TARGET).cpp
	$(CC) $(CFLAGS) $(INC) -c $(SRC)$(TARGET).cpp

tile.o: $(SRC)tile.cpp
	$(CC) $(CFLAGS) -c $(SRC)tile.cpp

board.o: $(SRC)board.cpp $(SRC)tile.h
	$(CC) $(CFLAGS) -c $(SRC)board.cpp

window.o: $(SRC)window.cpp $(SRC)board.h $(SRC)structs.h
	$(CC) $(CFLAGS) -c $(SRC)window.cpp

shader.o: $(SRC)shader.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)shader.cpp

VAO.o: $(SRC)VAO.cpp $(SRC)VBO.h 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)VAO.cpp

VBO.o: $(SRC)VBO.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)VBO.cpp

EBO.o: $(SRC)EBO.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)EBO.cpp

structs.o: $(SRC)structs.cpp 
	$(CC) $(CFLAGS) $(INC) -c $(SRC)structs.cpp

texture.o: $(SRC)texture.cpp $(SRC)structs.h
	$(CC) $(CFLAGS) $(INC) -c $(SRC)texture.cpp

clean:
	rm $(TARGET) *.o