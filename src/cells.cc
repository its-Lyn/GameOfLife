#include <cells.hh>

#include <raymath.h>

#include <cmath>

#include <iostream>

#include <format>
#include <string>

void Cells::set_cell(int x, int y, int state, std::unique_ptr<Cell>& cell)
{
    if (cell == nullptr)
        cell = std::make_unique<Cell>();

    cell->position = (Vector2) { (float)x, (float)y };
    cell->state = state; 
}

void Cells::populate()
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            // This SURE IS FUCKING PERFORMANT....
            for (Vector2 position : this->alive)
            {
                if (x == position.x && y == position.y) 
                    cells[x][y] = ALIVE;
            }
        }
    }
}

void Cells::handle_mouse(Vector2 current)
{
    int x = (int)floor(current.x / 8);
    int y = (int)floor(current.y / 8); 
    
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
    {
        this->message = "The Void";
        return;
    }

    switch (this->cells[x][y])
    {
        case DEAD:
            this->message = std::format("Cell ({}, {})\nStatus: Dead", x, y);
            this->set_cell(x, y, DEAD, this->m_active);

            break;

        case ALIVE:
            this->message = std::format("Cell ({}, {})\nStatus: Alive", x, y);
            this->set_cell(x, y, ALIVE, this->m_active);

            break;
    }
}

void Cells::handle(Vector2 current, Vector2 previous)
{
    if (!Vector2Equals(current, previous)) this->handle_mouse(current);

    if (this->m_active != nullptr)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            switch (this->m_active->state)
            {
                case DEAD:
                    this->alive.push_back(this->m_active->position); 
                    break;
                
                case ALIVE:
                    bool success = this->remove_at(this->m_active->position);
                    if (!success)
                        std::cerr << "Could not remove for whatever reason.\n";

                    break;
            }

            this->populate();
        }
    }
}

void Cells::draw_alive()
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (this->cells[x][y] == ALIVE)
                DrawRectangle(x * 8, y * 8, CELL_SIZE, CELL_SIZE, YELLOW);
        }
    }
}

bool Cells::remove_at(Vector2 pos)
{
    auto iter = std::find_if(
        this->alive.begin(),
        this->alive.end(),
        [pos](const Vector2 &other) {
            return Vector2Equals(pos, other);
        }
    );

    if (iter != this->alive.end())
    {
        this->cells[(int)pos.x][(int)pos.y] = DEAD;
        this->alive.erase(iter);

        this->populate();
        return true;
    }

    return false;
}

int Cells::get_neighbour_count(int x, int y)
{
    int live_neighbors = 0;

    for (auto& offset : neighbor_offsets) {
        int nx = x + offset[0];
        int ny = y + offset[1];

        if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT) {
            if (cells[nx][ny] == ALIVE) {
                live_neighbors++;
            }
        }
    }


    return live_neighbors;
}

void Cells::advance_generation()
{
    int temp_cells[MAP_WIDTH][MAP_HEIGHT] = {};

    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            int count = this->get_neighbour_count(x, y);
            switch (cells[x][y])
            {
                case ALIVE:
                    if (count < 2 || count > 3)
                        temp_cells[x][y] = DEAD;
                    else
                        temp_cells[x][y] = ALIVE;

                    break;

                case DEAD:
                    if (count == 3)
                        temp_cells[x][y] = ALIVE;
                    else
                        temp_cells[x][y] = DEAD;

                    break;
            }
        }
    }

    this->alive.clear(); 
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            this->cells[x][y] = temp_cells[x][y];
            if (temp_cells[x][y] == ALIVE)
                this->alive.push_back((Vector2) { (float)x, (float)y });
        }
    }

    this->populate();
}