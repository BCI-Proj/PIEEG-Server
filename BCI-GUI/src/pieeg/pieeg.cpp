#include "pieeg.h"

using namespace PIEEG;

Channels PIEEG::RetrieveData(float delta_time)
{
	// Method call to receive from UDP should be here
	Channels chns(delta_time, 10.2f, 42.4f, 100.3f, 86.2f, 67.5f, 48.2f, 123.7f, 23.4f);
	return chns;
}