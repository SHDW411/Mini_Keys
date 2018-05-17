#include <Windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "soundclass.h"
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

SoundClass m_Sound;
HBITMAP hBitmap = NULL;

MSG info;

//identyfikatory przycisków
#define ID_PRZYCISK1 101
#define ID_PRZYCISK2 102

//funkcja obs³uguj¹ca wszystko, co siê dzieje w okienku
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadImage(NULL, "resources\\nuta3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc, hdcNowy;
		HBITMAP hbmObraz;
		HGDIOBJ oldBitmap;
		hdc = BeginPaint(hwnd, &ps);
		hdcNowy = CreateCompatibleDC(hdc);
		oldBitmap = CreateCompatibleBitmap(hdcNowy, 28, 7);
		oldBitmap = SelectObject(hdcNowy, hBitmap);
		BitBlt(hdc, 200, 200, 28, 7, hdcNowy, 0, 0, SRCCOPY);
		SelectObject(hdcNowy, oldBitmap);
		DeleteDC(hdcNowy);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
			//przycisk odtwarzaj¹cy utworzon¹ melodiê
		case ID_PRZYCISK1:
		{
			m_Sound.Initialize(hwnd);
			m_Sound.playback();
			break;
		}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);

	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCSTR NazwaKlasy = "Window Class";

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = NazwaKlasy;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Failed to create window class", "Error", MB_ICONEXCLAMATION | MB_OK);
		return TRUE;
	}

	HWND hwnd, hPrzycisk1, hPrzycisk2;

	//wyczyszczenie warstw, ¿eby by³y puste przy rozpoczêciu programu
	for (int i = 0; i < 1000; i++)
	{
		m_Sound.layer1[i].note_id = 0;
		m_Sound.layer1[i].note_length = 0;
		m_Sound.layer2[i].note_id = 0;
		m_Sound.layer2[i].note_length = 0;
		m_Sound.layer3[i].note_id = 0;
		m_Sound.layer3[i].note_length = 0;
		m_Sound.layer4[i].note_id = 0;
		m_Sound.layer4[i].note_length = 0;
		m_Sound.layer5[i].note_id = 0;
		m_Sound.layer5[i].note_length = 0;
	}

	//test
	m_Sound.layer1[0].note_id = 0;
	m_Sound.layer1[0].note_length = 2;
	m_Sound.layer1[0].note_volume = 0;
	m_Sound.layer1[2].note_id = 1;
	m_Sound.layer1[2].note_length = 2;
	m_Sound.layer1[2].note_volume = 0;
	m_Sound.layer1[4].note_id = 2;
	m_Sound.layer1[4].note_length = 2;
	m_Sound.layer1[4].note_volume = 0;
	m_Sound.layer1[6].note_id = 0;
	m_Sound.layer1[6].note_length = 2;
	m_Sound.layer1[6].note_volume = 0;
	m_Sound.layer1[8].note_id = 3;
	m_Sound.layer1[8].note_length = 2;
	m_Sound.layer1[8].note_volume = 0;
	m_Sound.layer1[10].note_id = 4;
	m_Sound.layer1[10].note_length = 4;
	m_Sound.layer1[10].note_volume = 0;
	m_Sound.layer1[14].note_id = 5;
	m_Sound.layer1[14].note_length = 2;
	m_Sound.layer1[14].note_volume = 0;
	m_Sound.layer1[16].note_id = 0;
	m_Sound.layer1[16].note_length = 2;
	m_Sound.layer1[16].note_volume = 0;
	m_Sound.layer1[18].note_id = 5;
	m_Sound.layer1[18].note_length = 2;
	m_Sound.layer1[18].note_volume = 0;
	m_Sound.layer1[20].note_id = 6;
	m_Sound.layer1[20].note_length = 2;
	m_Sound.layer1[20].note_volume = 0;
	m_Sound.layer1[22].note_id = 0;
	m_Sound.layer1[22].note_length = 2;
	m_Sound.layer1[22].note_volume = 0;
	m_Sound.layer1[24].note_id = 3;
	m_Sound.layer1[24].note_length = 2;
	m_Sound.layer1[24].note_volume = 0;
	m_Sound.layer1[26].note_id = 7;
	m_Sound.layer1[26].note_length = 4;
	m_Sound.layer1[26].note_volume = 0;

	m_Sound.layer2[0].note_id = 8;
	m_Sound.layer2[0].note_length = 8;
	m_Sound.layer2[0].note_volume = -300;
	m_Sound.layer2[8].note_id = 9;
	m_Sound.layer2[8].note_length = 8;
	m_Sound.layer2[8].note_volume = -300;
	m_Sound.layer2[16].note_id = 10;
	m_Sound.layer2[16].note_length = 8;
	m_Sound.layer2[16].note_volume = -300;
	m_Sound.layer2[24].note_id = 8;
	m_Sound.layer2[24].note_length = 8;
	m_Sound.layer2[24].note_volume = -300;

	m_Sound.layer3[0].note_id = 11;
	m_Sound.layer3[0].note_length = 2;
	m_Sound.layer3[0].note_volume = -500;
	m_Sound.layer3[2].note_id = 12;
	m_Sound.layer3[2].note_length = 2;
	m_Sound.layer3[2].note_volume = -500;
	m_Sound.layer3[4].note_id = 13;
	m_Sound.layer3[4].note_length = 2;
	m_Sound.layer3[4].note_volume = -500;
	m_Sound.layer3[6].note_id = 14;
	m_Sound.layer3[6].note_length = 2;
	m_Sound.layer3[6].note_volume = -500;
	m_Sound.layer3[8].note_id = 15;
	m_Sound.layer3[8].note_length = 2;
	m_Sound.layer3[8].note_volume = -500;
	m_Sound.layer3[10].note_id = 16;
	m_Sound.layer3[10].note_length = 2;
	m_Sound.layer3[10].note_volume = -500;
	m_Sound.layer3[12].note_id = 17;
	m_Sound.layer3[12].note_length = 2;
	m_Sound.layer3[12].note_volume = -500;
	m_Sound.layer3[14].note_id = 13;
	m_Sound.layer3[14].note_length = 2;
	m_Sound.layer3[14].note_volume = -500;
	m_Sound.layer3[16].note_id = 18;
	m_Sound.layer3[16].note_length = 2;
	m_Sound.layer3[16].note_volume = -500;
	m_Sound.layer3[18].note_id = 19;
	m_Sound.layer3[18].note_length = 2;
	m_Sound.layer3[18].note_volume = -500;
	m_Sound.layer3[20].note_id = 20;
	m_Sound.layer3[20].note_length = 2;
	m_Sound.layer3[20].note_volume = -500;
	m_Sound.layer3[22].note_id = 21;
	m_Sound.layer3[22].note_length = 2;
	m_Sound.layer3[22].note_volume = -500;
	m_Sound.layer3[24].note_id = 11;
	m_Sound.layer3[24].note_length = 2;
	m_Sound.layer3[24].note_volume = -500;
	m_Sound.layer3[26].note_id = 12;
	m_Sound.layer3[26].note_length = 2;
	m_Sound.layer3[26].note_volume = -500;
	m_Sound.layer3[28].note_id = 13;
	m_Sound.layer3[28].note_length = 2;
	m_Sound.layer3[28].note_volume = -500;
	m_Sound.layer3[30].note_id = 14;
	m_Sound.layer3[30].note_length = 2;
	m_Sound.layer3[30].note_volume = -500;


	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, NazwaKlasy, "Mini keys", WS_OVERLAPPEDWINDOW + WS_HSCROLL + WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 720, NULL, NULL, hInstance, NULL);
	
	hPrzycisk2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Open", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 0, 200, 40, hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);
	hPrzycisk2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Save", WS_CHILD | WS_VISIBLE | WS_BORDER, 205, 0, 200, 40, hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);

//	HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 0, 330, 15, 320, hwnd, NULL, hInstance, NULL);
//	SetWindowText(hStatic, "1 /n 2");


//	HWND hStatic2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 650, 960, 15, hwnd, NULL, hInstance, NULL);
//	SetWindowText(hStatic, "1");

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 55, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 95, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 15, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&info, NULL, 0, 0))
	{
		TranslateMessage(&info);
		DispatchMessage(&info);
	}
	return info.wParam;

	return 0;
}
