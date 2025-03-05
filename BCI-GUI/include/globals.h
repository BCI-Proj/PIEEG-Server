#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "imgui.h";

/// <summary>
/// Commonly used variables.
/// </summary>
namespace Globals
{										   
	inline constexpr ImU32  kAccentColor   = IM_COL32(147, 129, 255, 255);
	inline constexpr UINT16 kPort		   = 8888;
	inline constexpr UINT8  kNumElectrodes = 8;
}

/// <summary>
/// Pop an info box on the screen. Used to display Error Message or some information
/// </summary>
inline VOID Info(LPCWSTR message, LPCWSTR title, UINT icon)
{
	MessageBox(
		GetActiveWindow(),
		message,
		title,
		icon
	);
}