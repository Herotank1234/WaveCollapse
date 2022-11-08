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

// int main() {
//   srand(time(NULL));
//   Board* board = new Board();

//   while(!board->isFinalised()) {
//     std::vector<std::pair<int, int>> coords = board->findTilesWithLeastEntropy();
//     std::cout << coords.size() << std::endl;
//     int index = rand() % coords.size();
//     board->collapseTile(coords[index].first, coords[index].second); 
//     board->printBoard();
//     std::cout << std::endl;
//   }
//   return 0;
// }

int main(int argc, char** argv) {
  // Set random seed
  srand(time(NULL));

  // Create new board and window
  Board* board = new Board(5, 5);
  Window* window = new Window(board);

  // Initialise the window
  window->windowInit();

  // Main Loop
  while(!window->shouldClose()) {
    window->updateDisplay();
    window->pollEvents();
  }
}