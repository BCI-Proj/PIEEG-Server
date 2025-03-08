#pragma once

#include <iostream>
#include <winsock2.h>
#include "globals.h"

#define WS_CLEAN() WSACleanup(); return TRUE;
#define WS_ERROR(message) Info(message, (const wchar_t*)WSAGetLastError(), MB_ICONERROR);

/// <summary>
/// Used to handle Socket and address.
/// Act as a Winsock UDP Server.
/// </summary>
class Receiver
{
private:
	int	m_port;
	
	SOCKET m_socket = 0;

	sockaddr_in m_receiverAddr = {};
	sockaddr_in m_clientAddr   = {};

	int m_clientAddrLen = sizeof(m_clientAddr);

	bool  Init();		  /// Initialize Winsock2
	bool  CreateSocket(); /// Create UDP Server socket
	bool  BindSocket();	  /// Bind UDP Server socket

public:
	float* buffer; // buffer for the data of the electrodes 

	Receiver() = default;
	Receiver(const uint16_t port, const uint16_t bufferLen)
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