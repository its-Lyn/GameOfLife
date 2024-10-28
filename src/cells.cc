#include <cells.hh>

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

void Cells::handle(Vector2 current, Vector2 previous)
{
    // Mouse moved
    if (!Vector2Equals(current, previous))
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
                this->set_cell(x, y, DEAD, this->m_dead);
                break;
            case ALIVE:
                this->message = std::format("Cell ({}, {})\nStatus: Alive", x, y);
                break;
        }
    }

    if (this->m_dead != nullptr)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            this->alive.push_back(this->m_dead.get()->position);
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