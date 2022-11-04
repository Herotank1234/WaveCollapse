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

std::map<std::string, std::vector<std::vector<char>>> edgeMap = {
{"Black", 
  {{'b', 'b', 'b'}, {'b', 'b', 'b'}, {'b', 'b', 'b'}, {'b', 'b', 'b'}}},
{"Connector", 
  {{'b', 'g', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'b'}, {'b', 'b', 'b'}}},
{"ConnectorEdge", 
  {{'b', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'b'}}},
{"DiagPipeOne", 
  {{'g', 'l', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}}},
{"DiagPipeTwo", 
  {{'g', 'l', 'g'}, {'g', 'l', 'g'}, {'g', 'l', 'g'}, {'g', 'l', 'g'}}},
{"Dot", 
  {{'g', 'g', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}}},
{"DotTwoWay", 
  {{'g', 'g', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}, {'g', 'l', 'g'}}},
{"Green", 
  {{'g', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}, {'g', 'g', 'g'}}},
{"Pipe", 
  {{'g', 'g', 'g'}, {'g', 'y', 'g'}, {'g', 'g', 'g'}, {'g', 'y', 'g'}}},
{"PipeCross", 
  {{'g', 'y', 'g'}, {'g', 'l', 'g'}, {'g', 'y', 'g'}, {'g', 'l', 'g'}}},
{"PipeGreen", 
  {{'g', 'g', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}, {'g', 'l', 'g'}}},
{"PipeSwitch", 
  {{'g', 'y', 'g'}, {'g', 'g', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}}},
{"PipeT", 
  {{'g', 'l', 'g'}, {'g', 'l', 'g'}, {'g', 'g', 'g'}, {'g', 'l', 'g'}}}
};

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