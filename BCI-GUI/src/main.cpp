#include "graphics.h"
#include "menu.h"

int main(int argc, char** argv) 
{
	Graphics panel(800, 600);

	panel.Loop
	(
		[&]()
		{
			Menu::ShowMenu();
		}
	);

	return 0;
}