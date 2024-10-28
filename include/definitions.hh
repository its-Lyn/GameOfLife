#pragma once

#include <raylib.h>

#define CELL_SIZE 8

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

#define MAP_WIDTH_PX (CELL_SIZE * MAP_WIDTH)
#define MAP_HEIGHT_PX (CELL_SIZE * MAP_HEIGHT)

#define DEAD 0
#define ALIVE 1

#define GRID_COLOUR DARKGRAY