#include "Tile.h"
#include <stdlib.h>
#include <map>
#include <algorithm>

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

Tile::Tile(): _finalTile(""), _finalised(false) {
  _possibleTiles = {"Black", "Connector", "Connector90", "Connector180", "Connector270",
  "ConnectorEdge", "ConnectorEdge90", "ConnectorEdge180", "ConnectorEdge270", "DiagPipeOne", 
  "DiagPipeOne90", "DiagPipeOne180", "DiagPipeOne270", "DiagPipeTwoL", "DiagPipeTwoR",
  "Dot", "Dot90", "Dot180", "Dot270", "DotTwoWayH", "DotTwoWayV", "Green", "PipeCrossH",
  "PipeCrossV", "PipeGreenH", "PipeGreenV", "PipeGreyH", "PipeGreyV", "PipeSwitch",
  "PipeSwitch90", "PipeSwitch180", "PipeSwitch270", "PipeT", "PipeT90", "PipeT180", "PipeT270"
  };
}

int Tile::getNumberOfPossibleTiles() {
  return _possibleTiles.size();
}

void Tile::setFinalTile() {
  _finalTile = _possibleTiles[0];
}

bool Tile::isFinalised() {
  return _finalised;
}

void Tile::collapseTile() {
  int index = rand() % _possibleTiles.size();
  _finalTile = _possibleTiles[index];
  _finalised = true;
}

std::string Tile::getFinalTile() {
  return _finalTile;
}

void Tile::reducePossibleTiles(int direction, std::string edge) {
  int reflectedDir = (direction + 2) % 4;
  std::string reflectedEdge = edge;
  std::reverse(reflectedEdge.begin(), reflectedEdge.end());
  std::vector<std::string> remainingTiles;
  for(std::string t : _possibleTiles) {
    if(edgeRules[t][reflectedDir] == reflectedEdge) {
      remainingTiles.push_back(t);
    }
  }
  _possibleTiles = remainingTiles;
}