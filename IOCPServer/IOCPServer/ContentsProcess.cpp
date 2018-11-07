#include "stdafx.h"
#include "ContentsProcess.h"


ContentsProcess::ContentsProcess()
{
	className = "ContentsProcess";
	Initialize();
}


ContentsProcess::~ContentsProcess()
{
	for (int i = 0; i < THREAD_COUNT; i++)
		hThread[i].join();
	DeleteCriticalSection(&lock);
}


void ContentsProcess::Initialize() {
	InitializeCriticalSection(&lock);

	for (int i = 0; i < THREAD_COUNT; i++) {
		hThread[i] = std::thread{ &ContentsProcess::Run, this };
	}

}

void ContentsProcess::Run() {

	while (status != STOP) {
		if (Package_Queue.empty()) continue;

		Package* package = GetPackage();
		if (package == nullptr) {
			printf("package is null \n");
			continue;
		}
		//반환 값은 iterator
		std::unordered_map<PacketType, PacketFunc*>::iterator it;
		it = PacketFuncTable.find(package->packet->GetType());

		if (it == PacketFuncTable.end()) {
			printf(" Is not Regist PacketFunc in Table");
			continue;
		}

		PacketFunc* func = it->second;

		func(package->session, package->packet);

	}

}


void ContentsProcess::AddPackage(Package* package) {
	EnterCriticalSection(&lock);
	Package_Queue.push(package);
	LeaveCriticalSection(&lock);
}


Package* ContentsProcess::GetPackage() {
	EnterCriticalSection(&lock);
	Package* temp = Package_Queue.front();
	Package_Queue.pop();
	LeaveCriticalSection(&lock);
	return temp;
}

