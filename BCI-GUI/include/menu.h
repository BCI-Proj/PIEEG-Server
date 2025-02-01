#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <vector>
#include <string>
#include <array>
#include <iostream>

namespace Menu
{
	// Booleans that refer to training actioners
	inline bool is_activet      = false;
	inline bool is_activeb      = false;
	inline bool is_activel      = false;
	inline bool is_activer      = false;
	inline bool is_paused       = false;

	// For saving training buttons order
	enum Direction
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	#pragma region Custom Components
	
	void ChannelGraph();
	void TrainingActioner(Direction direction, bool* b_value);
	void TrainingView();

	#pragma endregion

	void ShowMenu();
}
