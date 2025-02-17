#include "receiver.h"

bool Receiver::Init()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0)
	{
		WS_ERROR("CANT INIT WSA - %d\n");
		WS_CLEAN();
	}

	m_receiverAddr.sin_port        = htons(m_port);
	m_receiverAddr.sin_family      = AF_INET;
	m_receiverAddr.sin_addr.s_addr = INADDR_ANY;

	return 0;
}

bool Receiver::CreateSocket()
{
	SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET)
	{
		WS_ERROR("CANT CREATE SOCKET - %d\n");
		WS_CLEAN();
	}

	m_socket = serverSocket;

	return 0;
}

bool Receiver::BindSocket()
{
	int result = bind(
		m_socket, reinterpret_cast<sockaddr*>(&m_receiverAddr), sizeof(m_receiverAddr));

	if (result == SOCKET_ERROR)
	{
		WS_ERROR("BIND FAILED - %d\n");
		closesocket(m_socket);
		WS_CLEAN();
	}
	return 0;	
}

bool Receiver::ReceiveFromSender()
{
	int bufferLen = sizeof(m_buffer); 
	int result    = recvfrom(m_socket, m_buffer, bufferLen, 0, reinterpret_cast<sockaddr*>(&m_clientAddr), &m_clientAddrLen);

	if (result == SOCKET_ERROR)
	{
		WS_ERROR("RECEIVING FAILED - %d\n");
		closesocket(m_socket);
		WS_CLEAN();
	}
	m_buffer[bufferLen - 1] = '\0';
	std::printf("buffer : %s \n", m_buffer);

	return 0;
}
