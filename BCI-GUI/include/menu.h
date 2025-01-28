#pragma once

#include <imgui.h>

namespace Menu 
{
	// booleans that refer to actioners
	inline bool is_activet = false;
	inline bool is_activeb = false;
	inline bool is_activel = false;
	inline bool is_activer = false;

	// For saving training buttons order
	enum Direction
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	#pragma region Custom Components
		
	void TrainingActioner(Direction direction, bool* b_value);
	void TrainingView();

	#pragma endregion

	void ShowMenu();
}
