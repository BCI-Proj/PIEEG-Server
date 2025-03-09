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

	/// Ptr to SDL_Window   - The Window
	SDL_Window*	  m_pWindow = nullptr;   

	/// Ptr to SDL_Renderer - The Renderer used to display element on the window
	SDL_Renderer* m_pRenderer = nullptr; 

	/// <summary>
	/// Initialise SDL2 Window + Renderer
	/// </summary>
	void InitSDL();

	/// <summary>
	/// Initialise ImGui using created SDL2 Window
	/// </summary>
	void InitImGui() const;

	/// <summary>
	/// Change default style of ImGui
	/// </summary>
	void SetupImGuiStyle() const;

	/// <summary>
	/// Destroy ImGui + ImPlot + SDL2
	/// </summary>
	void Cleanup() const;

public:
	bool IsRunning = true;

	Graphics(uint16_t width, uint16_t height)
		: m_width(width), m_height(height)
	{
		InitSDL();
		InitImGui();
	}

	/// <summary>
	/// The main program loop where everything will occur
	/// </summary>
	void Loop();
};