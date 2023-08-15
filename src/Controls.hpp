#pragma once
#include "SDL_include.hpp"

class Controls
{
public:
  bool left  = false;
  bool right = false;
  bool up    = false;
  bool down  = false;

  void update(const Uint8* keyStates);
};
