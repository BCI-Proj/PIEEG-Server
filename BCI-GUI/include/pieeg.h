#pragma once

#include <array>
#include "receiver.h"
#include "globals.h"

namespace PIEEG
{
	inline Receiver receiver(Globals::kPort, Globals::kNumElectrodes);

	struct Channels
	{
		// Num of electrodes + 1 to handle the delta time in addition
		std::array<float, 8+ 1> vals = {};

		Channels() = default;
		Channels(float deltaTime, float* buff)
			: vals{ {deltaTime, buff[0],buff[1],buff[2],buff[3],buff[4],buff[5],buff[6],buff[7]} }
		{};
	};

	Channels RetrieveData(float deltaTime);
}
