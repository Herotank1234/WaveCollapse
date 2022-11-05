#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"

class Board {
public:
  Board();
  void printBoard();
  std::pair<int, int> findTileWithLeastEntropy();
  void collapseRandomTile();
  void collapseTile(int x, int y);
  bool isFinalised();
  void propagate(int x, int y);
  bool inBounds(int x, int y);
private:
  std::vector<std::vector<Tile>> _board;
};

#endif
