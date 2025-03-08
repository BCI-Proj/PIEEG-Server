#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <string>
#include <iostream>
#include <unordered_map>

#include "pieeg/pieeg.h"

#pragma warning(disable: 4996)

namespace Menu
{
	inline bool
		actionerT      = false,
		actionerB      = false,
		actionerL      = false,
		actionerR      = false,
		actionerC      = false,
		actionerHidden = false; // hide all actioners around the center (for pre-session training)

	inline bool			 
		isPaused		  = false, 
		isTrainingStarted = false;

	inline		     int      maxLoggingCount =  300;
	inline constexpr uint16_t maxGraphCount   = 3000;

	enum TrainingDirection 
	{
		kTop,
		kBottom,
		kLeft,
		kRight,
		kCenter
	};

	inline std::unordered_map<TrainingDirection, ImVec2> positionsMap =
	{
		{kTop,		ImVec2(0.5,  0.0f)},
		{kBottom,	ImVec2(0.5,  1.0f)},
		{kLeft,		ImVec2(0.0f, 0.5f)},
		{kRight,	ImVec2(1.0f, 0.5f)},
		{kCenter,	ImVec2(0.5f, 0.5f)}
	};

	/// <summary>
	/// Struct that dynamically remove oldest values (a certain percent is removed)
	/// </summary>
	struct Graph
	{
		ImVector<ChannelsArray> data;

		const uint16_t maximumSize;
		const uint16_t removeAmount = static_cast<uint16_t>(0.1f * maximumSize); // remove 10% of maximum size

		explicit Graph(uint16_t max)
			: maximumSize(max)
		{
			data.reserve(maximumSize); // Set capacity to maximum
		};

		inline void Add(const ChannelsArray& arr)
		{
			data.push_back(arr);

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
	void ChannelGraph();

	/// <summary>
	/// Custom ImGui component that act as indicators. Can flash in green
	/// </summary>
	/// <param name="direction"> - where it should be placed</param>
	/// <param name="pBoolean"> - active or not</param>
	void TrainingActioner(const TrainingDirection direction, bool* pBoolean);

	/// <summary>
	/// Contain all placed Actioners
	/// </summary>
	void TrainingView();

	/// <summary>
	/// Contain coming values from channels
	/// </summary>
	void LoggingView();

	/// <summary>
	/// Contain profile loader
	/// </summary>
	void ProfileView();

	/// <summary>
	/// Position Actioners in equal position depending on the direction (left, right ... ) 
	/// </summary>
	/// <param name="direction">Where the Actioner should be located</param>
	/// <param name="pBoolean">Ptr to bool that will be associated to this Actioner</param>
	inline void PositionActioner(const TrainingDirection direction, bool* pBoolean)
	{
		ImVec2 wndDimensions = ImGui::GetWindowSize(); // x refer to width, y refer to height
		
		ImGui::SetCursorPosX((wndDimensions.x - 30) * Menu::positionsMap[direction].x);
		ImGui::SetCursorPosY((wndDimensions.y - 50) * Menu::positionsMap[direction].y);

		TrainingActioner(direction, pBoolean);
	}

#pragma endregion

}
