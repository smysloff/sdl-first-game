#include "TileMap.hpp"

TileMap::TileMap(SDL_Renderer* renderer,
  int TilesInRow, int TilesInCol, int TileSize)
    : TilesInRow(TilesInRow), TilesInCol(TilesInCol), TileSize(TileSize)
{
  Width = TilesInRow * TileSize;
  Height = TilesInCol * TileSize;
  Map = new int[TilesInCol * TilesInRow]{0};
  Generate(renderer);
  CreateTexture(renderer);
}

TileMap::~TileMap()
{
  delete[] Map;
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
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);

  SDL_SetRenderTarget(renderer, texture);

  SDL_Texture* grass = IMG_LoadTexture(renderer, "img/grass.png");

  for (int col = 0; col < TilesInCol; ++col)
  {
    for (int row = 0; row < TilesInRow; ++row)
    {
      const SDL_Rect dstRect = {
        .x = row * TileSize,
        .y = col * TileSize,
        .w = TileSize,
        .h = TileSize
      };
      SDL_RenderCopy(renderer, grass, nullptr, &dstRect);
    }
  }

  SDL_DestroyTexture(grass);

  /* tile borders
   *
  SDL_SetRenderDrawColor(renderer, 0x22, 0x22, 0x22, SDL_ALPHA_OPAQUE);

  for (int row = 0; row < TilesInCol; ++row)
  {
    int y = row * TileSize;
    SDL_RenderDrawLine(renderer, 0, y, Width, y);
  }

  for (int col = 0; col < TilesInRow; ++col)
  {
    int x = col * TileSize;
    SDL_RenderDrawLine(renderer, x, 0, x, Height);
  }
  */

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, 0, 0, Width, 0);
  SDL_RenderDrawLine(renderer, 0, Height - 1, Width, Height -1);
  SDL_RenderDrawLine(renderer, 0, 0, 0, Height);
  SDL_RenderDrawLine(renderer, Width - 1, 0, Width - 1, Height);

  SDL_SetRenderTarget(renderer, nullptr);
}

int TileMap::getWidth()
{
  return Width;
}

int TileMap::getHeight()
{
  return Height;
}

int TileMap::getTileSize()
{
  return TileSize;
}

int TileMap::getTilesInRow()
{
  return TilesInRow;
}

int TileMap::getTilesInCol()
{
  return TilesInCol;
}

void TileMap::Generate(SDL_Renderer* renderer)
{
  (void)renderer; 
}
