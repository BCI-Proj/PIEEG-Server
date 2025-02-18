#include "pieeg.h"

using namespace PIEEG;

Channels PIEEG::RetrieveData(float deltaTime)
{
	// Method call to receive from UDP should be here
	if (!receiver.ReceiveFromSender())
		return Channels();

	float testBuffer [8] = {10.2f, 42.4f, 100.3f, 86.2f, 67.5f, 48.2f, 123.7f, 23.4f};
	
	Channels chns(deltaTime, testBuffer);
	return chns;
}
