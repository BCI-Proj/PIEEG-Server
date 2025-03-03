#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/// <summary>
/// Commonly used variables. The're defined and compile time.
/// </summary>
namespace Globals
{
	inline constexpr UINT16 kPort = 8888;
	inline constexpr UINT8  kNumElectrodes = 8;
}

/// <summary>
/// Pop an info box on the screen. Used to display Error Message
/// </summary>
inline VOID Info(LPCWSTR title, LPCWSTR message, UINT icon)
{
	MessageBox(
		GetActiveWindow(),
		title,
		message,
		icon
	);
	//Beep(750, 300);
}