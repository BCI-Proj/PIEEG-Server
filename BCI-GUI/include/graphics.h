#pragma once

#include <functional>

#include <SDL.h>
#include <menu.h>

class Graphics
{
private:
	int m_width = 0;
	int m_height = 0;

	SDL_Window*   m_pWindow = nullptr;
	SDL_Renderer* m_pRenderer = nullptr;

	bool		  m_IsRunning = true;

	void InitSDL();
	void InitImGui();
	void SetupImGuiStyle();
	void Cleanup();

public:
	Graphics(int width, int height)
		: m_width(width), m_height(height)
	{
		InitSDL();
		InitImGui();
	}

	void Loop(const std::function<void()>& toRender);
};