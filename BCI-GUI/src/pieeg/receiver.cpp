#include "pieeg/receiver.h"
#include "globals.h"
#include "json.hpp"

void Receiver::Init()
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0)
	{
		WS_ERROR(L"CANT INIT WSA\n")
		WS_CLEAN()
	}

	m_receiverAddr.sin_port        = htons(m_port);
	m_receiverAddr.sin_family      = AF_INET;
	m_receiverAddr.sin_addr.s_addr = INADDR_ANY;
}

void Receiver::CreateSocket()
{
	SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket == INVALID_SOCKET)
	{
		WS_ERROR(L"CANT CREATE SOCKET");
		WS_CLEAN();
	}

	m_socket = serverSocket;
}

void Receiver::BindSocket()
{
	int result = bind(
		m_socket, reinterpret_cast<sockaddr*>(&m_receiverAddr), sizeof(m_receiverAddr));
	
	if (result == SOCKET_ERROR)
	{
		WS_ERROR(L"BIND FAILED");
		closesocket(m_socket);
		WS_CLEAN();
	}
}

void Receiver::ReceiveFromSender()
{
	int result = recvfrom(m_socket, reinterpret_cast<char*>(buffer), Globals::kNumElectrodes * sizeof(float), 0, reinterpret_cast<sockaddr*>(&m_clientAddr), &m_clientAddrLen);

	if (result == SOCKET_ERROR)
	{
		WS_ERROR(L"Can't receive anything");
		closesocket(m_socket);
		WS_CLEAN();
	}
	for (int i = 0; i < Globals::kNumElectrodes; i++)
	{
		chunk.lines[i].values.data()[inBatchNumber] = buffer[i];
		Utility::document[std::to_string(chunk.id)][std::to_string(i)] = buffer[i];
	}
	inBatchNumber++;
	
	if (inBatchNumber == 250)
	{
		inBatchNumber = 0;
		Utility::document[std::to_string(chunk.id)]["target"] = "baseline";
		chunk.id+=1;
	}

	if (chunk.id == 200)
	{
		Utility::SaveToJson("test.json");
	}

#ifdef _DEBUG
	// Display all received values in console
	
	// Number of channels is Hardcoded here because I dont want to include globals.h 
	for (int i = 0; i < 8; i++)
	{
		std::printf("Channel %d : %f \n", i, buffer[i]);
		std::printf("Batch number : %d \n", inBatchNumber);
		std::printf("Chunk id: %d \n", chunk.id);

		std::cout << Utility::document.dump(4) << "\n";
	}
#endif
}
