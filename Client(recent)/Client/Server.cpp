#include "Server.h"

Server::Server()
{

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

	CsPacketLogin *login =
		reinterpret_cast<CsPacketLogin*>(sendBuf);
	login->packetSize = sizeof(CsPacketLogin);
	login->packetType = CS_LOGIN_REQUEST;

	ret = WSASend(sock, &wsaSendBuf, 1, &iobyte, 0, NULL, NULL);
	//cout << iobyte << endl;
	if (ret == SOCKET_ERROR)
		cout << "WSASend Error" << endl;
	cout << "로그인 요청" << endl;
	return 1;
}
void Server::keyDown(WPARAM wParam)
{
	int retval = 0;
	D3DXVECTOR3 playerDircetion;
	DWORD iobyte;
	DWORD ioflag = 0;

	if (wParam == VK_UP)
	{
		playerDircetion = D3DXVECTOR3(0, 0, 1);
	}
	if (wParam == VK_DOWN)
	{
		playerDircetion = D3DXVECTOR3(0, 0, -1);
	}
	if (wParam == VK_LEFT)
	{
		playerDircetion = D3DXVECTOR3(-1, 0, 0);
	}
	if (wParam == VK_RIGHT)
	{
		playerDircetion = D3DXVECTOR3(1, 0, 0);
	}

	CsPacketMove *myPacket = reinterpret_cast<CsPacketMove*>(sendBuf);
	myPacket->packetType = CS_MOVE;
	myPacket->packetSize = sizeof(myPacket);
	wsaSendBuf.buf = sendBuf;
	wsaSendBuf.len = sizeof(myPacket);
	myPacket->direction = playerDircetion;

	retval = WSASend(sock, &wsaSendBuf, 1, &iobyte, ioflag, NULL, NULL);
	//cout << iobyte << endl;
	if (retval == SOCKET_ERROR)
	{
		cout << "WSASend() x Error" << endl;
		cout << WSAGetLastError() << endl;
	}

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
	cout << "recv" << endl;
	int *ptr = reinterpret_cast<int*>(recvBuf);

	while (0 != iobyte)
	{
		if (inPacketSize == 0)
		{
			inPacketSize = ptr[0];
		}

		if (iobyte + savePacketSize >= inPacketSize)
		{
			memcpy(completeBuf + savePacketSize,
				ptr,
				inPacketSize - savePacketSize);

			processPacket(completeBuf);

			ptr += inPacketSize - savePacketSize;
			iobyte -= inPacketSize - savePacketSize;
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
		cout << "myId : " << Player[myId].getPlayerID() << endl;
		break;
	}
	case CS_MOVE:
	{
		cout << "pos" << endl;
		ScPacketMove *move =
			reinterpret_cast<ScPacketMove*>(ptr);
		//cout << p->id << "," << p->x << "," << p->y << endl;
		Player[move->id].setPlayerPosition(move->position);
		break;
	}
	case SC_MOVE_ERROR_CHECK:
	{
		cout << "이동 동기화 체크" << endl;
		ScPacketMove *check = reinterpret_cast<ScPacketMove*>(ptr);
		break;
	}

	}
}

void Server::sendPacket(SOCKET s, void* buf)
{
	SOCKET Send_socket = s;
	int packet_size = reinterpret_cast<char*>(buf)[0];
	memcpy(completeBuf, buf, packet_size);

	wsaCompleteBuf.buf = completeBuf;
	wsaCompleteBuf.len = packet_size;
	DWORD iobyte;
	WSASend(Send_socket, &wsaCompleteBuf, 1, &iobyte, 0, NULL, NULL);
}

int Server::getMyId()
{
	return myId;
}