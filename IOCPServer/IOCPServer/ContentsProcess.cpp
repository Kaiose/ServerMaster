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
	status = START;
	for (int i = 0; i < THREAD_COUNT-4; i++) {
		hThread[i] = std::thread( &ContentsProcess::Run, this );
	}

}

void ContentsProcess::Run() {
	
	while (status != STOP) {
		//Context switch  
		// is increase CPU Usage but need
		
		Package* package = GetPackage();
		if (package == nullptr) {
			std::this_thread::yield();
			//	printf("package is null \n");
			continue;
		}
		//반환 값은 iterator
		std::unordered_map<PacketType, PacketFunc*>::iterator it;
		it = PacketFuncTable.find(package->packet->GetType());
		//TODO : package 없애줘야함
		if (it == PacketFuncTable.end()) {
			printf(" Is not Regist PacketFunc in Table");
			SAFE_DELETE(package);
			continue;
		}

		PacketFunc* func = it->second;

		func(package->session, package->packet);
	
		SAFE_DELETE(package);

	}
	
}


void ContentsProcess::AddPackage(Package* package) {
	EnterCriticalSection(&lock);
	if (package == nullptr) {
		printf("package is null");
	}
	Package_Queue.push(package);
	LeaveCriticalSection(&lock);
}


inline Package* ContentsProcess::GetPackage() {
	Package* temp = nullptr;
	EnterCriticalSection(&lock);
	if (Package_Queue.empty() == true) {
		LeaveCriticalSection(&lock);
		return temp;
	}
	temp = Package_Queue.front();
	Package_Queue.pop();
	LeaveCriticalSection(&lock);
	return temp;
}
