#include "Controls.hpp"

void Controls::update(const Uint8* keyStates)
{
  left  = keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT];
  right = keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT];
  up    = keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP];
  down  = keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN];
}
