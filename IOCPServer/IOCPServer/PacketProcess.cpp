#include "stdafx.h"
#include "PacketProcess.h"


PacketProcess::PacketProcess()
{
#define INSERT_PACKET_PROCESS(type) PacketFuncTable.insert(std::make_pair(E_##type, &PacketProcess::##type))

	INSERT_PACKET_PROCESS(C_REQ_CHAT);

	className = "PacketProcess";
}


PacketProcess::~PacketProcess()
{

}

void PacketProcess::PacketParser() {

}


void PacketProcess::C_REQ_CHAT(Session* session, Packet* rowPacket) {

	PK_C_REQ_CHAT* packet = (PK_C_REQ_CHAT*)rowPacket;

	printf("name : %s , chat : %s \n", packet->name, packet->chat);

	return;

}