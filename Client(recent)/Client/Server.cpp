#include "stdafx.h"
#include "Server.h"

Server::Server()
{
	myId = 0;
	count = 0;
	for (int i = 0; i < SECTOR_WIDETH; ++i)
	{
		for (int j = 0; j < SECTOR_LENGTH; ++j)
		{
			sector[i][j].startSectorPosition.z = (j*80.0);
			sector[i][j].endSectorPosition.z = sector[i][j].startSectorPosition.z+80.0;
			sector[i][j].startSectorPosition.x = (i*60.0);
			sector[i][j].endSectorPosition.x = sector[i][j].startSectorPosition.x+60.0;
		}
	}
	ZeroMemory(&objectList, sizeof(objectList));
}
Server::~Server()
{

}
void Server::setSocketHWND(HWND s){
	socketHWND = s;
}
void Server::setHINSTANCE(HINSTANCE g)
{
	ghInst = g;
}
int Server::socketInit()
{
	WSADATA wsa;
	int ret = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		cout << "winsock init error" << endl;

	sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, 0);

	SOCKADDR_IN addr;

	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);

	ret = WSAConnect(sock, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL);

	WSAAsyncSelect(sock, socketHWND, WM_SOCKET, FD_READ | FD_CLOSE);

	wsaSendBuf.buf = sendBuf;
	wsaSendBuf.len = MAX_SIZE;
	wsaRecvBuf.buf = recvBuf;
	wsaRecvBuf.len = MAX_SIZE;

	DWORD iobyte;
	DWORD sendFlag=0;

	CsPacketLogin *login =
		reinterpret_cast<CsPacketLogin*>(sendBuf);
	login->packetSize = sizeof(CsPacketLogin);
	login->packetType = CS_LOGIN_REQUEST;

	ret = WSASend(sock, &wsaSendBuf, 1, &iobyte, sendFlag, NULL, NULL);
	cout << iobyte << endl;
	if (ret == SOCKET_ERROR)
		cout << "WSASend Error" << endl;
	cout << "Login Request" << endl;
	return 1;
}
void Server::keyDown(WPARAM wParam)
{
	D3DXVECTOR3 playerDircetion;

	if (wParam == VK_UP)
	{
		playerDircetion = D3DXVECTOR3(0, 0, -1);
	}
	if (wParam == VK_DOWN)
	{
		playerDircetion = D3DXVECTOR3(0, 0, 1);
	}
	if (wParam == VK_LEFT)
	{
		playerDircetion = D3DXVECTOR3(-1, 0, 0);
	}
	if (wParam == VK_RIGHT)
	{
		playerDircetion = D3DXVECTOR3(1, 0, 0);
	}

	CsPacketMove myPacket;
	myPacket.packetSize = sizeof(CsPacketMove);
	myPacket.packetType = CS_MOVE;
	myPacket.direction = playerDircetion;
	sendPacket(sock, &myPacket);

}
void Server::readPacket()
{
	DWORD iobyte, ioflag = 0;

	int ret = WSARecv(sock, &wsaRecvBuf, 1, &iobyte, &ioflag, NULL, NULL);
	if (ret != 0)
	{
		int err_code = WSAGetLastError();
		cout << "Recv Error : " << err_code << endl;
	}
	//cout << "recv" << endl;
	char *ptr = reinterpret_cast<char*>(recvBuf);

	while (0 != iobyte)
	{
		if (inPacketSize == 0)
		{
			inPacketSize = reinterpret_cast<int*>(ptr);
		}

		if (iobyte + savePacketSize >= *inPacketSize)
		{
			memcpy(completeBuf + savePacketSize,
				ptr,
				*inPacketSize - savePacketSize);

			processPacket(completeBuf);

			ptr += *inPacketSize - savePacketSize;
			iobyte -= *inPacketSize - savePacketSize;
			inPacketSize = 0;
			savePacketSize = 0;
		}
		else
		{
			memcpy(completeBuf + savePacketSize, ptr, iobyte);
			savePacketSize += iobyte;
			iobyte = 0;
		}
	}
}

void Server::processPacket(char* ptr)
{
	BYTE *header = reinterpret_cast<BYTE*>(ptr + 4);
	//cout << "process" << endl;
	switch (*header)
	{
	case SC_LOGIN_SUCCESS:
	{
		ScPacketMove *login =
			reinterpret_cast<ScPacketMove*>(ptr);
		myId = login->id;
		Player[myId].setPlayerID(myId);
		Player[myId].setPlay(true);
		cout << "myId : " << Player[myId].getPlayerID() << endl;
		break;
	}
	case SC_PLAYER_LIST:
	{
		ScPacketAcceptPlayerList *list =
			reinterpret_cast<ScPacketAcceptPlayerList*>(ptr);
		for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
		{
			if (i==list->id)
			{
				Player[i].setPlayerID(list->id);
				Player[i].setPlay(true);
				Player[i].setPlayerPosition(list->position);
			}
		}
		break;
	}
	case SC_MOVE_POSITION:
	{
//		cout << "movePacket" << endl;
		ScPacketMove *move =
			reinterpret_cast<ScPacketMove*>(ptr);
		//cout << p->id << "," << p->x << "," << p->y << endl;
		for (int i = 0; i < ROOM_MAX_PLAYER; ++i)
		{
			if (Player[i].getPlayerID() == move->id)
			{
				Player[i].setPlayerPosition(move->position);
			}
		}
		//Player[move->id].setPlayerPosition(move->position);
		break;
	}

	case SC_MOVE_ERROR_CHECK:
	{
		cout << "이동 동기화 체크" << endl;
		ScPacketMove *check = reinterpret_cast<ScPacketMove*>(ptr);
		break;
	}
	case SC_SECTOR_UPDATE:
	{
		ScPacketObject *object = reinterpret_cast<ScPacketObject*>(ptr);
		ZeroMemory(&objectList, sizeof(objectList));
		memcpy_s(&objectList, sizeof(objectList), &object->objects, sizeof(object->objects));
		break;
	}
	}
}

void Server::sendPacket(SOCKET s, void* buf)
{
	DWORD iobyte;
	DWORD ioflag = 0;
	SOCKET Send_socket = s;
	int *packet_size = reinterpret_cast<int*>(buf);
	OverEx *Send_Operation = new OverEx;
	ZeroMemory(Send_Operation, sizeof(OverEx));
	
	Send_Operation->buf.buf = Send_Operation->packetBuf;
	Send_Operation->buf.len = *packet_size;

	//wsaCompleteBuf.buf = completeBuf;
	//wsaCompleteBuf.len = packet_size;

	memcpy(Send_Operation->packetBuf, reinterpret_cast<char*>(buf), *packet_size);

	int retval = WSASend(Send_socket, &Send_Operation->buf, 1, &iobyte, ioflag, NULL, NULL);
	//cout << iobyte << endl;
	if (retval == SOCKET_ERROR)
	{
		cout << "WSASend() x Error" << endl;
		cout << WSAGetLastError() << endl;
	}
	//cout << "client data send" << endl;
}

int Server::getMyId()
{
	return myId;
}