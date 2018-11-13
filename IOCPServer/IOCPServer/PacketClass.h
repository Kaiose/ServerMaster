#pragma once



enum PacketType {
	E_C_REQ_EXIT = 90,
	PACKET_TYPE_ERROR = 99,
	E_C_REQ_SIGNUP = 100,
	E_S_ANS_SIGNUP = 101,
	E_C_REQ_SIGNIN = 102,
	E_S_ANS_SIGNIN = 103,
	E_S_NOTIFY_SERVER = 104,
	E_C_REQ_CONNECT = 105,
	E_S_ANS_CONNECT = 106,
	E_C_REQ_CONNECT_ROOM = 107,
	E_S_ANS_CONNECT_ROOM = 108,
	E_S_NOTIFY_OTHER_CLIENT = 109,
	E_C_REQ_CHAT = 110,
	E_S_ANS_CHAT = 111,
	E_C_REQ_MOVE = 112,
	E_S_ANS_MOVE = 113,

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


	void operator<< (bool Value) {
		memcpy(buffer + offset, &Value, sizeof(bool));
		offset += sizeof(bool);
	}

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


	void operator>> (bool& Value) {
		memcpy(&Value, buffer + offset, sizeof(bool));
		offset += sizeof(bool);
	}

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

	char name[NAME_SIZE];

public:
	Packet() {
		memset(this, NULL, sizeof(*this));
	}
	~Packet() { };
	virtual PacketType GetType() { return PACKET_TYPE_ERROR; };
	virtual void Encoding() {};
	virtual void Decoding() {};
};

//
//E_C_REQ_EXIT = 90,

class PK_C_REQ_EXIT : public Packet {
public:

public:
	PacketType GetType() { return E_C_REQ_EXIT; }

	void Encoding() {

		stream << (int)GetType();
		stream << name;
	}

	void Decoding() {
		stream >> name;
	}

};

class PK_C_REQ_CHAT : public Packet {

public:
	//char name[NAME_SIZE];
	int roomNumber;
	int userNumber;
	char chat[CHAT_SIZE];
	
public:

	PK_C_REQ_CHAT() {
	//	memset(name, NULL, sizeof(char)*NAME_SIZE);
		memset(chat, NULL, sizeof(char)*CHAT_SIZE);
	}

	PacketType GetType() { return E_C_REQ_CHAT; }


	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << userNumber;
		stream << chat;
	}
	void Decoding() {
		stream >> name;
		stream << roomNumber;
		stream << userNumber;
		stream >> chat;
	}


};

class PK_S_ANS_CHAT : public Packet {
public:
	int roomNumber;
	int userNumber;
	char chat[CHAT_SIZE];
public:
	PK_S_ANS_CHAT() {
		//	memset(name, NULL, sizeof(char)*NAME_SIZE);
		memset(chat, NULL, sizeof(char)*CHAT_SIZE);
	}
	PacketType GetType() { return E_S_ANS_CHAT; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << userNumber;
		stream << chat;
	}

	void Decoding() {
		stream >> name;
		stream >> roomNumber;
		stream >> userNumber;
		stream >> chat;
	}
};


class PK_C_REQ_SIGNUP : public Packet {
public:
	char password[NAME_SIZE];
public:

	PK_C_REQ_SIGNUP() {
		memset(password, NULL, sizeof(char)*NAME_SIZE);
	}
	PacketType GetType() { return E_C_REQ_SIGNUP; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << password;
	}

	void Decoding() {
		stream >> name;
		stream >> password;
	}
};

class PK_S_ANS_SIGNUP : public Packet {
public:

	char password[NAME_SIZE];
	bool result;
public:
	PK_S_ANS_SIGNUP() {
		memset(password, NULL, sizeof(char)*NAME_SIZE);
	}
	PacketType GetType() { return E_S_ANS_SIGNUP; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << password;
		stream << result;
	}

	void Decoding() {
		stream >> name;
		stream >> password;
		stream >> result;
	}
};


class PK_C_REQ_SIGNIN : public Packet {
public:
	char password[NAME_SIZE];
public:
	PK_C_REQ_SIGNIN() {
		memset(password, NULL, sizeof(char)*NAME_SIZE);
	}
	PacketType GetType() { return E_C_REQ_SIGNIN; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << password;
	}

	void Decoding() {
		stream >> name;
		stream >> password;
	}
};

class PK_S_ANS_SIGNIN : public Packet {
public:
	char password[NAME_SIZE];
	bool result;
public:
	PK_S_ANS_SIGNIN() {
		memset(password, NULL, sizeof(char)*NAME_SIZE);
	}
	PacketType GetType() { return E_S_ANS_SIGNIN; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << password;
		stream << result;
	}

	void Decoding() {
		stream >> name;
		stream >> password;
		stream >> result;
	}
};
//E_S_NOTIFY_SERVER = 104,
class PK_S_NOTIFY_SERVER : public Packet {
public:
	char	ip[NAME_SIZE];
	int		port;
public:
	PK_S_NOTIFY_SERVER() {
		memset(ip, NULL, sizeof(char)*NAME_SIZE);
	}
	PacketType GetType() { return E_S_NOTIFY_SERVER; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << ip;
		stream << port;
	}

	void Decoding() {
		stream >> name;
		stream >> ip;
		stream >> port;
	}
};


//E_C_REQ_CONNECT = 105,

class PK_C_REQ_CONNECT : public Packet {
public:

public:
	PacketType GetType() { return E_C_REQ_CONNECT; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
	}

	void Decoding() {
		stream >> name;
	}
};


//E_S_ANS_CONNECT = 106,
class PK_S_ANS_CONNECT : public Packet {
public:

public:
	PacketType GetType() { return E_S_ANS_CONNECT; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
	}

	void Decoding() {
		stream >> name;
	}
};
//E_C_REQ_CONNECT_ROOM = 107,
class PK_C_REQ_CONNECT_ROOM : public Packet {
public:
	int roomNumber;
	int userNumber;
public:
	PacketType GetType() { return E_C_REQ_CONNECT_ROOM; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << userNumber;
	}

	void Decoding() {
		stream >> name;
		stream >> roomNumber;
		stream >> userNumber;
	}
};

//E_S_ANS_CONNECT_ROOM = 108,

class PK_S_ANS_CONNECT_ROOM : public Packet {
public:
	int roomNumber;
	int UserNumber;
public:
	PacketType GetType() { return E_S_ANS_CONNECT_ROOM; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << UserNumber;
	}

	void Decoding() {
		stream >> name;
		stream >> roomNumber;
		stream >> UserNumber;
	}
};

//E_S_NOTIFY_OTHER_CLIENT = 109,

class PK_S_NOTIFY_OTHER_CLIENT : public Packet {
public:
	int userNumber;
public:
	PK_S_NOTIFY_OTHER_CLIENT() {
	
	}
	PacketType GetType() { return E_S_NOTIFY_OTHER_CLIENT; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << userNumber;
	}

	void Decoding() {
		stream >> name;
		stream >> userNumber;
	}
};
//E_C_REQ_MOVE = 112,

class PK_C_REQ_MOVE : public Packet {
public:
	int roomNumber;
	int userNumber;
public:
	PacketType GetType() { return E_C_REQ_MOVE; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << userNumber;
	}

	void Decoding() {
		stream >> name;
		stream >> roomNumber;
		stream >> userNumber;
	}
};
//E_S_ANS_MOVE = 113,


class PK_S_ANS_MOVE : public Packet {
public:
	int roomNumber;
	int userNumber;
public:
	PacketType GetType() { return E_S_ANS_MOVE; }

	void Encoding() {
		stream << (int)GetType();
		stream << name;
		stream << roomNumber;
		stream << userNumber;
	}

	void Decoding() {
		stream >> name;
		stream >> roomNumber;
		stream >> userNumber;
	}
};