#include "TileMap.h"

TileMap::TileMap(SDL_Renderer* renderer,
  int tilesInRow, int tilesInCol, int tileSize)
    : tilesInRow(tilesInRow), tilesInCol(tilesInCol), tileSize(tileSize)
  {
    width = tilesInRow * tileSize;
    height = tilesInCol * tileSize;
    CreateTexture(renderer);
  }

TileMap::~TileMap()
{
  SDL_DestroyTexture(texture);
}

void TileMap::render(SDL_Renderer* renderer,
  int x, int y, int winWidth, int winHeight
) {

  SDL_Rect srcRect = {
    .x = x - winWidth / 2,
    .y = y - winHeight / 2,
    .w = winWidth,
    .h = winHeight
  };

  SDL_RenderCopy(renderer, texture, &srcRect, nullptr);
}

void TileMap::CreateTexture(SDL_Renderer* renderer)
{
  texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

  SDL_SetRenderTarget(renderer, texture);
  SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, SDL_ALPHA_OPAQUE);

  for (int row = 0; row < tilesInCol; ++row)
  {
    int y = row * tileSize;
    SDL_RenderDrawLine(renderer, 0, y, width, y);
  }

  for (int col = 0; col < tilesInRow; ++col)
  {
    int x = col * tileSize;
    SDL_RenderDrawLine(renderer, x, 0, x, height);
  }

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, 0, width, 0);
  SDL_RenderDrawLine(renderer, 0, height - 1, width, height -1);
  SDL_RenderDrawLine(renderer, 0, 0, 0, height);
  SDL_RenderDrawLine(renderer, width - 1, 0, width - 1, height);

  SDL_SetRenderTarget(renderer, nullptr);
}
