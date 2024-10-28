#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "definitions.hh"
#include "cell.hh"

class Cells 
{
private:
    std::unique_ptr<Cell> m_active = nullptr;
    void set_cell(int x, int y, int state, std::unique_ptr<Cell>& cell);

    void handle_mouse(Vector2 current);

    bool remove_at(Vector2 position);
    int get_neighbour_count(int x, int y);

    const int neighbor_offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

public:
    std::string message;

    uint8_t cells[MAP_WIDTH][MAP_HEIGHT] = {};
    std::vector<Vector2> alive;

    void advance_generation();

    void populate();
    void handle(Vector2 current, Vector2 previous);

    void draw_alive();
};