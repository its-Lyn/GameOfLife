#pragma once

#include <raylib.h>

class KeyBindPanel
{
private:
	Rectangle m_size;

	float m_opacity;
	bool m_enabled;
public:

	KeyBindPanel(float x, float y, float width, float height);

	void OnWindowResize(float x, float y, float width, float height);
	void Update();
	void Draw();
};
