#include "stdafx.h"
#include "Session.h"


#include <sqlext.h>




Session::Session(SOCKET socket) : socket(socket) {


	className = "Session";
	id = 0;
	memset(ip, NULL, 20);
	ioData = new IO_Data[IO_ACCEPT];
	ioData[IO_READ].session = this;
	ioData[IO_WRITE].session = this;
	Initialize();		
}


Session::~Session()
{
	Clear();
}


void Session::Initialize() {
	memset(mainBuffer, NULL, sizeof(char)* BUF_SIZE);
	totalBytes = 0;

}



void Session::SetType() {
	ioData[IO_READ].ioType = IO_READ;
	ioData[IO_WRITE].ioType = IO_WRITE;
}

void Session::SendPacket(Packet* packet) {
	
	packet->Encoding();
	int headerSize = sizeof(int);
	int packetLen = headerSize + packet->stream.offset;
	
	memcpy(&ioData[IO_WRITE].buffer, &packetLen, headerSize);
	memcpy(&ioData[IO_WRITE].buffer[headerSize], packet->stream.buffer, packet->stream.offset);

	WSABUF wsaBuf;
	wsaBuf.buf = ioData[IO_WRITE].buffer;
	wsaBuf.len = BUF_SIZE;

	DWORD sendBytes;
	DWORD flags = 0;
	int ret = WSASend(socket, &wsaBuf, 1, &sendBytes, flags, &ioData[IO_WRITE], NULL);
	if (ret == FALSE && WSAGetLastError() != WSA_IO_PENDING) {
		printf("WSASend : %d \n", WSAGetLastError());
	}

}

void Session::Recv(int recvBytes) {

	memcpy(&mainBuffer[totalBytes], ioData[IO_READ].buffer, recvBytes);
	
	//memset(ioData[IO_READ].buffer, NULL, recvBytes);
	printf("before totalBytes ===>>>> %d \n", totalBytes);
	totalBytes += recvBytes;
	printf("totalBytes %d , recvBytes : %d \n", totalBytes , recvBytes);
	bool result = PacketAnalyzer();
	if (result == false) {
		printf("need more Data...");
		//RecvStanby();
	}
}


int Session::getId() {
	return id;
}

void Session::setId(int id) {
	this->id = id;
}


void Session::RecvStanby() {
	DWORD flags = 0;
	DWORD recvBytes;
	WSABUF wsabuf;
	wsabuf.buf = ioData[IO_READ].buffer;
	wsabuf.len = BUF_SIZE - totalBytes;


	int ret = WSARecv(socket, &wsabuf, 1, &recvBytes, &flags, (LPOVERLAPPED)&ioData[IO_READ], NULL);
	if (ret == FALSE && WSAGetLastError() != WSA_IO_PENDING) {
		printf("WSARecv : %d \n", WSAGetLastError());
	}

	
}

bool Session::PacketAnalyzer() {


	do {
		int packetLen;
		int currentOffset = 0;

		memcpy(&packetLen, mainBuffer, sizeof(int));

		if (packetLen > totalBytes) {
			printf("data is not enough to Analyzer! \n");
			return false;
		}
		currentOffset += sizeof(int);

		PacketType packetType;

		memcpy(&packetType, &mainBuffer[currentOffset], sizeof(int));
		currentOffset += sizeof(int);

		Packet* packet = GetPacketClass(packetType);
		printf("PacketLen : %d \n", packetLen);
		memcpy(packet->stream.buffer, &mainBuffer[currentOffset], packetLen - currentOffset);

		Log("Before totalBytes : %d \n", totalBytes);
		totalBytes = totalBytes - packetLen;
		Log("after totalBytes : %d \n", totalBytes);
		
		if (totalBytes <= 0)
			memset(mainBuffer, NULL, BUF_SIZE);
		else if (totalBytes - packetLen < 0) {
			memcpy(mainBuffer, &mainBuffer[packetLen], totalBytes);
			memset(&mainBuffer[totalBytes], NULL, BUF_SIZE - totalBytes);
		}
		else
			memcpy(mainBuffer, &mainBuffer[packetLen], totalBytes);
	
		packet->Decoding();

		// Session 으로부터 0.001 초마다 데이터가 들어오게 설정해놓으면
		// 패킷들이 뭉쳐서 들어오게 되는데
		// totalBytes가 >= 0 큰 상황에 대해서 처리를 안해주고 있는 상태임 현재.
		// 이걸 session 마다 pakcet Queue를 가져가고
		// server에서 recv 한 후 PacketQueue를 확인해서
		// Queue 가없을떄 까지 ContentesProcess에 Push하는 로직으로 만들자.

		// 아무리커도 wsabbuf 58512 로 보임

		// 버티도록 만들어야 하나?
		packetQueue.push(packet);
	} while (totalBytes > 0);
	return true;

}

Packet* Session::GetPacket() {

	if (packetQueue.empty() == true) return nullptr;

	Packet* retPacket = packetQueue.front();
	packetQueue.pop();

	return retPacket;

}

Packet* Session::GetPacketClass(PacketType packetType) {
	switch (packetType) {
	case E_C_REQ_CHAT: return new PK_C_REQ_CHAT();
	case E_S_ANS_CHAT: return new PK_S_ANS_CHAT();
	}

	return nullptr;
}

void Session::ZeroByteReceive() {
	

	DWORD flags = 0;
	DWORD recvBytes;
	WSABUF wsabuf;
	wsabuf.buf = NULL;
	wsabuf.len = 0;
	int ret = WSARecv(socket, &wsabuf, 1, &recvBytes,&flags, &ioData[IO_READ], NULL);
	if (ret == FALSE && WSAGetLastError() != WSA_IO_PENDING) {
		printf("WSARecv : %d \n", WSAGetLastError());
	}
}

void Session::Close() {
	closesocket(socket);
}

void Session::Clear() {
	closesocket(socket);
	SAFE_DELETE(ioData);
}