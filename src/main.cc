#include <cmath>
#include <cstdio>

#include <memory>
#include <format>

#include <raylib.h>
#include <raymath.h>

#include "definitions.hh"
#include "cells.hh"
#include "game_data.hh"

void draw_grid()
{
    for (int i = 0; i <= MAP_WIDTH; i++) DrawRectangleLines(0, CELL_SIZE * i, MAP_WIDTH_PX, 1, GRID_COLOUR);
    for (int i = 0; i <= MAP_WIDTH; i++) DrawRectangleLines(CELL_SIZE * i, 0, 1, MAP_HEIGHT_PX, GRID_COLOUR);
}

int main(void)  
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Game Of Life");

    Camera2D game_camera = {};

    game_camera.target = (Vector2) { (float)MAP_WIDTH_PX / 2, (float)MAP_HEIGHT_PX / 2 };
    game_camera.offset = (Vector2) { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    game_camera.rotation = 0.0f;
    game_camera.zoom = 2.0f;

    Vector2 mouse_screen = GetScreenToWorld2D(GetMousePosition(), game_camera);
    Vector2 previous_mouse = mouse_screen;

    std::unique_ptr<game_data> data = std::make_unique<game_data>();
    data->paused = true;
    data->generations = 0;

    Cells cells = Cells();
    cells.alive.push_back((Vector2) { 29, 29});
    cells.alive.push_back((Vector2) { 30, 30 });
    cells.alive.push_back((Vector2) { 28, 31 });
    cells.alive.push_back((Vector2) { 29, 31 });
    cells.alive.push_back((Vector2) { 30, 31 });

    cells.populate();

    while (!WindowShouldClose())    
    {
        Vector2 mouse_screen = GetScreenToWorld2D(GetMousePosition(), game_camera);

        if (IsKeyPressed(KEY_P)) data->paused = !data->paused;
     
        // The camera will stay focused on the same point, even though the window is resized.
        game_camera.offset = (Vector2) { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }; 

        // Handle camera zoom
        if (GetMouseWheelMove() != 0)
        {
            game_camera.zoom += (float)GetMouseWheelMove() * 0.05f;

            if (game_camera.zoom > 4.0f) game_camera.zoom = 4.0f;
            else if (game_camera.zoom < 1.0f) game_camera.zoom = 1.0f;
        }

        // Camera dragging
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
            game_camera.target = Vector2Subtract(game_camera.target, Vector2Scale(GetMouseDelta(), 1.0f / game_camera.zoom));

        cells.handle(mouse_screen, previous_mouse);

        previous_mouse = mouse_screen;

        if (!data->paused)
        {
            data->timer += GetFrameTime();
            if (data->timer >= data->time_out)
            {
                data->timer = 0;

                data->generations++;
                cells.advance_generation();
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(game_camera);
                cells.draw_alive();    
                draw_grid();
            EndMode2D();

            if (data->paused)
            {
                Vector2 measurements = MeasureTextEx(GetFontDefault(), "PAUSED", 20, 1);
                DrawText("PAUSED", GetScreenWidth() - measurements.x - 10, 5, 20, RED);
            }
            else
            {
                Vector2 measurements = MeasureTextEx(GetFontDefault(), "RUNNING", 20, 1);
                DrawText("RUNNING", GetScreenWidth() - measurements.x - 10, 5, 20, GREEN);
            }

            DrawText(cells.message.c_str(), 5, 5, 20, RAYWHITE);
            DrawText(std::format("Generations {}", data->generations).c_str(), 5, 40, 20, RAYWHITE);
            DrawFPS(5, GetScreenHeight() - 20);
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS; 
}