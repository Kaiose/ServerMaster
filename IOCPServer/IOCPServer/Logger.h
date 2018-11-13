#pragma once
#include "stdafx.h"

#define Log(arg, ...) Logger::getInstance().PrintLog(arg,__VA_ARGS__)
#define PLog(arg, ...) Logger::getInstance().PacketLog(arg, __VA_ARGS__)
#define SLog(arg, ...) Logger::getInstance().SessionLog(arg,__VA_ARGS__)

class Logger : public Singleton<Logger>{

	FILE* packetLog;
	FILE* sessionLog;
	
	CRITICAL_SECTION packetlock;
	CRITICAL_SECTION sessionlock;

	friend Singleton;

	Logger() {
		InitializeCriticalSection(&packetlock);
		InitializeCriticalSection(&sessionlock);
		fopen_s(&packetLog,"packetLog.txt", "a+");
		fopen_s(&sessionLog,"sessionLog.txt", "a+");
	}

	~Logger() {
		LeaveCriticalSection(&packetlock);
		LeaveCriticalSection(&sessionlock);
		fclose(packetLog);
		fclose(sessionLog);
	}
	
public:

	std::queue<char*> LoggerQueue;
	
public:

	
	void PacketLog(const char* fmt, ...) {
		/*
		va_list args;
		va_start(args, fmt);
		std::thread([&]{
			

			tm struct_tm = clock.GetTime();
			int month = struct_tm.tm_mon;
			int day = struct_tm.tm_mday;
			int hour = struct_tm.tm_hour;
			int min = struct_tm.tm_min;

			char logStr[BUF_SIZE] = { 0, };
			sprintf_s(logStr, "%d 월 %d 일 %d 시 %d 분", month, day, hour, min);

			int len = strlen(logStr);
			vsprintf_s(&logStr[len], BUF_SIZE - len, fmt, args);
			len = strlen(logStr);
			logStr[len] = '\n';
			printf("%s", logStr);
			EnterCriticalSection(&packetlock);
			fprintf_s(packetLog, "%s", logStr);
			
			LeaveCriticalSection(&packetlock);

		});
		va_end(args, fmt);
		*/
	}

	void SessionLog(const char* fmt, ...) {
	/*	va_list args;


		va_start(args, fmt);

		std::thread([&]() {


			tm struct_tm = clock.GetTime();
			int month = struct_tm.tm_mon;
			int day = struct_tm.tm_mday;
			int hour = struct_tm.tm_hour;
			int min = struct_tm.tm_min;

			char logStr[BUF_SIZE] = { 0, };
			sprintf_s(logStr, "%d 월 %d 일 %d 시 %d 분", month, day, hour, min);

			int len = strlen(logStr);
			vsprintf_s(&logStr[len], BUF_SIZE - len, fmt, args);
			len = strlen(logStr);
			logStr[len] = '\n';
			printf("%s", logStr);

			EnterCriticalSection(&sessionlock);
			fprintf_s(sessionLog, "%s", logStr);
			LeaveCriticalSection(&sessionlock);

		});
		va_end(args, fmt);
		*/
	}

	void PrintLog(const char* fmt , ...) {

		va_list args;
		va_start(args, fmt);

		char logStr[BUF_SIZE] = { 0, };
		vsprintf_s(logStr, BUF_SIZE, fmt, args);
		std::string name;
		
		tm struct_tm = clock.GetTime();
		int month = struct_tm.tm_mon;
		int day = struct_tm.tm_mday; 
		int hour = struct_tm.tm_hour;
		int min = struct_tm.tm_min;
		
		printf("%d 월 %d 일 %d 시 %d 분 %s \n", month,day,hour,min,logStr);

		va_end(args);

	}


};