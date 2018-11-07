#pragma once
#include "stdafx.h"



class Package {
public:
	Session * session;
	Packet*		packet;

public:
	Package(Session* session, Packet* packet) :session(session), packet(packet) {};
};

class ContentsProcess
{
	std::queue<Package*> Package_Queue;
	CRITICAL_SECTION lock;
	std::thread hThread[THREAD_COUNT];
protected:

public:
	typedef void PacketFunc(Session* session, Packet* packet);
	std::unordered_map<PacketType, PacketFunc*> PacketFuncTable;

	std::string		className;
public:
	ContentsProcess();
	~ContentsProcess();

	void Initialize();
	void Run();
	void AddPackage(Package* package);
	Package* GetPackage();


};

