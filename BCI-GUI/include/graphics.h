#pragma once

#include <functional>

#include <SDL.h>
#include <menu.h>

class Graphics
{
private:
	int m_width = 0, m_height = 0;

	SDL_Window*   m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	void InitSDL();
	void InitImGui();
	void Cleanup();

public:
	bool IsRunning = true;

	Graphics(int width, int height)
		: m_width(width), m_height(height)
	{
		InitSDL();
		InitImGui();
	}

	void Loop();
};