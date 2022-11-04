#include "board.h"
#include <iostream>
int BOARD_LENGTH = 5;
int BOARD_WIDTH = 5;

Board::Board() {
  for(int i = 0; i < BOARD_LENGTH; i++) {
    std::vector<Tile> row;
    for(int j = 0; j < BOARD_WIDTH; j++) {
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