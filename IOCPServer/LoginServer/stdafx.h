// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
#pragma comment(lib,"ws2_32.LIB")

#pragma comment(lib,"ServerLibrary.lib")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string.h>

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

#include "../ServerLibrary/tinyXml/tinystr.h"
#include "../ServerLibrary/tinyXml/tinyxml.h"



#include "../ServerLibrary/Util/Util.h"
#include "../ServerLibrary/Util/Singleton.h"
#include "../ServerLibrary/Database/Database.h"
#include "../ServerLibrary/Util/Clock.h"
#include "../ServerLibrary/Util/Logger.h"
#include "../ServerLibrary/Packet/PacketClass.h"
#include "../ServerLibrary/Session/Session.h"
#include "../ServerLibrary/Session/SessionManager.h"
#include "../ServerLibrary/Contents/ContentsProcess.h"
#include "../ServerLibrary/Server/Server.h"
#include "../ServerLibrary/Packet/PacketProcess.h"



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
