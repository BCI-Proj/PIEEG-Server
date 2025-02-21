#include "graphics.h"
#include "menu.h"
#include <thread>

int main(int argc, char** argv) 
{
	Graphics panel(800, 600);

	std::thread t_udp(
		[&]()
		{
			while (panel.IsRunning)
			{
				PIEEG::receiver.ReceiveFromSender();
			}
		});

	panel.Loop();
	
	t_udp.join();
	return 0;
}