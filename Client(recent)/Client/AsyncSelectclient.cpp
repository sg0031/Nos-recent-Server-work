#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment (lib, "ws2_32.lib")

#include "Server.h"

using namespace std;

Server *s = Server::getInstangce();


HINSTANCE g_hInst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	s->setHINSTANCE(hInstance);

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = s->IpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(s->IpszClass, s->IpszClass, WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_HSCROLL | WS_VSCROLL, 100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	s->setSocket_HWND(hWnd);
	s->socketinit();

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;


	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		break;
	case WM_KEYDOWN:
		s->KeyDown(wParam);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		for (int p = 0; p < 8; ++p)
		{
			Rectangle(hdc,
				s->Player[p].getPlayer_Position().x,
				s->Player[p].getPlayer_Position().y,
				s->Player[p].getPlayer_Position().x + 20,
				s->Player[p].getPlayer_Position().y + 20);
		}

		//for (int i = 0; i < 8; ++i)
		//{
		//	Rectangle(hdc, 
		//		s->Player[i].P_x, 
		//		s->Player[i].P_y,
		//		s->Player[i].P_x + 20, 
		//		s->Player[i].P_y + 20);
		//}
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_SOCKET:
	{
		if (WSAGETSELECTERROR(IParam)) {
			closesocket((SOCKET)wParam);
			break;
		}
		switch (WSAGETSELECTEVENT(IParam)) {
		case FD_READ:
			s->ReadPacket();
		//	InvalidateRect(hWnd, NULL, TRUE);
			break;
		case FD_CLOSE:
			closesocket((SOCKET)wParam);
			break;
		}
	}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

