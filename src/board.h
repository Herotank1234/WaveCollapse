#ifndef BOARD_H
#define BOARD_H
#include "tile.h"

class Board {
public:
  Board(int length, int width);
  void printBoard();
  std::vector<std::pair<int, int>> findTilesWithLeastEntropy();
  bool collapseTile(int x, int y);
  bool isFinalised();
  void propagate(int x, int y);
  bool inBounds(int x, int y);
  std::string getTileName(int x, int y);
  std::pair<int, int> getSize();
private:
  int _length, _width;
  int _maxEntropy = 36;
  std::vector<std::vector<Tile>> _board;
};

#endif
