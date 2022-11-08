#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <utility>
#include <vector>
#include <map>
#include "board.h"
#include "tile.h"
#include "window.h"

int main(int argc, char** argv) {
  // Set random seed
  srand(time(NULL));

  // Create new board and window
  Board* board = new Board(20, 20);
  Window* window = new Window(board);

  // Initialise the window
  window->windowInit();

  // Main Loop
  while(!window->shouldClose()) {
    if(!board->isFinalised()) {
      std::vector<std::pair<int, int>> coords = board->findTilesWithLeastEntropy();
      int index = rand() % coords.size();
      std::pair<int, int> coord = coords[index];
      if(!board->collapseTile(coord.first, coord.second)) {
        board = new Board(20, 20);
        window->setBoard(board);
      } 
    }
    window->updateDisplay();
    window->pollEvents();
  }
}