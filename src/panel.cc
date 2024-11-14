#include "entities/panel.hh"

KeyBindPanel::KeyBindPanel(float x, float y, float width, float height)
{
	this->m_size = Rectangle{x, y, width, height};

	this->m_opacity = 0;
	this->m_enabled = false;
}

void KeyBindPanel::Update()
{
	if (IsKeyDown(KEY_LEFT_CONTROL))
	{
		if (IsKeyPressed(KEY_K))
		{
			this->m_enabled = !this->m_enabled;
		}
	}

	if (this->m_enabled)
	{
		this->m_opacity += 5 * GetFrameTime();
		if (this->m_opacity >= 1)
		{
			this->m_opacity = 1;
			return;
		}
	}
	else
	{
		this->m_opacity -= 5 * GetFrameTime();
		if (this->m_opacity <= 0)
		{
			this->m_opacity = 0;
			return;
		}
	}
}

void KeyBindPanel::Draw()
{
	DrawRectangleRec(this->m_size, Fade(BLACK, this->m_opacity));
	DrawRectangleLinesEx(this->m_size, 3, Fade(GRAY, this->m_opacity));

	DrawText("KeyBinds", this->m_size.width / 2 + 30, this->m_size.y + 5, 30, Fade(WHITE, this->m_opacity));
}

void KeyBindPanel::OnWindowResize(float x, float y, float width, float height)
{
	if (!IsWindowResized()) return;
	this->m_size = Rectangle{x, y, width, height};
}
