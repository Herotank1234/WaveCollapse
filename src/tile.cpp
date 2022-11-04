#include "Tile.h"
#include <stdlib.h>

Tile::Tile(): _finalTile(""), _finalised(false) {
  _possibleTiles = {"Black", "Connector", "ConnectorEdge", "DiagpipeOne", 
  "DiagPipeTwo", "Dot", "DotTwoWay", "Green", "Pipe", "PipeCross", "PipeGreen", 
  "PipeSwitch", "PipeT"};
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

