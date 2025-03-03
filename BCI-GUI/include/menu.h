#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <vector>
#include <string>
#include <iostream>

#include "pieeg.h"

#pragma warning(disable: 4996)

namespace Menu
{
	// Booleans that refer to training actioners ( last letter refer to direction )
	inline bool bActionerT       = false;
	inline bool bActionerB       = false;
	inline bool bActionerL       = false;
	inline bool bActionerR       = false;
	inline bool bActionerC		 = false;
	inline bool bHideActioner	 = false; // hide all actioners around the center (for pre-session training)

	inline bool bPaused			 = false;
	inline bool bTrainingStarted = false;

	// For saving training buttons order
	enum TrainingDirection 
	{
		kTop,
		kBottom,
		kLeft,
		kRight,
		kCenter
	};

	/// <summary>
	/// Struct that dynamically remove oldest values by keeping a 
	/// </summary>
	struct Graph
	{
		ImVector<ChannelsArray> data;
		const int maximumSize;
		const int removeAmount = static_cast<int>(0.1f * maximumSize); // remove 10% of maximum size

		explicit Graph(int max)
			: maximumSize(max)
		{
			data.reserve(maximumSize); // Set capacity to maximum
		};

		inline void Add(const ChannelsArray& arr)
		{
			data.push_back(arr);

			// Remember to check index of elements
			if (data.size() >= maximumSize)
				data.erase(data.begin(), data.begin() + removeAmount); // Removed N oldest
		}
	};

	/// <summary>
	/// Display the whole interface.
	/// </summary>
	void ShowMenu();

#pragma region Custom Components
	
	/// <summary>
	/// Graph used to monitor all electrodes channels coming values
	/// </summary>
	/// <param name="buffer"> - floats buffer of values received via UDP from the electrodes</param>
	void ChannelGraph(float* buffer);

	/// <summary>
	/// Custom ImGui component that act as indicators. Can flash in green
	/// </summary>
	/// <param name="direction"> - where it should be placed</param>
	/// <param name="pBoolean"> - active or not</param>
	void TrainingActioner(TrainingDirection direction, bool* pBoolean);

	/// <summary>
	/// Contain all placed Actioners
	/// </summary>
	void TrainingView();


	// To place Actioner in the Training View depending on direction
	inline void PositionActioner(ImVec2 wndDimensions, int* margins, TrainingDirection direction, bool* p_bValue)
	{
		ImVec2 cursorPos{};

		switch (direction)
		{
		case kTop:
			cursorPos = { 0.5f, 0.0f }; break;
		case kBottom:
			cursorPos = { 0.5f, 1.0f }; break;
		case kLeft:
			cursorPos = { 0.0f, 0.5f }; break;
		case kRight:
			cursorPos = { 1.0f, 0.5f }; break;
		case kCenter:
			cursorPos = { 0.5f, 0.5f }; break;
		default:
			cursorPos = { 0.0f, 0.0f }; break;
		}

		ImGui::SetCursorPosX((wndDimensions.x - margins[0]) * cursorPos.x);
		ImGui::SetCursorPosY((wndDimensions.y - margins[1]) * cursorPos.y);

		TrainingActioner(direction, p_bValue);
	}

#pragma endregion

}
