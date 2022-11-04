#include "board.h"
#include <iostream>

int BOARD_LENGTH = 5;
int BOARD_WIDTH = 5;
int MAX_ENTROPY = 13;

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

std::pair<int, int> Board::findTileWithLeastEntropy() {
  int x = -1, y = -1, leastEntropy = MAX_ENTROPY, entropy = 0;
  for(int i = 0; i < BOARD_LENGTH; i++) {
    for(int j = 0; j < BOARD_LENGTH; j++) {
      entropy = _board[i][j].getNumberOfPossibleTiles();
      if(!_board[i][j].isFinalised() && entropy < leastEntropy) {
        y = i;
        x = j;
        leastEntropy = entropy;
      }
    }
  }
  return std::pair<int, int>({x, y});
}

void Board::collapseRandomTile() {
  int x = rand() % BOARD_WIDTH, y = rand() % BOARD_LENGTH;
  while(_board[y][x].isFinalised()) {
    x = rand() % BOARD_WIDTH;
    y = rand() % BOARD_LENGTH;
  }
  _board[y][x].collapseTile();
}

void Board::collapseTile(int x, int y) {
  _board[y][x].collapseTile();
}
 
bool Board::isFinalised() {
  for(int i = 0; i < BOARD_LENGTH; i++) {
    for(int j = 0; j < BOARD_WIDTH; j++) {
      if(!_board[i][j].isFinalised()) return false;
    }
  }
  return true;
}