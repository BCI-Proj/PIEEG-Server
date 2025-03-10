#pragma once

#include <iostream>
#include <winsock2.h>
#include "utils/utility.h"

#define WS_CLEAN() WSACleanup(); 
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

	int inBatchNumber = 0; // to 250

	Utility::Chunk chunk	   = {};

	sockaddr_in m_receiverAddr = {};
	sockaddr_in m_clientAddr   = {};

	int m_clientAddrLen = sizeof(m_clientAddr);

	/// <summary>
	/// Initialize Winsock2
	/// </summary>
	void  Init();		  
	
	/// <summary>
	/// Create UDP Server socket
	/// </summary>
	void  CreateSocket(); 

	/// <summary>
	/// Bind UDP Server socket
	/// </summary>
	void  BindSocket();	 

public:
	/// buffer for the data of the electrodes 
	float* buffer; 

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
	void ReceiveFromSender();
};