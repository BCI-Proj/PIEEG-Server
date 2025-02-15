#include "receiver.h"

int Receiver::Init()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0)
	{
		
		std::printf("Can't initialize WSA, Startup failed : %d\n", result);
		WSACleanup();
		return 1;
	}

	m_receiverAddr.sin_port        = htons(m_port);
	m_receiverAddr.sin_family      = AF_INET;
	m_receiverAddr.sin_addr.s_addr = INADDR_ANY;

	return 0;
}

int Receiver::CreateSocket()
{
	SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET)
	{
		std::printf("Error at socket %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	m_socket = serverSocket;

	return 0;
}

int Receiver::BindSocket()
{
	int result = bind(
		m_socket, reinterpret_cast<sockaddr*>(&m_receiverAddr), sizeof(m_receiverAddr));

	if (result == SOCKET_ERROR)
	{
		std::printf("Bind failed with error %d\n", WSAGetLastError());
		closesocket(m_socket);
		WSACleanup();
		return 1;
	}
	
	return 0;
}

int Receiver::ReceiveFromSender(char* buffer, int bufferLen)
{
	return 0;
}
