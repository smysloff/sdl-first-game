#include "FPS.h"

FPS::FPS()
{
  lasttime = time = SDL_GetTicks64();
}

void FPS::update()
{
  time = SDL_GetTicks64();

  if (time - lasttime < 1000)
    ++count;
  else
  {
    value = count;
    count = 0;
    lasttime = time;
  }
}

int FPS::getValue()
{
  return value;
}

int FPS::getCount()
{
  return count;
}

Uint64 FPS::getTime()
{
  return time;
}

Uint64 FPS::getLasttime()
{
  return lasttime;
}

void FPS::render()
{

}
