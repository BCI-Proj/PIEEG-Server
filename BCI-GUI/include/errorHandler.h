#pragma once

#include <Windows.h>

inline VOID ErrorPop(const wchar_t* message)
{
	MessageBox(
		GetActiveWindow(), 
		L"Error Occured", 
		message, 
		MB_ICONERROR
	);
}