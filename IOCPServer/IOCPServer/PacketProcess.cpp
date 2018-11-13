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

	Log("session id : %d, name : %s, chat : %s \n", session->getId(), packet->name, packet->chat);
//	printf("sessioname : %s , chat : %s \n", packet->name, packet->chat);

	tm struct_tm = clock.GetTime();
	int year = struct_tm.tm_year + 1900;
	int month = struct_tm.tm_mon;
	int day = struct_tm.tm_mday;
	int hour = struct_tm.tm_hour;
	int min = struct_tm.tm_min;
	int sec = struct_tm.tm_sec;

	PK_S_ANS_CHAT ansPacket;
	ansPacket.roomNumber = 1;
	ansPacket.userNumber = 1;
	memcpy(ansPacket.name, "kinam", 5);

	sprintf_s(ansPacket.chat, "%d년 %d월 %d일 %d시 %d분 %d초", year, month, day, hour, min, sec);
	
	session->SendPacket(&ansPacket);
	delete rowPacket;

	//return;

}