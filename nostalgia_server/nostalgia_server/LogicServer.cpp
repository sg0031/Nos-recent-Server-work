#include "LogicServer.h"


HANDLE LogicServer::io = NULL;	//빈 포트 생성
int LogicServer::id = 0;
PlayerInfo LogicServer::player[4];

LogicServer::LogicServer()
{

	srand((unsigned)time(NULL));
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "초기화 error" << endl;

	SYSTEM_INFO is;
	GetSystemInfo(&is);

	vector<thread*> worker;

	io = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	for (auto i = 0; i < (int)is.dwNumberOfProcessors; ++i)
	{
		worker.push_back(new thread{ workerThread });
	}

	auto Acceptex = thread{ acceptThread };
	auto Lobby = thread{ lobbyThread };

	while (1)
	{
		Sleep(1000);
	}

	Acceptex.join();
	Lobby.join();

	for (auto t : worker)
	{
		t->join();
	}
}


LogicServer::~LogicServer()
{
}

void LogicServer::acceptThread()
{
	cout << "시작" << endl;

	SOCKET listenSock;
	SOCKADDR_IN  addr;

	listenSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, 0, WSA_FLAG_OVERLAPPED);

	//주소 설정
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(9000);

	//bind 부분
	int retval = 0;
	retval = ::bind(listenSock, (SOCKADDR*)&addr, sizeof(addr));
	if (retval == SOCKET_ERROR)
		cout << "Bind Error" << endl;

	//리슨 소켓 설정
	retval = listen(listenSock, SOMAXCONN);
	if (retval == INVALID_SOCKET)
	{
		cout << "listen_sock error" << endl;
	}

	SOCKET clientSock;
	SOCKADDR_IN clientAddr;

	clientSock = NULL;

	while (1)
	{
		int len = sizeof(clientAddr);
		clientSock = WSAAccept(listenSock, (SOCKADDR*)&clientAddr,
			&len, NULL, NULL);

		if (clientSock == INVALID_SOCKET)
			cout << "클라이언트 소켓 에러" << endl;

		player[id].overEx.s = clientSock;
		//player[id].overEx.buf.buf = player[id].overEx.packetBuf;
		//player[id].overEx.buf.len = sizeof(player[id].overEx.packetBuf);

		CreateIoCompletionPort((HANDLE)clientSock, io, id, 0);
		cout << id << "접속" << endl;

		unsigned long recvflag = 0;
		WSARecv(clientSock, &player[id].overEx.buf,
			1, NULL, &recvflag,
			(LPOVERLAPPED)&player[id].overEx.overLapped, NULL);
		//클라이언트별 개별 아이디 부여
		id++;
	}
}
void LogicServer::lobbyThread()
{

}
void LogicServer::workerThread()
{
	//패킷 재조립이란?
	int retval;
	unsigned long ioSize;
	unsigned long objectId;
	unsigned long ioFlag = 0;
	OverEx *over = nullptr;
	while (1)
	{
		GetQueuedCompletionStatus(io, &ioSize, &objectId,
			reinterpret_cast<LPOVERLAPPED *>(&over), INFINITE);

		if (ioSize == 0)
		{
			//cout << iosize << endl;
			closesocket(over->s);
			//WSAGetOverlappedResult
			//게임종료 처리
		}

		if (over->operationType == Recvtype)
		{
			//cout << iosize << endl;
			//cout << "Recvtype" << endl;
			char *buf = over->iocpBuf;	//?
			unsigned long dataToProcess = ioSize;
			over->currentSize = dataToProcess;

			while (dataToProcess > 0)
			{
				if (over->currentSize == 0)
					over->currentSize = buf[0];

				unsigned int needToBuild =
					over->currentSize - over->prevSize;

				if (dataToProcess >= needToBuild)
				{
					//조립
					memcpy(over->packetBuf + over->prevSize, buf, needToBuild);
					//cout << static_cast<int>(Object_ID) << endl;
					processPacket(static_cast<int>(objectId), over->packetBuf);

					over->currentSize = 0;
					over->prevSize = 0;
					buf += needToBuild;
					dataToProcess -= needToBuild;
				}
				else
				{
					//훗날을 기약해
					memcpy(over->packetBuf + over->prevSize, buf, dataToProcess);
					over->prevSize += dataToProcess;
					dataToProcess = 0;
				}

			}
			retval = WSARecv(over->s, &over->buf, 1, NULL, &ioFlag, &over->overLapped, NULL);
		}

		else if (over->operationType == Sendtype)
		{
			delete over;
		}
	}
}
void LogicServer::processPacket(int id, char *ptr)
{
	//cout << "processPacket 진입" << endl;
	//cout <<"id : "<< id << endl;
	BYTE *header = reinterpret_cast<BYTE*>(ptr + 4);
	switch (*header)
	{
	case CS_LOGIN_REQUEST:
	{
		cout << "로그인 요청" << endl;
		cout << "id : " << id << endl;
		player[id].id = id;
		player[id].play = true;
		ScPacketMove login;
		login.packetSize = sizeof(ScPacketMove);
		login.packetType = SC_LOGIN_SUCCESS;
		login.position = player[id].playerPosition;
		sendPacket(id, &login);
		cout << "로그인" << endl;
		break;
	}
	case CS_MOVE:
	{
		player[id].playerPosition = player[id].playerPosition +
			(player[id].playerVelocity * player[id].playerDirection);
		//ScPacketMove packet;
		//packet.packetSize = sizeof(ScPacketMove);
		//packet.id = player[id].id;
		//packet.packetType = SC_MOVE_ERROR_CHECK;
		//packet.position = player[id].playerPosition;
		//sendPacket(id, &packet);
		break;
	}
	}

	//매번 플레이어들의 위치값 갱신
	for (int i = 0; i < 4; ++i)
	{
		if (player[i].play == true)
		{
			cout << "보냄" << endl;
			ScPacketMove packet;
			packet.packetSize = sizeof(ScPacketMove);
			packet.id = player[i].id;
			packet.packetType = SC_MOVE_POSITION;
			packet.position = player[i].playerPosition;
			sendPacket(id, &packet);
		}
	}
}
void LogicServer::sendPacket(int client, void* packet)
{
	//	char* a = reinterpret_cast<char*>(packet);
	int packetSize = reinterpret_cast<unsigned char*>(packet)[0];
	OverEx *Send_Operation = new OverEx;
	ZeroMemory(Send_Operation, sizeof(OverEx));

	Send_Operation->operationType = Sendtype;

	Send_Operation->buf.buf = Send_Operation->packetBuf;
	Send_Operation->buf.len = packetSize;

	//	ScPacketMove *b = reinterpret_cast<ScPacketMove*>(packet);
	//	char *c = reinterpret_cast<char*>(packet);

	memcpy(Send_Operation->packetBuf, reinterpret_cast<char*>(packet), packetSize);

	//	ScPacketMove *p = reinterpret_cast<ScPacketMove*>(Send_Operation->Packetbuf);
	//	cout << "id:" << p->id<<"x :"<<p->x << "type:" << static_cast<char>(p->type) << endl;

	DWORD iobyte;
	int retval;
	retval = WSASend(player[client].overEx.s, &Send_Operation->buf, 1,
		&iobyte, 0, &Send_Operation->overLapped, NULL);
	if (retval != 0)
		cout << "error sendpacket" << endl;
	cout << client << "정보 Send" << endl;


}