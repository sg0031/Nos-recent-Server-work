#include "stdafx.h"
#include "LogicServer.h"


HANDLE LogicServer::io = NULL;	//빈 포트 생성
int LogicServer::id = 0;
PlayerInfo LogicServer::player[ROOM_MAX_PLAYER];
priority_queue<FIFO, vector<FIFO>, Standard> LogicServer::playerID;
int LogicServer::count = 0;
mutex LogicServer::myLock;
Sector LogicServer::sector[SECTOR_WIDETH][SECTOR_LENGTH];

LogicServer::LogicServer()
{

	FIFO init;
	//FIFO que
	for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
	{
		init.data = i;
		init.turn = i;
		playerID.push(init);
	}
	//sector init
	for (int i = 0; i < SECTOR_WIDETH;++i)
	{
		for (int j = 0; j < SECTOR_LENGTH; ++j)
		{
			sector[i][j].startSectorPosition.z = (j*80.0);
			sector[i][j].endSectorPosition.z = sector[i][j].startSectorPosition.z+80.0;
			sector[i][j].startSectorPosition.x = (i*60.0);
			sector[i][j].endSectorPosition.x = sector[i][j].endSectorPosition.x+60.0;
			sector[i][j].sectorNum.sectorNumX = i;
			sector[i][j].sectorNum.sectorNumY = j;
			for (int p = 0; p < MAX_OBJECT; ++p)
			{
				if (p % 2 == 0)
				{
					sector[i][j].arrayObject[p].radius = rand() % 15;
					sector[i][j].arrayObject[p].kind = 1;
					sector[i][j].arrayObject[p].objectPosition.x +=
						(sector[i][j].startSectorPosition.x + rand()%20);
					sector[i][j].arrayObject[p].objectPosition.z +=
						(sector[i][j].startSectorPosition.z + rand() % 20);
				}
			}
		}
	}
	//create thread
	srand((unsigned)time(NULL));
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "init error" << endl;

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
	cout << "ServerInit" << endl;

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
	retval = ::bind(listenSock, reinterpret_cast<SOCKADDR*>(&addr), sizeof(SOCKADDR));
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
		//	myLock.lock();
		int len = sizeof(clientAddr);
		clientSock = WSAAccept(listenSock, (SOCKADDR*)&clientAddr,
			&len, NULL, NULL);

		if (clientSock == INVALID_SOCKET)
			cout << "Client Socket Error" << endl;


		for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
		{
			if (player[i].acceptPlayer == false)
			{
				player[i].overEx->s = clientSock;
				player[i].acceptPlayer = true;
				count = i;
				break;
			}
		}
		//	player[count].overEx.s = clientSock;
		CreateIoCompletionPort((HANDLE)clientSock, io, count, 0);
		//	cout << id << "명 접속" << endl;

		unsigned long recvflag = 0;
		unsigned long ioByte = 0;
		int ret = 0;
		ret = WSARecv(clientSock, &player[count].overEx->buf,
			1, NULL, &recvflag,
			reinterpret_cast<LPOVERLAPPED>(&player[count].overEx->overLapped), NULL);
		if (ret == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
				cout << "error code : " << WSAGetLastError() << endl;
		}
		//count++;
		//cout << count << endl;
		//	myLock.unlock();
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
	unsigned long recvSize = 0;
	unsigned long objectId;
	unsigned long ioFlag = 0;
	OverEx *over = nullptr;
	double currentTime = 0.0;

	currentTime = clock();

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
					double newTime = clock();
					double frameTime = newTime - currentTime;
					if (frameTime > 0.25)
						frameTime = 0.25;
					currentTime = newTime;
					//accumulator += frameTime;
					//조립
					memcpy(over->packetBuf + over->prevSize, buf, needToBuild);
					//cout << static_cast<int>(Object_ID) << endl;
					processPacket(static_cast<int>(objectId), over->packetBuf, frameTime);
					//t += dt;
					//accumulator -= dt;
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
			retval = WSARecv(over->s, &over->buf, 1, &recvSize, &ioFlag, &over->overLapped, NULL);
		}

		else if (over->operationType == Sendtype)
		{
			delete over;
		}
	}
}
void LogicServer::processPacket(int id, char *ptr, double deltaTime)
{
	//cout << "processPacket 진입" << endl;
	//cout <<"id : "<< id << endl;
	BYTE *header = reinterpret_cast<BYTE*>(ptr + 4);
	FIFO idAllot;
	switch (*header)
	{
	case CS_LOGIN_REQUEST:
	{
		cout << "Login Accept" << endl;
		idAllot = playerID.top();
		playerID.pop();
		player[id].id = idAllot.data;
		player[id].play = true;
		cout << "id : " << player[id].id << endl;

		ScPacketMove login;
		login.packetSize = sizeof(ScPacketMove);
		login.packetType = SC_LOGIN_SUCCESS;
		login.id = player[id].id;
		login.position = player[id].playerPosition;
		sendPacket(id, &login);

		
		player[id].currentSector.sectorNumX = player[id].playerPosition.x/60.0;
		player[id].currentSector.sectorNumY = player[id].playerPosition.z /80.0;
		

		unsigned long objectCount = 0;	
		ScPacketObject sectorObjectPacket;
		ZeroMemory(&sectorObjectPacket.objects, sizeof(sectorObjectPacket.objects));
		myLock.lock();
		for (int i = player[id].currentSector.sectorNumX - 1; i < player[id].currentSector.sectorNumX + 2; ++i)
		{
			for (int j = player[id].currentSector.sectorNumY - 1; j < player[id].currentSector.sectorNumY + 2; ++j)
			{
				memcpy_s(sectorObjectPacket.objects + objectCount,
					sizeof(sectorObjectPacket.objects)-(sizeof(sector[i][j].arrayObject)*i),
					sector[i][j].arrayObject,
					sizeof(sector[i][j].arrayObject));
				objectCount += 10;
			}
		}
		sectorObjectPacket.position = player[id].currentSector;
		sectorObjectPacket.id = player[id].id;
		sectorObjectPacket.packetSize = sizeof(ScPacketObject);
		sectorObjectPacket.packetType = SC_SECTOR_UPDATE;
		myLock.unlock();
		sendPacket(id, &sectorObjectPacket);


		for (int p = 0; p < ROOM_MAX_PLAYER; ++p)
		{
			if (player[p].play == true)
			{
				for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
				{
					ScPacketAcceptPlayerList playerList;
					playerList.packetSize = sizeof(ScPacketAcceptPlayerList);
					playerList.packetType = SC_PLAYER_LIST;
					playerList.id = player[i].id;
					playerList.position = player[i].playerPosition;
					sendPacket(p, &playerList);
				}
			}
		}
		//cout << "로그인" << endl;
		break;
	}
	case CS_MOVE:
	{
		CsPacketMove *movePacket = reinterpret_cast<CsPacketMove*>(ptr);
		player[id].playerDirection = movePacket->direction;
		player[id].playerPosition = player[id].playerPosition +
			(player[id].playerVelocity * player[id].playerDirection*deltaTime);

		player[id].currentSector.sectorNumX = player[id].playerPosition.x / 60.0;
		player[id].currentSector.sectorNumY = player[id].playerPosition.z / 80.0;
		unsigned long objectCount = 0;
		ScPacketObject sectorObjectPacket;
		ZeroMemory(&sectorObjectPacket.objects, sizeof(sectorObjectPacket.objects));
		myLock.lock();
		for (int i = player[id].currentSector.sectorNumX - 1; i < player[id].currentSector.sectorNumX + 2; ++i)
		{
			for (int j = player[id].currentSector.sectorNumY - 1; j < player[id].currentSector.sectorNumY + 2; ++j)
			{
				memcpy_s(sectorObjectPacket.objects + objectCount,
					sizeof(sectorObjectPacket.objects) - (sizeof(sector[i][j].arrayObject)*i),
					sector[i][j].arrayObject,
					sizeof(sector[i][j].arrayObject));
				objectCount += 10;
			}
		}
		sectorObjectPacket.position = player[id].currentSector;
		sectorObjectPacket.id = player[id].id;
		sectorObjectPacket.packetSize = sizeof(ScPacketObject);
		sectorObjectPacket.packetType = SC_SECTOR_UPDATE;
		myLock.unlock();
		sendPacket(id, &sectorObjectPacket);

		for (int p = 0; p < ROOM_MAX_PLAYER; ++p)
		{
			if (player[p].play == true)
			{
				for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
				{
					ScPacketMove packet;
					packet.packetSize = sizeof(ScPacketMove);
					packet.id = player[i].id;
					packet.packetType = SC_MOVE_POSITION;
					packet.position = player[i].playerPosition;
					sendPacket(p, &packet);
				}
			}
		}

		break;
	}
	}

	//매번 플레이어들의 위치값 갱신

}
void LogicServer::sendPacket(int client, void* packet)
{
	//	char* a = reinterpret_cast<char*>(packet);
	int *packetSize = reinterpret_cast<int*>(packet);
	OverEx *Send_Operation = new OverEx;
	ZeroMemory(&Send_Operation->overLapped, sizeof(WSAOVERLAPPED));

	Send_Operation->operationType = Sendtype;

	Send_Operation->buf.buf = Send_Operation->iocpBuf;
	Send_Operation->buf.len = *packetSize;

	//	ScPacketMove *b = reinterpret_cast<ScPacketMove*>(packet);
	//	char *c = reinterpret_cast<char*>(packet);

	memcpy(Send_Operation->iocpBuf, reinterpret_cast<char*>(packet), *packetSize);

	//	ScPacketMove *p = reinterpret_cast<ScPacketMove*>(Send_Operation->Packetbuf);
	//	cout << "id:" << p->id<<"x :"<<p->x << "type:" << static_cast<char>(p->type) << endl;

	DWORD iobyte;
	DWORD sendFlag = 0;
	int retval;
	retval = WSASend(player[client].overEx->s, &Send_Operation->buf, 1,
		&iobyte, sendFlag, &Send_Operation->overLapped, NULL);
	if (retval != 0)
		cout << "error sendpacket" << endl;
//	cout << client << "data Send" << endl;

}