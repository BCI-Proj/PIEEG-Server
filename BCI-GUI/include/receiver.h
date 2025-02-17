#pragma once

#include <iostream>
#include <winsock2.h>

#define WS_CLEAN() WSACleanup(); return 1;
#define WS_ERROR(message) std::printf(message, WSAGetLastError());

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
	Receiver(int port, char* recvBuffer, int bufferLen)
		: m_port(port)
	{
		if (!Init())         return;
		if (!CreateSocket()) return;
		if (!BindSocket())   return;
	}
	bool ReceiveFromSender(char* buffer, int bufferLen);
};