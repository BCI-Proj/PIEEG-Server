#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "imgui.h";

/// <summary>
/// Commonly used variables.
/// </summary>
namespace Globals
{								
	/// The Accent color of Sema Cerebrum
	inline constexpr ImU32    kAccentColor   = IM_COL32(147, 129, 255, 255);
	/// The Port where to receive
	inline constexpr uint16_t kPort		     = 8888;
	/// The Number of electrodes connected to the PIEEG
	inline constexpr uint8_t  kNumElectrodes = 8;
}

/// <summary>
/// Pop an info box on the screen. Used to display Error Message or some information
/// </summary>
/// <param name="message">The message in the Info Box</param>
/// <param name="title">The title of the Info Box</param>
/// <param name="icon">The icon display the Info Box</param>
inline VOID Info(LPCWSTR message, LPCWSTR title, UINT icon)
{
	MessageBox(
		GetActiveWindow(),
		message,
		title,
		icon
	);
}