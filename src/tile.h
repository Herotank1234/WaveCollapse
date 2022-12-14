#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>

class Tile {
public:
  Tile();
  int getNumberOfPossibleTiles();
  void setFinalTile();
  bool isFinalised();
  bool collapseTile();
  std::string getFinalTile();
  void reducePossibleTiles(int direction, std::string tile);
private:
  std::vector<std::string> _possibleTiles;
  std::string _finalTile;
  bool _finalised;
};

#endif