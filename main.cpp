#include <iostream>

#include "SDL_include.h"
#include "TileMap.h"
#include "FPS.h"

using std::cerr;
using std::endl;

const int   TILE_SIZE       = 32;
const int   TILES_IN_ROW    = 64;
const int   TILES_IN_COL    = 40;

const char* WINDOW_TITLE    = "SDL2 Simple Game";
const int   WINDOW_POS_X    = SDL_WINDOWPOS_CENTERED;
const int   WINDOW_POS_Y    = SDL_WINDOWPOS_CENTERED;
const int   WINDOW_WIDTH    = 1280;
const int   WINDOW_HEIGHT   = 720;
const int   WINDOW_FLAGS    = SDL_WINDOW_SHOWN;

//const int   WINDOW_CENTER_X = WINDOW_WIDTH / 2;  // 562
//const int   WINDOW_CENTER_Y = WINDOW_HEIGHT / 2; // 320

bool init(
  SDL_Window*& window, SDL_Renderer*& renderer, const Uint8*& keyStates);

void cleanup(SDL_Window*& window, SDL_Renderer*& renderer);


int main()
{
  SDL_Event event;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  const Uint8* keyStates = nullptr;

  if (! init(window, renderer, keyStates) )
    return -1;

  FPS fps;
  TileMap tileMap(renderer, TILES_IN_ROW, TILES_IN_COL, TILE_SIZE);

  int x = TILES_IN_ROW * TILE_SIZE / 2;
  int y = TILES_IN_COL * TILE_SIZE / 2;

  bool left = false;
  bool right = false;
  bool up = false;
  bool down = false;

  for (bool loop = true; loop; )
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        loop = false;
        break;
      }

      if (event.type == SDL_KEYDOWN)
      {
        if (keyStates[SDL_SCANCODE_ESCAPE])
        {
          loop = false;
          break;
        }

        if (keyStates[SDL_SCANCODE_LEFT] || keyStates[SDL_SCANCODE_A])
          left = true;

        if (keyStates[SDL_SCANCODE_RIGHT] || keyStates[SDL_SCANCODE_D]) 
          right = true;

        if (keyStates[SDL_SCANCODE_UP] || keyStates[SDL_SCANCODE_W])
          up = true;

        if (keyStates[SDL_SCANCODE_DOWN] || keyStates[SDL_SCANCODE_S])
          down = true;
      }
      
      if (event.type == SDL_KEYUP)
      {
        if (!keyStates[SDL_SCANCODE_LEFT] && !keyStates[SDL_SCANCODE_A])
          left = false;

        if (!keyStates[SDL_SCANCODE_RIGHT] && !keyStates[SDL_SCANCODE_D]) 
          right = false;

        if (!keyStates[SDL_SCANCODE_UP] && !keyStates[SDL_SCANCODE_W])
          up = false;

        if (!keyStates[SDL_SCANCODE_DOWN] && !keyStates[SDL_SCANCODE_S])
          down = false;
      }
 
    }


    if (fps.getCount() == 1)
      std::cout << "fps: " << fps.getValue() << endl;
    fps.update();

    if (left)  --x;
    if (right) ++x;
    if (up)    --y;
    if (down)  ++y;

    if (x < WINDOW_WIDTH / 2)
      x = WINDOW_WIDTH / 2;
    
    if (x > tileMap.getWidth() - WINDOW_WIDTH / 2)
      x = tileMap.getWidth() - WINDOW_WIDTH / 2;

    if (y < WINDOW_HEIGHT / 2)
      y = WINDOW_HEIGHT / 2;
    
    if (y > tileMap.getHeight() - WINDOW_HEIGHT / 2)
      y = tileMap.getHeight() - WINDOW_HEIGHT / 2;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    tileMap.render(renderer, x, y, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_RenderPresent(renderer);
  }

  cleanup(window, renderer);
}


bool init(
  SDL_Window*& window, SDL_Renderer*& renderer, const Uint8*& keyStates
) {
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
