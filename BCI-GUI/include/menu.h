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
	inline bool bActionerT = false;
	inline bool bActionerB = false;
	inline bool bActionerL = false;
	inline bool bActionerR = false;
	inline bool bPaused    = false;

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
		const int maximumSize;
		const int removeAmount = 0.1f * maximumSize; // remove 10% 

		Graph(int max)
			: maximumSize(max)
		{
			data.reserve(maximumSize); // Set capacity to maximum
		};

		inline void Add(ChannelsArray arr)
		{
			data.push_back(arr);

			// Remember to check index of elements
			if (data.size() >= maximumSize)
				data.erase(data.begin(), data.begin() + removeAmount); // Removed N oldest
		}
	};

	#pragma region Custom Components
	
	// Component used to display channels graph on interface
	void ChannelGraph();

	// Actioner in training view
	void TrainingActioner(TrainingDirection direction, bool* bValue);

	inline void PlaceActioner(float posX, float posY, TrainingDirection direction)
	{
		
	}

	// Component used to display multiple Actioners in multiple directions
	void TrainingView();

	#pragma endregion

	void ShowMenu();
}
