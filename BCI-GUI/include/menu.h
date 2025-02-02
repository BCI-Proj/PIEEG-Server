#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <vector>
#include <string>
#include <iostream>

#include "pieeg.h"

namespace Menu
{
	using ChannelsArray = std::array<float, 9>;

	// Booleans that refer to training actioners ( last letter refert to direction )
	inline bool is_activet = false;
	inline bool is_activeb = false;
	inline bool is_activel = false;
	inline bool is_activer = false;
	inline bool is_paused  = false;

	// For saving training buttons order
	enum TrainingDirection
	{
		kTop,
		kBottom,
		kLeft,
		kRight
	};

	struct Graph
	{
		ImVector<ChannelsArray> data;
		const int maximum_size;
		const int remove_amount = 0.1f * maximum_size; // remove 10% 

		Graph(int _max)
			: maximum_size(_max)
		{
			data.reserve(maximum_size); // Set capacity to maximum
		};

		inline void Add(ChannelsArray arr)
		{
			data.push_back(arr);

			// Remember to check index of elements
			if (data.size() >= maximum_size)
				data.erase(data.begin(), data.begin() + remove_amount); // Removed N oldest
		}
	};

	#pragma region Custom Components
	
	// Component used to display channels graph on interface
	void ChannelGraph();

	// Actioner in training view
	void TrainingActioner(TrainingDirection direction, bool* b_value);

	// Component used to display multiple Actioners in multiple directions
	void TrainingView();

	#pragma endregion

	void ShowMenu();
}
