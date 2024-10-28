#pragma once

#include <raylib.h>

#define CELL_SIZE 8

#define MAP_WIDTH 60
#define MAP_HEIGHT 60

#define MAP_WIDTH_PX (CELL_SIZE * MAP_WIDTH)
#define MAP_HEIGHT_PX (CELL_SIZE * MAP_HEIGHT)

#define DEAD 0
#define ALIVE 1

#define GRID_COLOUR DARKGRAY