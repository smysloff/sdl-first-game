#include "config.hpp"

const int   TILE_SIZE          = 32;
const int   TILES_IN_ROW       = 64;
const int   TILES_IN_COL       = 40;

const char* WINDOW_TITLE       = "SDL2 Simple Game";
const int   WINDOW_POS_X       = SDL_WINDOWPOS_CENTERED;
const int   WINDOW_POS_Y       = SDL_WINDOWPOS_CENTERED;
const int   WINDOW_WIDTH       = 1280;
const int   WINDOW_HEIGHT      = 768;
const int   WINDOW_FLAGS       = SDL_WINDOW_SHOWN;

const char* FONT               = "fonts/8bitOperatorPlus8-Regular.ttf";

const int   HALF_TILE_SIZE     = TILE_SIZE     / 2;
const int   HALF_WINDOW_WIDTH  = WINDOW_WIDTH  / 2;
const int   HALF_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;
const int   WINDOW_CENTER_X    = HALF_WINDOW_WIDTH;
const int   WINDOW_CENTER_Y    = HALF_WINDOW_HEIGHT;
const int   DOUBLE_TILE_SIZE   = TILE_SIZE     * 2;
const int   TRIPLE_TILE_SIZE   = TILE_SIZE     * 3;
