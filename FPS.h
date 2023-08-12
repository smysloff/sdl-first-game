#pragma once

#ifdef __APPLE__
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

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
