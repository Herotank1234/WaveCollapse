#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board {
public:
  Board();
  void printBoard();
private:
  std::vector<std::vector<Tile>> _board;
};

#endif
