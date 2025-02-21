#include "graphics.h"
#include "menu.h"
#include <thread>

int main(int argc, char** argv) 
{
	Graphics panel(800, 600);

	std::thread t_udpReceiver(
		[&]()
		{
			while (panel.IsRunning)
			{
				PIEEG::receiver.ReceiveFromSender();
			}
		});

	panel.Loop();

	// Detach and not join here to kill the thread because recvfrom function will wait until the next message before closing.
	t_udpReceiver.detach();
	return 0;
}