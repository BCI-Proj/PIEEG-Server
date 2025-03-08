#pragma once

#include <array>
#include "receiver.h"
#include "globals.h"

using ChannelsArray = std::array<float, Globals::kNumElectrodes + 1>;

namespace PIEEG
{
	inline Receiver receiver(Globals::kPort, Globals::kNumElectrodes);

	struct Channels
	{
		ChannelsArray vals = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

		Channels() = default;
		Channels(const float* deltaTime, const float* buff)
			: vals{ {*deltaTime, buff[0],buff[1],buff[2],buff[3],buff[4],buff[5],buff[6],buff[7]} }
		{};
	};
}
