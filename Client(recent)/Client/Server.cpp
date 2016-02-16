#include "Server.h"

Server::Server()
{

}
Server::~Server()
{

}
void Server::setSocket_HWND(HWND s){
	Socket_HWND = s;
}
void Server::setHINSTANCE(HINSTANCE g)
{
	g_hInst = g;
}
int Server::socketinit()
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

	WSAAsyncSelect(sock, Socket_HWND, WM_SOCKET, FD_READ | FD_CLOSE);

	WSA_send_buf.buf = Send_buf;
	WSA_send_buf.len = MAX_SIZE;
	WSA_recv_buf.buf = Recv_buf;
	WSA_recv_buf.len = MAX_SIZE;

	DWORD iobyte;

	cs_packet_accept *login =
		reinterpret_cast<cs_packet_accept*>(Send_buf);
	login->size = sizeof(cs_packet_accept);
	login->type = CS_LOGIN;

	ret = WSASend(sock, &WSA_send_buf, 1, &iobyte, 0, NULL, NULL);
	//cout << iobyte << endl;
	if (ret == SOCKET_ERROR)
		cout << "WSASend Error" << endl;

	return 1;
}
void Server::KeyDown(WPARAM wParam)
{
	int retval = 0;
	D3DXVECTOR3 player_dircetion;
	DWORD iobyte;
	DWORD ioflag = 0;

	if (wParam == VK_UP)
	{
		player_dircetion = D3DXVECTOR3(0, 0, 1);
	}
	if (wParam == VK_DOWN)
	{
		player_dircetion = D3DXVECTOR3(0, 0, -1);
	}
	if (wParam == VK_LEFT)
	{
		player_dircetion = D3DXVECTOR3(-1, 0, 0);
	}
	if (wParam == VK_RIGHT)
	{
		player_dircetion = D3DXVECTOR3(1, 0, 0);
	}

	cs_packet_move *my_packet = reinterpret_cast<cs_packet_move*>(Send_buf);
	my_packet->packet_size = sizeof(my_packet);
	WSA_send_buf.len = sizeof(my_packet);
	my_packet->direction = player_dircetion;

	retval = WSASend(sock, &WSA_send_buf, 1, &iobyte, ioflag, NULL, NULL);
	//cout << iobyte << endl;
	if (retval == SOCKET_ERROR)
	{
		cout << "WSASend() x Error" << endl;
		cout << WSAGetLastError() << endl;
	}

}
void Server::ReadPacket()
{
	DWORD iobyte, ioflag = 0;

	int ret = WSARecv(sock, &WSA_recv_buf, 1, &iobyte, &ioflag, NULL, NULL);
	if (ret != 0)
	{
		int err_code = WSAGetLastError();
		cout << "Recv Error : " << err_code << endl;
	}
	cout << "recv" << endl;
	BYTE *ptr = reinterpret_cast<BYTE*>(Recv_buf);

	while (0 != iobyte)
	{
		if (in_packet_size == 0)
		{
			in_packet_size = ptr[0];
		}

		if (iobyte + save_packet_size >= in_packet_size)
		{
			memcpy(Complete_buf + save_packet_size,
				ptr,
				in_packet_size - save_packet_size);

			ProcessPacket(Complete_buf);

			ptr += in_packet_size - save_packet_size;
			iobyte -= in_packet_size - save_packet_size;
			in_packet_size = 0;
			save_packet_size = 0;
		}
		else
		{
			memcpy(Complete_buf + save_packet_size, ptr, iobyte);
			save_packet_size += iobyte;
			iobyte = 0;
		}

	}
}


void Server::ProcessPacket(char* ptr)
{
	//cout << "process" << endl;
	switch (ptr[1])
	{

	case SC_LOGIN_SUCCESS:
	{
		sc_packet_login *p =
			reinterpret_cast<sc_packet_login*>(ptr);
		my_id = p->id;
		//Player[my_id].P_id = my_id;
		cout << "my_id : "<< my_id << endl;
		break;
	}

	case CS_MOVE:
	{
		cout << "pos" << endl;
		sc_packet_move *p =
			reinterpret_cast<sc_packet_move*>(ptr);
		//cout << p->id << "," << p->x << "," << p->y << endl;
		Player[p->id].setPlayer_Position(p->position);
		break;
	}
	case SC_MOVE_ERROR_CHECK:
	{
		cout << "이동 동기화 체크" << endl;
		sc_packet_move *p = reinterpret_cast<sc_packet_move*>(ptr);
		
		break;
	}
	}
}

void Server::SendPacket(SOCKET s, void* buf)
{
	SOCKET Send_socket = s;
	int packet_size = reinterpret_cast<char*>(buf)[0];
	memcpy(Complete_buf, buf, packet_size);

	WSA_Complete_buf.buf = Complete_buf;
	WSA_Complete_buf.len = packet_size;
	DWORD iobyte;
	WSASend(Send_socket, &WSA_Complete_buf, 1, &iobyte, 0, NULL, NULL);
}

int Server::GetMy_id()
{
	return my_id;
}