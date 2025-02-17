#pragma once

#include <array>
#include "receiver.h"

namespace PIEEG
{
	inline constexpr uint8_t kNumElectrodes = 8;

	Receiver receiver;

	struct Channels
	{
		// Num of electrodes + 1 to handle the delta time in addition
		std::array<float, kNumElectrodes + 1> vals = {};

		Channels(float deltaTime, float c1, float c2, float c3, float c4, float c5, float c6, float c7, float c8)
			: vals{ {deltaTime, c1,c2,c3,c4,c5,c6,c7,c8} }
		{};
	};

	Channels RetrieveData(float deltaTime);
}
