#pragma once



enum PacketType {
	PACKET_TYPE_ERROR = 99,
	E_C_REQ_CHAT = 100,
	E_S_ANS_CHAT = 101,
};

class Stream {

public:
	int offset;
	BYTE buffer[BUF_SIZE];

	void operator<< (int Value) {
		memcpy(buffer + offset, &Value, sizeof(int));
		offset += sizeof(int);
	};


	void operator<< (short Value) {
		memcpy(buffer + offset, &Value, sizeof(short));
		offset += sizeof(short);
	};


	void operator<< (char* Value) {
		
		int stringSize = int(sizeof(char)*strlen(Value));
		*this << stringSize;

		memcpy(buffer + offset, Value ,stringSize);
		offset += stringSize;
	};


	void operator>> (int& Value) {
		memcpy(&Value, buffer + offset, sizeof(int));
		offset += sizeof(int);
	};


	void operator>> (short& Value) {
		memcpy(&Value, buffer + offset, sizeof(short));
		offset += sizeof(short);
	};


	void operator>> (char* Value) {
		int stringSize;
		*this >> stringSize;
		memcpy(Value, buffer + offset, stringSize);
		offset += sizeof(char) * stringSize;
	};

};
class Packet
{

public:
	Stream stream;

public:
	Packet() {
		memset(this, NULL, sizeof(*this));
	}
	~Packet() { };
	virtual PacketType GetType() { return PACKET_TYPE_ERROR; };
	virtual void Encoding() {};
	virtual void Decoding() {};
};


class PK_C_REQ_CHAT : public Packet {

public:
	char name[NAME_SIZE];
	char chat[CHAT_SIZE];

public:

	PK_C_REQ_CHAT() {
		memset(name, NULL, sizeof(char)*NAME_SIZE);
		memset(chat, NULL, sizeof(char)*CHAT_SIZE);
	}

	PacketType GetType() { return E_C_REQ_CHAT; }


	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << chat;
	}
	void Decoding() {
		stream >> name;
		stream >> chat;
	}




};

class PK_S_ANS_CHAT : public Packet{

};