#pragma once
#include "stdafx.h"


#define THREAD_COUNT	8
#define RESOURCE_COUNT	1000
#define BUF_SIZE		1024 * 10
#define CHAT_SIZE		512
#define NAME_SIZE		16
#define MIN				10


#define SAFE_DELETE(obj)		\
{	if(obj != NULL) delete obj;	\
	obj = NULL;					\
}								\




enum STATUS {
	START,
	STOP,
};


//static HANDLE	hIOCP;
static STATUS	status;

enum IO_Type {
	IO_READ,
	IO_WRITE,
	IO_ACCEPT,
};
static int sessionCount;

class Session;

#define session_it std::unordered_set<Session*>::iterator
//#define session_it std::set<Session*>::iterator
#define session_map_it std::unordered_map<int, Session*>::iterator

struct IO_Data : public OVERLAPPED {
public:
	Session * session;
	IO_Type ioType;
	//WSABUF wsaBuf;
	char buffer[BUF_SIZE];
	
	IO_Data() {
		memset(this, NULL, sizeof(*this));
		ioType = IO_ACCEPT;
	}

	void Initialize() {
		memset(this, NULL, sizeof(OVERLAPPED));
		Fill_Zero();
		ioType = IO_ACCEPT;
	}

	void Fill_Zero() {
		memset(buffer, NULL, BUF_SIZE);
	}

};