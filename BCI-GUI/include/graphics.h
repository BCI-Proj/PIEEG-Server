#pragma once

#include <functional>

#include <SDL.h>
#include <menu.h>

/// <summary>
/// To manage everything related to graphics. EX: Window, Render, UI...
/// </summary>
class Graphics
{
private:
	int m_width = 0, m_height = 0;

	SDL_Window*   m_pWindow   = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	// Initialise SDL2 Window + Renderer
	void InitSDL();

	// Initialise ImGui using created SDL2 Wnd
	void InitImGui();

	// Destroy ImGui + ImPlot + SDL2
	void Cleanup();

public:
	bool IsRunning = true;

	Graphics(int width, int height)
		: m_width(width), m_height(height)
	{
		InitSDL();
		InitImGui();
	}

	// The main program loop where everything will occur
	void Loop();
};