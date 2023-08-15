#pragma once
#include <iostream>
#include "config.hpp"

bool init(
  SDL_Window*& window, SDL_Renderer*& renderer, const Uint8*& keyStates);

void cleanup(SDL_Window*& window, SDL_Renderer*& renderer);
