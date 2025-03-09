#pragma once

#include <array>
#include "receiver.h"
#include "globals.h"

/// <summary>
/// ChannelArray is a typedef that correspond to an array that contain floats data coming from the electrodes & the delta time
/// </summary>
using ChannelsArray = std::array<float, Globals::kNumElectrodes + 1>;

/// <summary>
/// Namespace that contain what's needed to gather data from the PIEEG module
/// </summary>
namespace PIEEG
{
	/// <summary>
	/// Receiver that act as UDP Server to receive data coming from the client in the RaspberryPi 
	/// </summary>
	/// <param name="port">The port to open UDP Server</param>
	/// <param name="bufferLen">The number of electrodes used</param>
	inline Receiver receiver(Globals::kPort, Globals::kNumElectrodes);

	/// <summary>
	/// Struct to handle values coming from PIEEG + DeltaTime - 
	/// Used to keep track when displayed on graph so we know when a chunk of data has been received
	/// </summary>
	struct Channels 
	{
		ChannelsArray vals = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

		Channels() = default;
		Channels(const float* deltaTime, const float* buff)
			: vals{ {*deltaTime, buff[0],buff[1],buff[2],buff[3],buff[4],buff[5],buff[6],buff[7]} }
		{};
	};
}
