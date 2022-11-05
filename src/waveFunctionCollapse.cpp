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
    std::pair<int, int> coords = board->findTileWithLeastEntropy();
    std::cout << coords.first << " " << coords.second << std::endl;
    if(coords.first == -1) {
      board->collapseRandomTile();
    } else {
      board->collapseTile(coords.first, coords.second);
    }
    board->printBoard();
    std::cout << std::endl;
  }
  return 0;
}