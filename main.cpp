#include <Windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "soundclass.h"
#include "define.h"
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;

string nid, nleng, nvol;
fstream file;


SoundClass m_Sound;
HBITMAP hBitmap = NULL;
HBITMAP hBitmap2 = NULL;

MSG info;

//funkcja obs³uguj¹ca wszystko, co siê dzieje w okienku
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadImage(NULL, "resources\\nuta3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitmap2 = (HBITMAP)LoadImage(NULL, "resources\\nuta2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc, hdcNowy, hdcNowy2;
		HGDIOBJ oldBitmap, oldBitmap2;
		hdc = BeginPaint(hwnd, &ps);
		hdcNowy = CreateCompatibleDC(hdc);
		hdcNowy2 = CreateCompatibleDC(hdc);
		oldBitmap = CreateCompatibleBitmap(hdcNowy, 28, 7);
		oldBitmap2 = CreateCompatibleBitmap(hdcNowy2, 28, 7);
		oldBitmap = SelectObject(hdcNowy, hBitmap);
		oldBitmap2 = SelectObject(hdcNowy2, hBitmap2);
		m_Sound.wyswietl(m_Sound.current_layer, m_Sound.octaves, m_Sound.time, &hdc, &hdcNowy, &hdcNowy2);
		SelectObject(hdcNowy, oldBitmap);
		SelectObject(hdcNowy2, oldBitmap2);
		DeleteDC(hdcNowy);
		DeleteDC(hdcNowy2);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case octave3:
				m_Sound.octave=1;
				break;
		case octave5:
				m_Sound.octave=2;
				break;
		case octave7:
				m_Sound.octave=3;
				break;
		case play:
			m_Sound.Initialize(hwnd);
			m_Sound.playback();
			file.open("save.txt", ios::out | ios::app);
			break;

			//przycisk odtwarzaj¹cy utworzon¹ melodiê
		case ID_PRZYCISK1:
			if(m_Sound.octave==1){
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 576, 16, m_Sound.volume);
				break;
			} else if (m_Sound.octave==2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 384, 16, m_Sound.volume);
				break;
			} else if (m_Sound.octave==3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 192, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK2:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 575, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 383, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 191, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK3:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 574, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 382, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 190, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK4:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 573, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 381, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 189, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK5:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 572, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 380, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 188, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK6:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 571, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 379, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 187, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK7:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 570, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 378, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 186, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK8:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 569, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 377, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 185, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK9:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 575, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 383, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 191, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK10:
			m_Sound.Initialize(hwnd);
			m_Sound.playback();
			m_Sound.layer1[0].note_id = 2;
			m_Sound.layer1[0].note_length = 1;
			m_Sound.layer1[0].note_volume = 0;
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		}
		break;
	case WM_CLOSE:
		file.close();
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

	HWND hwnd, hPrzycisk1, hPrzycisk2, hPrzycisk3, hPrzycisk4, hPrzycisk5, hPrzycisk6, hPrzycisk7, hPrzycisk8, hPrzycisk9, hPrzycisk10, hPrzycisk11, hPrzycisk12, hPrzycisk13, hPrzycisk14, hPrzycisk15, hPrzycisk16, hPrzycisk17, hPrzycisk18, hPrzycisk19, hPrzycisk20, hPrzycisk21, hPrzycisk22, hPrzycisk23, hPrzycisk24, hPrzycisk25, hPrzycisk26, hPrzycisk27, hPrzycisk28, hPrzycisk29, hPrzycisk30, hPrzycisk31, hPrzycisk32, hPrzycisk33, hPrzycisk34, hPrzycisk35, hPrzycisk36, hPrzycisk37, hPrzycisk38, hPrzycisk39, hPrzycisk40, hPrzycisk41, hPrzycisk42, hPrzycisk43, hPrzycisk44, hPrzycisk45, hPrzycisk46, hPrzycisk47, hPrzycisk48, hPrzycisk49, hPrzycisk50, hPrzycisk51, hPrzycisk52, hPrzycisk53, hPrzycisk54, hPrzycisk55, hPrzycisk56, hPrzycisk57, hPrzycisk58, hPrzycisk59, hPrzycisk60, hPrzycisk61, hPrzycisk62, hPrzycisk63, hPrzycisk64, hPrzycisk65, hPrzycisk66, hPrzycisk67, hPrzycisk68, hPrzycisk69, hPrzycisk70, hPrzycisk71, hPrzycisk72, hPrzycisk73, hPrzycisk74, hPrzycisk75, hPrzycisk76, hPrzycisk77, hPrzycisk78, hPrzycisk79, hPrzycisk80, hPrzycisk81, hPrzycisk82, hPrzycisk83, hPrzycisk84, hPrzycisk85, hPrzycisk86, hPrzycisk87, hPrzycisk88, hPrzycisk89, hPrzycisk90, hPrzycisk91, hPrzycisk92, hPrzycisk93, hPrzycisk94, hPrzycisk95, hPrzycisk96, hPrzycisk97, hPrzycisk98, hPrzycisk99, hPrzycisk100, hPrzycisk101, hPrzycisk102, hPrzycisk103, hPrzycisk104, hPrzycisk105, hPrzycisk106, hPrzycisk107, hPrzycisk108, hPrzycisk109, hPrzycisk110, hPrzycisk111, hPrzycisk112, hPrzycisk113, hPrzycisk114, hPrzycisk115, hPrzycisk116, hPrzycisk117, hPrzycisk118, hPrzycisk119, hPrzycisk120, hPrzycisk121, hPrzycisk122, hPrzycisk123, hPrzycisk124, hPrzycisk125, hPrzycisk126, hPrzycisk127, hPrzycisk128, hPrzycisk129, hPrzycisk130, hPrzycisk131, hPrzycisk132, hPrzycisk133, hPrzycisk134, hPrzycisk135, hPrzycisk136, hPrzycisk137, hPrzycisk138, hPrzycisk139, hPrzycisk140, hPrzycisk141, hPrzycisk142, hPrzycisk143, hPrzycisk144, hPrzycisk145, hPrzycisk146, hPrzycisk147, hPrzycisk148, hPrzycisk149, hPrzycisk150, hPrzycisk151, hPrzycisk152, hPrzycisk153, hPrzycisk154, hPrzycisk155, hPrzycisk156, hPrzycisk157, hPrzycisk158, hPrzycisk159, hPrzycisk160, hPrzycisk161, hPrzycisk162, hPrzycisk163, hPrzycisk164, hPrzycisk165, hPrzycisk166, hPrzycisk167, hPrzycisk168, hPrzycisk169, hPrzycisk170, hPrzycisk171, hPrzycisk172, hPrzycisk173, hPrzycisk174, hPrzycisk175, hPrzycisk176, hPrzycisk177, hPrzycisk178, hPrzycisk179, hPrzycisk180, hPrzycisk181, hPrzycisk182, hPrzycisk183, hPrzycisk184, hPrzycisk185, hPrzycisk186, hPrzycisk187, hPrzycisk188, hPrzycisk189, hPrzycisk190, hPrzycisk191, hPrzycisk192, hPrzycisk193, hPrzycisk194, hPrzycisk195, hPrzycisk196, hPrzycisk197, hPrzycisk198, hPrzycisk199, hPrzycisk200;
	HWND open, octave23, octave45, octave67, vol1, vol2, vol3, vol4, vol5;

	//wyczyszczenie warstw, ¿eby by³y puste przy rozpoczêciu programu
	for (int i = 0; i < 1000; i++)
	{
		m_Sound.layer1[i].note_id = 0;
		m_Sound.layer1[i].note_length = 0;
		m_Sound.layer1[i].note_volume = 0;
		m_Sound.layer2[i].note_id = 0;
		m_Sound.layer2[i].note_length = 0;
		m_Sound.layer2[i].note_volume = 0;
		m_Sound.layer3[i].note_id = 0;
		m_Sound.layer3[i].note_length = 0;
		m_Sound.layer3[i].note_volume = 0;
		m_Sound.layer4[i].note_id = 0;
		m_Sound.layer4[i].note_length = 0;
		m_Sound.layer4[i].note_volume = 0;
		m_Sound.layer5[i].note_id = 0;
		m_Sound.layer5[i].note_length = 0;
		m_Sound.layer5[i].note_volume = 0;
	}

	if(file.good()==false){}
	string line;
	while (getline(file, line))
	{

	}

	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, NazwaKlasy, "Mini keys", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 720, NULL, NULL, hInstance, NULL);
	
	open = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Play", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 0, 200, 40, hwnd, (HMENU)play, hInstance, NULL);
	octave23 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 2,3", WS_CHILD | WS_VISIBLE | WS_BORDER, 205, 0, 200, 40, hwnd, (HMENU)octave3, hInstance, NULL);
	octave45 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 4,5", WS_CHILD | WS_VISIBLE | WS_BORDER, 405, 0, 200, 40, hwnd, (HMENU)octave5, hInstance, NULL);
	octave67 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 6,7", WS_CHILD | WS_VISIBLE | WS_BORDER, 605, 0, 200, 40, hwnd, (HMENU)octave7, hInstance, NULL);

	HWND hStatic1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |SS_LEFT, 0, 340, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic1, " 1");
	HWND hStatic12 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 380, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic12, "3/4");
	HWND hStatic13 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 420, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic13, "1/2");
	HWND hStatic14 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 460, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic14, "3/8");
	HWND hStatic16 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 500, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic16, "1/4");
	HWND hStatic18 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 540, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic18, "3/16");
	HWND hStatic112 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 580, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic112, "1/8");
	HWND hStatic116 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 620, 30, 40, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic116, "1/16");




	HWND hStaticC = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 45, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticC, "C");
	HWND hStaticC2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 85, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticC2, "C#");
	HWND hStaticD = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 125, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticD, "D");
	HWND hStaticD2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 165, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticD2, "D#");
	HWND hStaticE = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 205, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticE, "E");
	HWND hStaticF = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 245, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticF, "F");
	HWND hStaticF2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 285, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticF2, "F#");
	HWND hStaticG = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 325, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticG, "G");
	HWND hStaticG2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 365, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticG2, "G#");
	HWND hStaticA = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 405, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticA, "A");
	HWND hStaticA2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 445, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticA2, "A#");
	HWND hStaticH = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 485, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticH, "H");
	HWND hStaticc = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 525, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticc, "c");
	HWND hStaticc2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 565, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticc2, "c#");
	HWND hStaticd = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 605, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticd, "d");
	HWND hStaticd2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 645, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticd2, "d#");
	HWND hStatice = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 685, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatice, "e");
	HWND hStaticf = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 725, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticf, "f");
	HWND hStaticf2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 765, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticf2, "f#");
	HWND hStaticg = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 805, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticg, "g");
	HWND hStaticg2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 845, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStaticg2, "g#");
	HWND hStatica = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 885, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatica, "a");
	HWND hStatica2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 925, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatica2, "a#");
	HWND hStatich = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 965, 650, 960, 15, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatich, "h");



	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);
	hPrzycisk3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK3, hInstance, NULL);
	hPrzycisk4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK4, hInstance, NULL);
	hPrzycisk5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK5, hInstance, NULL);
	hPrzycisk6 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK6, hInstance, NULL);
	hPrzycisk7 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK7, hInstance, NULL);
	hPrzycisk8 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK8, hInstance, NULL);
	
	hPrzycisk9 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK9, hInstance, NULL);
	hPrzycisk10 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK10, hInstance, NULL);
	hPrzycisk11 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK11, hInstance, NULL);
	hPrzycisk12 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK12, hInstance, NULL);
	hPrzycisk13 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK13, hInstance, NULL);
	hPrzycisk14 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK14, hInstance, NULL);
	hPrzycisk15 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK15, hInstance, NULL);
	hPrzycisk16 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK16, hInstance, NULL);

	hPrzycisk17 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK17, hInstance, NULL);
	hPrzycisk18 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK18, hInstance, NULL);
	hPrzycisk19 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK19, hInstance, NULL);
	hPrzycisk20 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK20, hInstance, NULL);
	hPrzycisk21 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK21, hInstance, NULL);
	hPrzycisk22 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK22, hInstance, NULL);
	hPrzycisk23 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK23, hInstance, NULL);
	hPrzycisk24 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 110, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK24, hInstance, NULL);

	hPrzycisk25 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK25, hInstance, NULL);
	hPrzycisk26 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK26, hInstance, NULL);
	hPrzycisk27 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK27, hInstance, NULL);
	hPrzycisk28 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK28, hInstance, NULL);
	hPrzycisk29 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK29, hInstance, NULL);
	hPrzycisk30 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK30, hInstance, NULL);
	hPrzycisk31 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK31, hInstance, NULL);
	hPrzycisk32 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK32, hInstance, NULL);

	hPrzycisk33 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK33, hInstance, NULL);
	hPrzycisk34 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK34, hInstance, NULL);
	hPrzycisk35 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK35, hInstance, NULL);
	hPrzycisk36 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK36, hInstance, NULL);
	hPrzycisk37 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK37, hInstance, NULL);
	hPrzycisk38 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK38, hInstance, NULL);
	hPrzycisk39 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK39, hInstance, NULL);
	hPrzycisk40 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK40, hInstance, NULL);

	hPrzycisk41 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk42 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk43 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk44 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk45 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk46 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk47 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk48 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk49 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk50 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk51 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk52 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk53 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk54 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk55 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk56 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk57 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk58 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk59 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk60 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk61 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk62 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk63 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk64 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk65 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk66 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk67 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk68 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk69 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk70 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk71 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk72 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk73 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk74 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk75 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk76 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk77 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk78 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk79 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk80 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk81 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk82 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk83 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk84 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk85 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk86 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk87 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk88 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk89 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk90 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk91 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk92 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk93 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk94 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk95 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk96 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk97 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk98 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk99 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk100 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk101 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk102 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk103 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk104 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk105 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk106 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk107 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk108 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk109 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk110 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk111 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk112 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk113 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk114 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk115 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk116 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk117 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk118 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk119 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk120 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk121 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk122 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk123 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk124 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk125 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk126 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk127 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk128 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk129 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk130 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk131 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk132 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk133 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk134 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk135 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk136 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk137 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk138 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk139 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk140 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk141 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk142 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk143 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk144 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk145 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk146 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk147 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk148 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk149 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk150 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk151 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk152 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk153 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk154 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk155 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk156 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk157 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk158 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk159 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk160 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk161 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk162 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk163 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk164 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk165 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk166 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk167 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk168 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk169 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk170 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk171 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk172 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk173 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk174 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk175 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk176 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk177 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk178 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk179 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/3", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk180 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk181 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/6", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk182 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk183 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/12", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk184 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

	hPrzycisk185 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK41, hInstance, NULL);
	hPrzycisk186 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK42, hInstance, NULL);
	hPrzycisk187 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK43, hInstance, NULL);
	hPrzycisk188 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK44, hInstance, NULL);
	hPrzycisk189 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK45, hInstance, NULL);
	hPrzycisk190 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK46, hInstance, NULL);
	hPrzycisk191 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK47, hInstance, NULL);
	hPrzycisk192 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK48, hInstance, NULL);

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
