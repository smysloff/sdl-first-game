#include "utils.hpp"

using std::cerr;
using std::endl;

bool init(
  SDL_Window*& window, SDL_Renderer*& renderer, const Uint8*& keyStates)
{
  if (SDL_Init(SDL_INIT_VIDEO))
  {
    cerr << "error: on SDL_Init(SDL_INIT_VIDEO). " << SDL_GetError() << endl;
    return false;
  }

  if (! (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    SDL_Quit();
    cerr << "error: on IMG_Init(IMG_INIT_PNG). " << IMG_GetError() << endl;
    return false;
  }

  if (TTF_Init())
  {
    IMG_Quit();
    SDL_Quit();
    cerr << "error: on TTF_Init(). " << SDL_GetError() << endl;
    return false;
  }

  window = SDL_CreateWindow(WINDOW_TITLE,
    WINDOW_POS_X, WINDOW_POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS); 

  if (!window)
  {
    cerr << "error: on SDL_CreateWindow(). " << SDL_GetError() << endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1,
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer)
  {
    cerr << "error: on SDL_CreateRenderer(). " << SDL_GetError() << endl;
    return false;
  }

  keyStates = SDL_GetKeyboardState(nullptr);

  return true;
}

void cleanup(SDL_Window*& window, SDL_Renderer*& renderer)
{
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
