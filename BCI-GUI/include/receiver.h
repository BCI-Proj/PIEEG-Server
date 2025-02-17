#pragma once

#include <iostream>
#include <winsock2.h>

#define WS_CLEAN() WSACleanup(); return 1;
#define WS_ERROR(message) std::printf(message, WSAGetLastError());

class Receiver
{
private:
	int	    m_port;
	char*   m_buffer; // buffer for the data of the electrodes ( NOT char*, should be changed ) 

	SOCKET m_socket = 0;

	sockaddr_in
		m_receiverAddr = {},
		m_clientAddr   = {};

	int m_clientAddrLen = sizeof(m_clientAddr);

	bool  Init();
	bool  CreateSocket();
	bool  BindSocket();

public:
	Receiver() = default;
	Receiver(int port, int bufferLen)
		: m_port(port), m_buffer(new char[bufferLen])
	{
		if (!Init())         return;
		if (!CreateSocket()) return;
		if (!BindSocket())   return;
	}
	bool ReceiveFromSender();
};