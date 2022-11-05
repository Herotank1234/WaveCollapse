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

std::map<std::string, std::vector<std::string>> edgeRules = {
  {"Black", {"bbb", "bbb", "bbb", "bbb"}},
  {"Connector", {"bbb", "bgg", "glg", "ggb"}}, 
  {"Connector90", {"ggb", "bbb", "bgg", "glg"}}, 
  {"Connector180", {"glg", "ggb", "bbb", "bgg"}},
  {"Connector270", {"bgg", "glg", "ggb", "bbb"}},
  {"ConnectorEdge", {"ggb", "bgg", "ggg", "ggg"}},
  {"ConnectorEdge90", {"ggg", "ggb", "bgg", "ggg"}},
  {"ConnectorEdge180", {"ggg", "ggg", "ggb", "bgg"}},
  {"ConnectorEdge270", {"bgg", "ggg", "ggg", "ggb"}},
  {"DiagPipeOne", {"ggg", "glg", "glg", "ggg"}},
  {"DiagPipeOne90", {"ggg", "ggg", "glg", "glg"}},
  {"DiagPipeOne180", {"glg", "ggg", "ggg", "glg"}},
  {"DiagPipeOne270", {"glg", "glg", "ggg", "ggg"}},
  {"DiagPipeTwoL", {"glg", "glg", "glg", "glg"}},
  {"DiagPipeTwoR", {"glg", "glg", "glg", "glg"}},
  {"Dot", {"ggg", "ggg", "glg", "ggg"}},
  {"Dot90", {"ggg", "ggg", "ggg", "glg"}},
  {"Dot180", {"glg", "ggg", "ggg", "ggg"}},
  {"Dot270", {"ggg", "glg", "ggg", "ggg"}},
  {"DotTwoWayH", {"ggg", "glg", "ggg", "glg"}},
  {"DotTwoWayV", {"glg", "ggg", "glg", "ggg"}},
  {"Green", {"ggg", "ggg", "ggg", "ggg"}},
  {"PipeCrossH", {"glg", "gyg", "glg", "gyg"}},
  {"PipeCrossV", {"gyg", "glg", "gyg", "glg"}},
  {"PipeGreenH", {"ggg", "glg", "ggg", "glg"}},
  {"PipeGreenV", {"glg", "ggg", "glg", "ggg"}},
  {"PipeGreyH", {"ggg", "gyg", "ggg", "gyg"}},
  {"PipeGreyV", {"gyg", "ggg", "gyg", "ggg"}},
  {"PipeSwitch", {"ggg", "gyg", "ggg", "glg"}},
  {"PipeSwitch90", {"glg", "ggg", "gyg", "ggg"}},
  {"PipeSwitch180", {"ggg", "glg", "ggg", "gyg"}},
  {"PipeSwitch270", {"gyg", "ggg", "glg", "ggg"}},
  {"PipeT", {"glg", "glg", "glg", "ggg"}},
  {"PipeT90", {"ggg", "glg", "glg", "glg"}},
  {"PipeT180", {"glg", "ggg", "glg", "glg"}},
  {"PipeT270", {"glg", "glg", "ggg", "glg"}}
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