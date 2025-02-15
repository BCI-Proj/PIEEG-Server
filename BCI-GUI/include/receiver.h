#pragma once

#include <winsock2.h>
#include <cstdio>

class Receiver
{
private:
	int	m_port;

	SOCKET m_socket = 0;

	sockaddr_in
		m_receiverAddr = {},
		m_clientAddr = {};

public:
	Receiver(int port, char* buffer, int bufferLen)
		: m_port(port)
	{
		if (!Init())         return;
		if (!CreateSocket()) return;
		if (!BindSocket())   return;

		ReceiveFromSender(buffer, bufferLen);
	}

	int	 Init();
	int  CreateSocket();
	int  BindSocket();
	int  ReceiveFromSender(char* buffer, int bufferLen);
};