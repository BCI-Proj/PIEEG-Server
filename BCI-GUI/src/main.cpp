#include "graphics.h"
#include "menu.h"
#include "receiver.h"

int main(int argc, char** argv) 
{
	
	Graphics panel(800, 600);
	PIEEG::receiver = Receiver(8888, PIEEG::kNumElectrodes);

	panel.Loop
	(
		[&]()
		{
			Menu::ShowMenu();
		}
	);

	return 0;
}