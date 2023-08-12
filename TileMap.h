#pragma once

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

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

  ~TileMap();

  void render(SDL_Renderer* renderer,
    int x, int y, int winWidth, int winHeight);

private:
  void CreateTexture(SDL_Renderer* renderer);
};
