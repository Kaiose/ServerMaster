#pragma once
#include "stdafx.h"



class Session
{
	
public:
	SOCKET socket;
	char ip[20];
	int id;

	char mainBuffer[BUF_SIZE];
	int totalBytes;

	IO_Data* ioData;
	
	std::queue<Packet*> packetQueue;


public:

	std::string		className;
	Session(SOCKET socket);
	~Session();

	void Initialize();
	void SetType();
	void SendPacket(Packet* packet);
	void Recv(int recvBytes);
	void Close();

	void Clear();

	void RecvStanby();
	void ZeroByteReceive();
	int getId();
	void setId(int id);

	Packet* GetPacketClass(PacketType packetType);
	Packet* GetPacket();
	bool PacketAnalyzer();
};

