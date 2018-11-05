// IOCPServer.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

int main()
{
	PacketProcess* packetProcess = new PacketProcess();

	Server* server = new Server(packetProcess);
	
	Log("Server Start");
	
	char command[10];
	while (true) {
		memset(command, NULL, sizeof(char) * 10);


		std::cin >> command;

		if (strcmp(command, "Exit") == 0) {
			status = STOP;
			break;
		}

		if (strcmp(command, "Show") == 0) {
			server->ShowPool();
		}

		if (strcmp(command, "Release") == 0) {
			server->Release_Resources();
		}

		if (strcmp(command, "Increase") == 0) {
			server->Create_Resources();
		}
	}
    return 0;
}
