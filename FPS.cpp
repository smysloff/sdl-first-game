#include "FPS.h"

FPS::FPS()
{
  Lasttime = Time = SDL_GetTicks64();
}

void FPS::update()
{
  Time = SDL_GetTicks64();

  if (Time - Lasttime < 1000)
    ++Count;
  else
  {
    Value = Count;
    Count = 0;
    Lasttime = Time;
  }
}

int FPS::getValue()
{
  return Value;
}

int FPS::getCount()
{
  return Count;
}

Uint64 FPS::getTime()
{
  return Time;
}

Uint64 FPS::getLasttime()
{
  return Lasttime;
}

void FPS::render(SDL_Renderer* renderer, TTF_Font* font)
{
  std::stringstream text;

  text.str("");
  text << Value;

  SDL_Surface* surface = TTF_RenderText_Solid(
    font, text.str().c_str(), { 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE });
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width, height;
  TTF_SizeText(font, text.str().c_str(), &width, &height);

  SDL_Rect dstRect = { .x = 5, .y = 7, .w = width, .h = height };
  SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}
