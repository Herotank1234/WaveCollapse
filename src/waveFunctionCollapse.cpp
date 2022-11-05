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

int main() {
  srand(time(NULL));
  Board* board = new Board();

  while(!board->isFinalised()) {
    std::vector<std::pair<int, int>> coords = board->findTilesWithLeastEntropy();
    std::cout << coords.size() << std::endl;
    int index = rand() % coords.size();
    board->collapseTile(coords[index].first, coords[index].second); 
    board->printBoard();
    std::cout << std::endl;
  }
  return 0;
}