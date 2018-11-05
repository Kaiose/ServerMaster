#pragma once

#include "stdafx.h"

#define Log(arg, ...) Logger::getInstance().PrintLog(arg,__VA_ARGS__)

class Logger : public Singleton<Logger>{

	Logger() {}

	friend Singleton;
public:

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