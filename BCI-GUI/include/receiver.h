#pragma once

#include <iostream>
#include <winsock2.h>
#include "globals.h"

#define WS_CLEAN() WSACleanup(); return 1;
#define WS_ERROR(message) std::printf(message, WSAGetLastError());

/// <summary>
/// Used to handle Socket and address.
/// Act as a Winsock UDP Server.
/// </summary>
class Receiver
{
private:
	int	m_port;
	
	SOCKET m_socket = 0;

	sockaddr_in
		m_receiverAddr = {},
		m_clientAddr   = {};

	int m_clientAddrLen = sizeof(m_clientAddr);

	bool  Init();
	bool  CreateSocket();
	bool  BindSocket();

public:
	float* buffer; // buffer for the data of the electrodes 

	Receiver() = default;
	Receiver(int port, int bufferLen)
		: m_port(port), buffer(new float[bufferLen])
	{
		Init();
		CreateSocket();
		BindSocket();
	}

	/// <summary>
	/// Store received float values in Receiver buffer
	/// </summary>
	bool ReceiveFromSender();
};