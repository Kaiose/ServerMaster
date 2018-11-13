#pragma once
#include "stdafx.h"
class PacketProcess : public ContentsProcess
{
public:
	std::string		className;
	PacketProcess();
	~PacketProcess();

	void PacketParser();


	static void C_REQ_CHAT(Session* session, Packet* packet);

};

