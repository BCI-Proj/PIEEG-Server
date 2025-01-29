#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <vector>
#include <array>


namespace Menu
{
	// Booleans that refer to training actioners
	inline bool is_activet = false;
	inline bool is_activeb = false;
	inline bool is_activel = false;
	inline bool is_activer = false;

	//	Struct that refer to all 8 channels. 8 for each electrode
	struct Channels
	{
		std::array<float, 8> vals = {};
		
		Channels(float _c1, float _c2, float _c3, float _c4, float _c5, float _c6, float _c7, float _c8)
			: vals{{_c1,_c2,_c3,_c4,_c5,_c6,_c7,_c8}} 
		{};
	};

	// For saving training buttons order
	enum Direction
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	#pragma region Custom Components
	
	void ChannelGraph(int numChannel);
	void TrainingActioner(Direction direction, bool* b_value);
	void TrainingView();

	#pragma endregion

	void ShowMenu();
}
