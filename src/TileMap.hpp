#pragma once
#include "SDL_include.hpp"

class TileMap
{
public:
  SDL_Texture* texture;

  TileMap(SDL_Renderer* renderer,
    int TilesInRow, int TilesInCol, int TileSize);

  ~TileMap();

  void render(SDL_Renderer* renderer,
    int x, int y, int winWidth, int winHeight);

  int getWidth();
  int getHeight();
  int getTilesInRow();
  int getTilesInCol();
  int getTileSize();

private:
  int Width;
  int Height;
  int TilesInRow;
  int TilesInCol;
  int TileSize;
  int *Map;

  void CreateTexture(SDL_Renderer* renderer);
  void Generate(SDL_Renderer* renderer);
};
