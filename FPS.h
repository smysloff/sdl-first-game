#pragma once
#include "SDL_include.h"

class FPS
{
public:
  FPS();
  void update();
  void render();
  int getValue();
  int getCount();
  Uint64 getTime();
  Uint64 getLasttime();

private:
  int value = 0;
  int count = 0;
  Uint64 time;
  Uint64 lasttime;
};
