#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#pragma comment (lib, "ws2_32.lib")
#include "Server.h"

using namespace std;

Server *s = Server::getInstangce();


HINSTANCE ghInst;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	ghInst = hInstance;
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


	s->setSocketHWND(hWnd);
	s->socketInit();

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
		s->keyDown(wParam);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int p = 0; p < ROOM_MAX_PLAYER; ++p)
		{
			if (s->Player[p].getPlay() == true)
			{
				Rectangle(hdc,
					s->Player[p].getPlayerPosition().x,
					s->Player[p].getPlayerPosition().z,
					s->Player[p].getPlayerPosition().x + 20,
					s->Player[p].getPlayerPosition().z + 20);
				for (int i = 0; i < 100; ++i)
				{
					Ellipse(hdc, s->objectList[i].objectPosition.x - s->objectList[i].radius,
						s->objectList[i].objectPosition.z - s->objectList[i].radius,
						s->objectList[i].objectPosition.x + s->objectList[i].radius,
						s->objectList[i].objectPosition.z + s->objectList[i].radius);
				}
			}

		}

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
			s->readPacket();
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

