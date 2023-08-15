#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "config.hpp"
#include "Controls.hpp"
#include "Entity.hpp"
#include "FPS.hpp"
#include "TileMap.hpp"
#include "utils.hpp"

int main()
{
  SDL_Event event;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  const Uint8* keyStates = nullptr;

  if (! init(window, renderer, keyStates) )
    return -1;

  TTF_Font* font = TTF_OpenFont(FONT, 24);
  if (!font)
  {
    std::cerr << "error: on TTF_OpenFont(). " << TTF_GetError() << std::endl;
    return -1;
  }

  FPS fps;
  Controls controls;
  TileMap tileMap(renderer, TILES_IN_ROW, TILES_IN_COL, TILE_SIZE);

  Entity character(HALF_WINDOW_WIDTH, HALF_WINDOW_HEIGHT + HALF_TILE_SIZE, 90);
  int character_width = TILE_SIZE * 2;
  int character_height = TILE_SIZE * 4;
  SDL_Texture* character_texture = IMG_LoadTexture(renderer, "img/char.png");
  SDL_Rect character_sprites[] = {
    {
      .x = character_width * 1, .y = 0,
      .w = character_width,     .h = character_height
    },
    { 
      .x = character_width * 2, .y = 0,
      .w = character_width,     .h = character_height
    },
    {
      .x = character_width * 0, .y = 0,
      .w = character_width,     .h = character_height
    },
    { 
      .x = character_width * 3, .y = 0, 
      .w = character_width,     .h = character_height
    }
  };
  double character_lasttime = fps.getTime();

  int camera_x = TILES_IN_ROW * HALF_TILE_SIZE;
  int camera_y = TILES_IN_COL * HALF_TILE_SIZE;

  for (bool loop = true; loop; )
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        loop = false;
        break;
      }

      if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
      {
        if (keyStates[SDL_SCANCODE_ESCAPE])
        {
          loop = false;
          break;
        }
        controls.update(keyStates);
      }

      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        int x, y;
        SDL_GetMouseState(&x, &y);
        character.setWaypoint(x, y);
      }
    }

    fps.update();
    character.update((fps.getTime() - character_lasttime) / 1000.);
    character_lasttime = fps.getTime();

    if (controls.left)  --camera_x;
    if (controls.right) ++camera_x;
    if (controls.up)    --camera_y;
    if (controls.down)  ++camera_y;

    if (camera_x < HALF_WINDOW_WIDTH)
      camera_x = HALF_WINDOW_WIDTH;
    
    if (camera_x > tileMap.getWidth() - HALF_WINDOW_WIDTH)
      camera_x = tileMap.getWidth() - HALF_WINDOW_WIDTH;

    if (camera_y < HALF_WINDOW_HEIGHT)
      camera_y = HALF_WINDOW_HEIGHT;
    
    if (camera_y > tileMap.getHeight() - HALF_WINDOW_HEIGHT)
      camera_y = tileMap.getHeight() - HALF_WINDOW_HEIGHT;

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    tileMap.render(renderer, camera_x, camera_y, WINDOW_WIDTH, WINDOW_HEIGHT);

    int number = 0;
    if (!character.isMoving())
      number = 0;

    else if (character.angle > 1 && character.angle < (M_PI - 1))
      number = 0;
    
    else if (character.angle < -1 && character.angle > (-M_PI + 1))
      number = 1;
  
    else if (character.angle >= (M_PI - 1) || character.angle <= (-M_PI + 1))
      number = 2;

    else if (character.angle >= -1 && character.angle <= 1)
      number = 3;
  
    if (character.isMoving())
    {
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderDrawLine(renderer,
        character.position.x, character.position.y,
        character.waypoint.x, character.waypoint.y);

      SDL_Rect dstRect = {
        .x = (int) character.waypoint.x - 3,
        .y = (int) character.waypoint.y - 3,
        .w = 7, .h = 7
      };
      SDL_RenderFillRect(renderer, &dstRect);
    }

    SDL_Rect* srcRect = &character_sprites[number];
    SDL_Rect  dstRect = {
      .x = (int) character.position.x - HALF_TILE_SIZE,
      .y = (int) character.position.y - TILE_SIZE,
      .w = TILE_SIZE,
      .h = DOUBLE_TILE_SIZE
    };
    SDL_RenderCopy(renderer, character_texture, srcRect, &dstRect);

    fps.render(renderer, font);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(character_texture);
  TTF_CloseFont(font);
  cleanup(window, renderer);
}
