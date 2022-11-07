#include "board.h"
#include <iostream>

Board::Board(int length, int width) : _length(length), _width(width) {
  for(int i = 0; i < _length; i++) {
    std::vector<Tile> row;
    for(int j = 0; j < _width; j++) {
      row.emplace_back();
    }
    _board.push_back(row);
  }
}

void Board::printBoard() {
  for(auto row : _board) {
    std::cout << "| ";
    for(auto tile : row) {
      std::cout << tile.getFinalTile() << " | ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::pair<int, int>> Board::findTilesWithLeastEntropy() {
  int leastEntropy = _maxEntropy, entropy = 0;
  for(int i = 0; i < _length; i++) {
    for(int j = 0; j < _length; j++) {
      entropy = _board[i][j].getNumberOfPossibleTiles();
      std::cout << entropy << std::endl;
      if(!_board[i][j].isFinalised() && entropy < leastEntropy) {
        leastEntropy = entropy;
      }
    }
  }
  std::vector<std::pair<int, int>> res;
  for(int i = 0; i < _length; i++) {
    for(int j = 0; j < _width; j++) {
      entropy = _board[i][j].getNumberOfPossibleTiles();
      if(!_board[i][j].isFinalised() && entropy == leastEntropy) {
        res.push_back({j, i});
      }
    }
  }
  return res;
}

void Board::collapseTile(int x, int y) {
  _board[y][x].collapseTile();
  propagate(x, y);
}
 
bool Board::isFinalised() {
  for(int i = 0; i < _length; i++) {
    for(int j = 0; j < _width; j++) {
      if(!_board[i][j].isFinalised()) return false;
    }
  }
  return true;
}

void Board::propagate(int x, int y) {
  std::vector<std::pair<int, int>> steps = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  for(size_t i = 0; i < steps.size(); i++) {
      std::pair<int, int> currStep = steps[i];
      int nextX = x + currStep.first, nextY = y + currStep.second;
      if(inBounds(nextX, nextY) && !_board[nextY][nextX].isFinalised()) {
        _board[nextY][nextX].reducePossibleTiles(i, _board[y][x].getFinalTile());
      }
  }
}

bool Board::inBounds(int x, int y) {
  return x >= 0 && x < _width && y >= 0 && y < _length;
}

std::pair<int, int> Board::getSize() {
  return {_width, _length};
}