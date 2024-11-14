#pragma once

struct game_data
{
	bool show_grid = true;

	bool paused = true;
	int generations = 0;

	float timer = 0;
	float time_out = 0.1f;
};
