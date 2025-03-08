#pragma once

#include <SDL.h>
#include "menu.h"

/// <summary>
/// To manage everything related to graphics. EX: Window, Render, UI...
/// </summary>
class Graphics
{
private:
	int m_width  = 0;
	int m_height = 0;

	SDL_Window*	  m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	// Initialise SDL2 Window + Renderer
	void InitSDL();

	// Initialise ImGui using created SDL2 Wnd
	void InitImGui() const;

	// Change default style of ImGui
	void SetupImGuiStyle() const;

	// Destroy ImGui + ImPlot + SDL2
	void Cleanup() const;

public:
	bool IsRunning = true;

	Graphics(uint16_t width, uint16_t height)
		: m_width(width), m_height(height)
	{
		InitSDL();
		InitImGui();
	}

	// The main program loop where everything will occur
	void Loop();
};