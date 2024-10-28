#pragma once

#include <raylib.h>
#include <raymath.h>

#include <cmath>

#include <format>
#include <string>

#include <iostream>
#include <memory>
#include <vector>

#include "definitions.hh"
#include <cell.hh>

class Cells 
{
private:
    std::unique_ptr<Cell> m_dead = nullptr;
    void set_cell(int x, int y, int state, std::unique_ptr<Cell>& cell);

public:
    std::string message;

    uint8_t cells[MAP_WIDTH][MAP_HEIGHT] = {};
    std::vector<Vector2> alive;

    void populate();
    void handle(Vector2 current, Vector2 previous);

    void draw_alive();
};