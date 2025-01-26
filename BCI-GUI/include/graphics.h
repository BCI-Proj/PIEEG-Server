#pragma once

#include <functional>

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

class Graphics
{
private:
	int mWidth				 = 0;
	int mHeight				 = 0;
	
	SDL_Window*	  mWindow    = nullptr;
	SDL_Renderer* mRenderer  = nullptr;

	bool		  mIsRunning = true;
	
public:
	Graphics(int width, int height) 
		: mWidth(width), mHeight(height)
	{
		InitSDL();
		InitImGui();
	}

	void InitSDL();
	void InitImGui();
	void Loop(const std::function<void()>& toRender);
	void Cleanup();
};