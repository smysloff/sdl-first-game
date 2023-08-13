#pragma once
#include <sstream>
#include "SDL_include.h"

class FPS
{
public:
  FPS();
  void update();
  void render(SDL_Renderer* renderer, TTF_Font* font);
  int getValue();
  int getCount();
  Uint64 getTime();
  Uint64 getLasttime();

private:
  int Value = 0;
  int Count = 0;
  Uint64 Time;
  Uint64 Lasttime;
};
