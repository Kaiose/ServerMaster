// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib,"ws2_32.LIB")

#include "targetver.h"
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
//#include <Windows.h>
//#include <mstcpip.h>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <time.h>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <MSWSock.h>
#include <thread>
#include <utility>
#include <set>
#include <string.h>


//using namespace std;




// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.


#include "Util.h"
#include "Singleton.h"

#include "Clock.h"
#include "Logger.h"
#include "PacketClass.h"
#include "Session.h"
#include "SessionManager.h"
#include "ContentsProcess.h"
#include "Server.h"

#include "PacketProcess.h"


