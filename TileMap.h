#pragma once

#include <SDL2/SDL.h>

class TileMap
{
public:
  int tilesInRow;
  int tilesInCol;
  int tileSize;
  int width;
  int height;
  SDL_Texture* texture;

  TileMap(SDL_Renderer* renderer,
    int tilesInRow, int tilesInCol, int tileSize);
/*    : tilesInRow(tilesInRow), tilesInCol(tilesInCol), tileSize(tileSize)
  {
    width = tilesInRow * tileSize;
    height = tilesInCol * tileSize;
    CreateTexture(renderer);
  }*/

  ~TileMap();

  void render(SDL_Renderer* renderer,
    int x, int y, int winWidth, int winHeight);

private:
  void CreateTexture(SDL_Renderer* renderer);
};
