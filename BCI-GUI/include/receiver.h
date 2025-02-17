#pragma once

#include <iostream>
#include <winsock2.h>

#define WSA_CLEAN() WSACleanup(); return 1;

class Receiver
{
private:
	int	m_port;

	SOCKET m_socket = 0;

	sockaddr_in
		m_receiverAddr = {},
		m_clientAddr   = {};

	int m_clientAddrLen = sizeof(m_clientAddr);

public:
	Receiver(int port, char* recvBuffer, int bufferLen)
		: m_port(port)
	{
		if (!Init())         return;
		if (!CreateSocket()) return;
		if (!BindSocket())   return;

		ReceiveFromSender(recvBuffer, bufferLen);
	}

	bool  Init();
	bool  CreateSocket();
	bool  BindSocket();
	bool  ReceiveFromSender(char* buffer, int bufferLen);
};