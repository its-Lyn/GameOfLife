#pragma once

struct game_data {
    bool paused;
    int generations;

    float timer = 0;
    float time_out = 0.1f;
};