#pragma once

#include <array>

namespace PIEEG
{
	inline constexpr uint8_t kNumElectrodes = 8;

	struct Channels
	{
		// Num of electrodes + 1 to handle the delta time in addition
		std::array<float, kNumElectrodes + 1> vals = {};

		Channels(float _delta_time, float _c1, float _c2, float _c3, float _c4, float _c5, float _c6, float _c7, float _c8)
			: vals{ {_delta_time, _c1,_c2,_c3,_c4,_c5,_c6,_c7,_c8} }
		{};
	};

	Channels RetrieveData(float delta_time);
}
