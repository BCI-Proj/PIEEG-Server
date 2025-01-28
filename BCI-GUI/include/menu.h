#pragma once

#include <imgui.h>

namespace Menu 
{
	// For saving training buttons order
	enum Direction
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	#pragma region Space for Custom Components
		
	void TrainingActioner(const char* label, bool* b_value);

	#pragma endregion

	void ShowMenu();
}
