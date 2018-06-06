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
#include <time.h>
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

using namespace std;

int nline = 1, nid, nleng;
fstream file;
string line;

SoundClass m_Sound;
HBITMAP hBitmap = NULL;
HBITMAP hBitmap2 = NULL;
HBITMAP hBitmap3 = NULL;
HWND hStatic_layer_value, hStatic_octaves_value, hStatic_display_value, hStatic_volume_value;

MSG info;

//funkcja obs³uguj¹ca wszystko, co siê dzieje w okienku
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		hBitmap = (HBITMAP)LoadImage(NULL, "resources\\nuta3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitmap2 = (HBITMAP)LoadImage(NULL, "resources\\nuta2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitmap3 = (HBITMAP)LoadImage(NULL, "resources\\bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc, hdcNowy, hdcNowy2, hdcNowy3;
		HGDIOBJ oldBitmap, oldBitmap2, oldBitmap3;
		hdc = BeginPaint(hwnd, &ps);
		hdcNowy = CreateCompatibleDC(hdc);
		hdcNowy2 = CreateCompatibleDC(hdc);
		hdcNowy3 = CreateCompatibleDC(hdc);
		oldBitmap = CreateCompatibleBitmap(hdcNowy, 28, 7);
		oldBitmap2 = CreateCompatibleBitmap(hdcNowy2, 28, 7);
		oldBitmap3 = CreateCompatibleBitmap(hdcNowy3, 956, 287);
		oldBitmap = SelectObject(hdcNowy, hBitmap);
		oldBitmap2 = SelectObject(hdcNowy2, hBitmap2);
		oldBitmap3 = SelectObject(hdcNowy3, hBitmap3);
		m_Sound.wyswietl(m_Sound.current_layer, m_Sound.octaves, m_Sound.time, &hdc, &hdcNowy, &hdcNowy2, &hdcNowy3);
		SelectObject(hdcNowy, oldBitmap);
		SelectObject(hdcNowy2, oldBitmap2);
		SelectObject(hdcNowy3, oldBitmap3);
		DeleteDC(hdcNowy);
		DeleteDC(hdcNowy2);
		DeleteDC(hdcNowy3);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case octave24:
				m_Sound.octaves = 0;
				SetWindowText(hStatic_display_value, "2-4");
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
				break;
		case octave57:
				m_Sound.octaves = 1;
				SetWindowText(hStatic_display_value, "5-7");
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
				break;
		case octave3:
				m_Sound.octave=1;
				SetWindowText(hStatic_octaves_value, "2-3");
				break;
		case octave5:
				m_Sound.octave=2;
				SetWindowText(hStatic_octaves_value, "4-5");
				break;
		case octave7:
				m_Sound.octave=3;
				SetWindowText(hStatic_octaves_value, "6-7");
				break;
		case current_layer1:
			m_Sound.current_layer = 1;
			SetWindowText(hStatic_layer_value, "1");
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case current_layer2:
			m_Sound.current_layer = 2;
			SetWindowText(hStatic_layer_value, "2");
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case current_layer3:
			m_Sound.current_layer = 3;
			SetWindowText(hStatic_layer_value, "3");
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case current_layer4:
			m_Sound.current_layer = 4;
			SetWindowText(hStatic_layer_value, "4");
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case current_layer5:
			m_Sound.current_layer = 5;
			SetWindowText(hStatic_layer_value, "5");
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case previous_display:
			if (m_Sound.time > 0)
			{
				m_Sound.time -= 32;
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			}
			break;
		case next_display:
			m_Sound.time += 32;
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case last_delete:
			if (m_Sound.current_layer == 1)
			{
				while (m_Sound.layer1[m_Sound.layer1_counter].note_length == 0)
				{
					m_Sound.layer1_counter--;
				}
				m_Sound.layer1[m_Sound.layer1_counter].note_id = 0;
				m_Sound.layer1[m_Sound.layer1_counter].note_length = 0;
				m_Sound.layer1[m_Sound.layer1_counter].note_volume = 0;
			}
			else if (m_Sound.current_layer == 2)
			{
				while (m_Sound.layer2[m_Sound.layer2_counter].note_length == 0)
				{
					m_Sound.layer2_counter--;
				}
				m_Sound.layer2[m_Sound.layer2_counter].note_id = 0;
				m_Sound.layer2[m_Sound.layer2_counter].note_length = 0;
				m_Sound.layer2[m_Sound.layer2_counter].note_volume = 0;
			}
			else if (m_Sound.current_layer == 3)
			{
				while (m_Sound.layer3[m_Sound.layer3_counter].note_length == 0)
				{
					m_Sound.layer3_counter--;
				}
				m_Sound.layer3[m_Sound.layer3_counter].note_id = 0;
				m_Sound.layer3[m_Sound.layer3_counter].note_length = 0;
				m_Sound.layer3[m_Sound.layer3_counter].note_volume = 0;
			}
			else if (m_Sound.current_layer == 4)
			{
				while (m_Sound.layer4[m_Sound.layer4_counter].note_length == 0)
				{
					m_Sound.layer4_counter--;
				}
				m_Sound.layer4[m_Sound.layer4_counter].note_id = 0;
				m_Sound.layer4[m_Sound.layer4_counter].note_length = 0;
				m_Sound.layer4[m_Sound.layer4_counter].note_volume = 0;
			}
			else
			{
				while (m_Sound.layer5[m_Sound.layer5_counter].note_length == 0)
				{
					m_Sound.layer5_counter--;
				}
				m_Sound.layer5[m_Sound.layer5_counter].note_id = 0;
				m_Sound.layer5[m_Sound.layer5_counter].note_length = 0;
				m_Sound.layer5[m_Sound.layer5_counter].note_volume = 0;
			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
			break;
		case addpause:
			m_Sound.AddNote(hwnd, m_Sound.current_layer, 0, 1, 0);
			break;
		case play:
			m_Sound.Initialize(hwnd);
			m_Sound.playback();
			break;
			//przycisk odtwarzaj¹cy utworzon¹ melodiê
		case vol0:
			m_Sound.volume = -1500;
			SetWindowText(hStatic_volume_value, "-15 dB");
			break;
		case vol1:
			m_Sound.volume = -1000;
			SetWindowText(hStatic_volume_value, "-10 dB");
			break;
		case vol2:
			m_Sound.volume = -750;
			SetWindowText(hStatic_volume_value, "-7,5 dB");
			break;
		case vol3:
			m_Sound.volume = -500;
			SetWindowText(hStatic_volume_value, "-5 dB");
			break;
		case vol4:
			m_Sound.volume = -250;
			SetWindowText(hStatic_volume_value, "-2,5 dB");
			break;
		case vol5:
			m_Sound.volume = 0;
			SetWindowText(hStatic_volume_value, "0 dB");
			break;
		case saver:
			m_Sound.save_to_file();
			break;
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 575, 12, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 574, 8, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 573, 6, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 572, 4, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 571, 3, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 570, 2, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 569, 1, m_Sound.volume);
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
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 568, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 376, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 184, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK10:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 567, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 375, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 183, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK11:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 566, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 375, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 182, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK12:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 565, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 374, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 181, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK13:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 564, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 373, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 180, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK14:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 563, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 372, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 179, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK15:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 562, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 371, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 178, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK16:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 561, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 370, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 177, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK17:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 560, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 369, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 176, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK18:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 559, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 368, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 175, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK19:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 558, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 367, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 174, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK20:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 557, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 366, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 173, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK21:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 556, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 372, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 188, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK22:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 555, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 364, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 171, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK23:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 554, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 363, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 170, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK24:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 553, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 362, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 169, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK25:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 552, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 361, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 168, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK26:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 551, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 360, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 167, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK27:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 550, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 359, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 166, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK28:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 549, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 358, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 165, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK29:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 548, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 357, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 164, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK30:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 547, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 356, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 163, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK31:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 546, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 355, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 162, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK32:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 545, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 354, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 161, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK33:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 544, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 353, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 160, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK34:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 5435, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 352, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 159, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK35:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 542, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 351, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 158, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK36:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 541, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 350, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 157, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK37:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 540, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 349, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 156, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK38:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 539, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 348, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 155, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK39:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 538, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 347, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 154, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK40:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 537, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 346, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 153, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK41:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 536, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 345, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 152, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK42:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 535, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 344, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 151, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK43:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 534, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 343, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 150, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK44:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 533, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 342, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 149, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK45:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 532, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 341, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 148, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK46:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 531, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 340, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 147, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK47:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 530, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 339, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 146, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK48:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 529, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 338, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 145, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK49:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 528, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 337, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 144, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK50:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 527, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 336, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 143, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK51:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 526, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 335, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 142, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK52:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 525, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 334, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 141, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK53:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 524, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 333, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 140, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK54:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 523, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 332, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 139, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK55:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 522, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 331, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 138, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK56:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 521, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 330, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 137, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK57:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 520, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 329, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 136, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK58:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 519, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 328, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 135, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK59:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 518, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 327, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 134, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK60:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 517, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 326, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 133, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK61:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 516, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 325, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 132, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK62:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 515, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 324, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 131, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK63:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 514, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 323, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 130, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK64:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 513, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 322, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 129, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK65:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 512, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 321, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 128, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK66:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 511, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 320, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 127, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK67:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 510, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 319, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 126, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK68:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 509, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 318, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 125, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK69:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 508, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 317, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 124, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK70:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 507, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 316, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 123, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK71:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 508, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 315, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 122, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK72:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 507, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 314, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 121, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK73:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 506, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 313, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 120, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK74:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 505, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 312, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 119, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK75:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 504, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 311, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 118, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK76:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 503, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 310, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 117, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK77:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 502, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 309, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 116, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK78:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 501, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 308, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 115, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK79:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 500, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 307, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 114, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK80:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 499, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 306, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 113, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK81:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 498, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 305, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 112, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK82:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 497, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 304, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 111, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK83:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 496, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 303, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 110, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK84:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 495, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 302, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 109, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK85:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 494, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 301, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 108, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK86:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 493, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 300, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 107, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK87:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 492, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 299, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 106, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK88:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 491, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 298, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 105, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK89:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 490, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 297, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 104, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK90:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 489, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 296, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 103, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK91:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 488, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 295, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 102, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK92:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 487, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 294, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 101, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK93:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 486, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 293, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 100, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK94:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 485, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 292, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 99, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK95:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 484, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 291, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 98, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK96:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 483, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 290, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 97, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK97:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 482, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 289, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 96, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK98:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 481, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 288, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 95, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK99:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 480, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 287, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 94, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK100:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 479, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 286, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 93, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK101:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 478, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 285, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 92, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK102:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 477, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 284, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 91, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK103:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 476, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 283, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 90, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK104:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 475, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 282, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 89, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK105:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 474, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 281, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 88, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK106:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 473, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 280, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 87, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK107:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 472, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 279, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 86, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK108:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 471, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 278, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 85, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK109:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 470, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 277, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 84, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK110:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 469, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 276, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 83, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK111:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 468, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 275, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 82, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK112:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 467, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 274, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 81, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK113:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 466, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 273, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 80, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK114:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 465, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 272, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 79, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK115:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 464, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 271, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 78, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK116:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 463, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 270, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 77, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK117:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 462, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 269, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 76, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK118:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 461, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 268, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 75, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK119:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 460, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 267, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 74, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK120:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 459, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 266, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 73, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK121:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 458, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 265, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 72, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK122:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 457, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 264, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 71, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK123:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 456, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 263, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 70, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK124:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 455, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 262, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 69, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK125:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 454, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 261, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 68, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK126:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 453, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 260, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 67, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK127:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 452, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 259, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 66, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK128:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 451, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 258, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 65, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK129:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 450, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 257, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 64, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK130:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 449, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 256, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 63, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK131:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 448, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 255, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 62, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK132:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 447, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 254, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 61, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK133:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 446, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 253, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 60, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK134:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 445, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 252, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 59, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK135:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 444, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 251, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 58, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK136:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 443, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 250, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 57, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK137:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 442, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 249, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 56, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK138:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 441, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 248, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 55, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK139:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 440, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 247, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 54, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK140:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 439, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 246, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 53, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK141:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 438, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 245, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 52, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK142:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 437, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 244, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 51, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK143:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 436, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 243, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 50, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK144:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 435, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 242, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 49, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK145:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 434, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 241, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 48, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK146:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 433, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 240, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 47, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK147:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 432, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 239, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 46, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK148:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 431, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 238, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 45, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK149:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 430, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 237, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 44, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK150:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 429, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 236, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 43, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK151:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 428, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 235, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 42, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK152:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 427, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 234, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 41, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK153:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 426, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 233, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 40, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK154:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 425, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 232, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 39, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK155:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 424, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 231, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 38, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK156:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 423, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 230, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 37, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK157:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 422, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 229, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 36, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK158:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 421, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 228, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 35, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK159:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 420, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 227, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 34, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK160:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 419, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 226, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 33, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK161:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 418, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 225, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 32, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK162:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 417, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 224, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 31, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK163:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 416, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 223, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 30, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK164:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 415, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 222, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 29, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK165:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 414, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 221, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 28, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK166:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 413, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 220, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 27, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK167:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 412, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 219, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 26, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK168:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 411, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 218, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 25, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK169:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 410, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 217, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 24, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK170:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 409, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 216, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 23, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK171:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 408, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 215, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 22, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK172:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 407, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 214, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 21, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK173:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 406, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 213, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 20, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK174:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 405, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 212, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 19, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK175:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 404, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 211, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 18, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK176:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 403, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 210, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 17, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK177:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 402, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 209, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 16, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK178:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 401, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 208, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 15, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK179:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 400, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 207, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 14, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK180:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 399, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 206, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 13, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK181:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 398, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 205, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 12, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK182:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 397, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 204, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 11, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK183:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 396, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 203, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 10, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK184:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 395, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 202, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 9, 1, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK185:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 394, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 201, 16, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 8, 16, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK186:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 393, 12, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 200, 12, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 7, 12, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK187:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 392, 8, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 199, 8, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 6, 8, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK188:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 391, 6, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 198, 6, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 5, 6, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK189:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 390, 4, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 197, 4, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 4, 4, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK190:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 389, 3, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 196, 3, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 3, 3, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK191:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 388, 2, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 195, 2, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 2, 2, m_Sound.volume);
				break;
			}
		case ID_PRZYCISK192:
			if (m_Sound.octave == 1) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 387, 1, 0);
				break;
			}
			else if (m_Sound.octave == 2) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 194, 1, m_Sound.volume);
				break;
			}
			else if (m_Sound.octave == 3) {
				m_Sound.AddNote(hwnd, m_Sound.current_layer, 1, 1, m_Sound.volume);
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

	HWND hwnd, hPrzycisk1, hPrzycisk2, hPrzycisk3, hPrzycisk4, hPrzycisk5, hPrzycisk6, hPrzycisk7, hPrzycisk8, hPrzycisk9, hPrzycisk10, hPrzycisk11, hPrzycisk12, hPrzycisk13, hPrzycisk14, hPrzycisk15, hPrzycisk16, hPrzycisk17, hPrzycisk18, hPrzycisk19, hPrzycisk20, hPrzycisk21, hPrzycisk22, hPrzycisk23, hPrzycisk24, hPrzycisk25, hPrzycisk26, hPrzycisk27, hPrzycisk28, hPrzycisk29, hPrzycisk30, hPrzycisk31, hPrzycisk32, hPrzycisk33, hPrzycisk34, hPrzycisk35, hPrzycisk36, hPrzycisk37, hPrzycisk38, hPrzycisk39, hPrzycisk40, hPrzycisk41, hPrzycisk42, hPrzycisk43, hPrzycisk44, hPrzycisk45, hPrzycisk46, hPrzycisk47, hPrzycisk48, hPrzycisk49, hPrzycisk50, hPrzycisk51, hPrzycisk52, hPrzycisk53, hPrzycisk54, hPrzycisk55, hPrzycisk56, hPrzycisk57, hPrzycisk58, hPrzycisk59, hPrzycisk60, hPrzycisk61, hPrzycisk62, hPrzycisk63, hPrzycisk64, hPrzycisk65, hPrzycisk66, hPrzycisk67, hPrzycisk68, hPrzycisk69, hPrzycisk70, hPrzycisk71, hPrzycisk72, hPrzycisk73, hPrzycisk74, hPrzycisk75, hPrzycisk76, hPrzycisk77, hPrzycisk78, hPrzycisk79, hPrzycisk80, hPrzycisk81, hPrzycisk82, hPrzycisk83, hPrzycisk84, hPrzycisk85, hPrzycisk86, hPrzycisk87, hPrzycisk88, hPrzycisk89, hPrzycisk90, hPrzycisk91, hPrzycisk92, hPrzycisk93, hPrzycisk94, hPrzycisk95, hPrzycisk96, hPrzycisk97, hPrzycisk98, hPrzycisk99, hPrzycisk100, hPrzycisk101, hPrzycisk102, hPrzycisk103, hPrzycisk104, hPrzycisk105, hPrzycisk106, hPrzycisk107, hPrzycisk108, hPrzycisk109, hPrzycisk110, hPrzycisk111, hPrzycisk112, hPrzycisk113, hPrzycisk114, hPrzycisk115, hPrzycisk116, hPrzycisk117, hPrzycisk118, hPrzycisk119, hPrzycisk120, hPrzycisk121, hPrzycisk122, hPrzycisk123, hPrzycisk124, hPrzycisk125, hPrzycisk126, hPrzycisk127, hPrzycisk128, hPrzycisk129, hPrzycisk130, hPrzycisk131, hPrzycisk132, hPrzycisk133, hPrzycisk134, hPrzycisk135, hPrzycisk136, hPrzycisk137, hPrzycisk138, hPrzycisk139, hPrzycisk140, hPrzycisk141, hPrzycisk142, hPrzycisk143, hPrzycisk144, hPrzycisk145, hPrzycisk146, hPrzycisk147, hPrzycisk148, hPrzycisk149, hPrzycisk150, hPrzycisk151, hPrzycisk152, hPrzycisk153, hPrzycisk154, hPrzycisk155, hPrzycisk156, hPrzycisk157, hPrzycisk158, hPrzycisk159, hPrzycisk160, hPrzycisk161, hPrzycisk162, hPrzycisk163, hPrzycisk164, hPrzycisk165, hPrzycisk166, hPrzycisk167, hPrzycisk168, hPrzycisk169, hPrzycisk170, hPrzycisk171, hPrzycisk172, hPrzycisk173, hPrzycisk174, hPrzycisk175, hPrzycisk176, hPrzycisk177, hPrzycisk178, hPrzycisk179, hPrzycisk180, hPrzycisk181, hPrzycisk182, hPrzycisk183, hPrzycisk184, hPrzycisk185, hPrzycisk186, hPrzycisk187, hPrzycisk188, hPrzycisk189, hPrzycisk190, hPrzycisk191, hPrzycisk192, hPrzycisk193, hPrzycisk194, hPrzycisk195, hPrzycisk196, hPrzycisk197, hPrzycisk198, hPrzycisk199, hPrzycisk200;
	HWND save, open, octave23, octave45, octave67, volum0,volum1, volum2, volum3, volum4, volum5, openerr, octaves24, octaves57, current_layer_1, current_layer_2, current_layer_3, current_layer_4, current_layer_5, add_pause, display_next, display_previous, delete_last;

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


	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, NazwaKlasy, "Mini keys", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 720, NULL, NULL, hInstance, NULL);
	
	open = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Play", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 0, 100, 40, hwnd, (HMENU)play, hInstance, NULL);
	octave23 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 2,3", WS_CHILD | WS_VISIBLE | WS_BORDER, 105, 0, 100, 40, hwnd, (HMENU)octave3, hInstance, NULL);
	octave45 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 4,5", WS_CHILD | WS_VISIBLE | WS_BORDER, 205, 0, 100, 40, hwnd, (HMENU)octave5, hInstance, NULL);
	octave67 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octave 6,7", WS_CHILD | WS_VISIBLE | WS_BORDER, 305, 0, 100, 40, hwnd, (HMENU)octave7, hInstance, NULL);
	save = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Save", WS_CHILD | WS_VISIBLE | WS_BORDER, 405, 0, 100, 40, hwnd, (HMENU)saver, hInstance, NULL);
	openerr = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Open", WS_CHILD | WS_VISIBLE | WS_BORDER, 505, 0, 100, 40, hwnd, (HMENU)opener, hInstance, NULL);
	volum0 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-15 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 605, 0, 60, 40, hwnd, (HMENU)vol0, hInstance, NULL);
	volum1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-10 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 665, 0, 60, 40, hwnd, (HMENU)vol1, hInstance, NULL);
	volum2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-7,5 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 725, 0, 60, 40, hwnd, (HMENU)vol2, hInstance, NULL);
	volum3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-5 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 785, 0, 60, 40, hwnd, (HMENU)vol3, hInstance, NULL);
	volum4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "-2,5 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 845, 0, 60, 40, hwnd, (HMENU)vol4, hInstance, NULL);
	volum5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "0 dB", WS_CHILD | WS_VISIBLE | WS_BORDER, 905, 0, 60, 40, hwnd, (HMENU)vol5, hInstance, NULL);

	octaves24 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octaves 2-4", WS_CHILD | WS_VISIBLE | WS_BORDER, 985, 0, 100, 40, hwnd, (HMENU)octave24, hInstance, NULL);
	octaves57 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Octaves 5-7", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 0, 100, 40, hwnd, (HMENU)octave57, hInstance, NULL);

	current_layer_1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Layer 1", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 80, 100, 40, hwnd, (HMENU)current_layer1, hInstance, NULL);
	current_layer_2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Layer 2", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 120, 100, 40, hwnd, (HMENU)current_layer2, hInstance, NULL);
	current_layer_3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Layer 3", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 160, 100, 40, hwnd, (HMENU)current_layer3, hInstance, NULL);
	current_layer_4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Layer 4", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 200, 100, 40, hwnd, (HMENU)current_layer4, hInstance, NULL);
	current_layer_5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Layer 5", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 240, 100, 40, hwnd, (HMENU)current_layer5, hInstance, NULL);

	add_pause = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Pause", WS_CHILD | WS_VISIBLE | WS_BORDER, 1085, 280, 100, 40, hwnd, (HMENU)addpause, hInstance, NULL);

	display_next = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", ">", WS_CHILD | WS_VISIBLE | WS_BORDER, 1045, 280, 40, 40, hwnd, (HMENU)next_display, hInstance, NULL);
	display_previous = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "<", WS_CHILD | WS_VISIBLE | WS_BORDER, 1005, 280, 40, 40, hwnd, (HMENU)previous_display, hInstance, NULL);
	delete_last = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Delete last note", WS_CHILD | WS_VISIBLE | WS_BORDER, 985, 40, 200, 40, hwnd, (HMENU)last_delete, hInstance, NULL);

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

	HWND hStatic_layer = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 400, 600, 20, hwnd, NULL, hInstance, NULL);
	hStatic_layer_value = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 420, 600, 20, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic_layer, "Current layer: ");
	SetWindowText(hStatic_layer_value, "1");

	HWND hStatic_octaves = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 460, 600, 20, hwnd, NULL, hInstance, NULL);
	hStatic_octaves_value = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 480, 600, 20, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic_octaves, "Current keyboard octaves: ");
	SetWindowText(hStatic_octaves_value, "2-3");

	HWND hStatic_display = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 520, 600, 20, hwnd, NULL, hInstance, NULL);
	hStatic_display_value = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 540, 600, 20, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic_display, "Current display octaves: ");
	SetWindowText(hStatic_display_value, "2-4");

	HWND hStatic_volume = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 580, 600, 20, hwnd, NULL, hInstance, NULL);
	hStatic_volume_value = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 1000, 600, 600, 20, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic_volume, "Current volume: ");
	SetWindowText(hStatic_volume_value, "0 dB");

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);
	hPrzycisk3 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK3, hInstance, NULL);
	hPrzycisk4 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK4, hInstance, NULL);
	hPrzycisk5 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK5, hInstance, NULL);
	hPrzycisk6 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK6, hInstance, NULL);
	hPrzycisk7 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK7, hInstance, NULL);
	hPrzycisk8 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK8, hInstance, NULL);
	
	hPrzycisk9 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK9, hInstance, NULL);
	hPrzycisk10 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK10, hInstance, NULL);
	hPrzycisk11 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK11, hInstance, NULL);
	hPrzycisk12 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK12, hInstance, NULL);
	hPrzycisk13 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK13, hInstance, NULL);
	hPrzycisk14 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK14, hInstance, NULL);
	hPrzycisk15 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK15, hInstance, NULL);
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
	hPrzycisk26 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK26, hInstance, NULL);
	hPrzycisk27 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK27, hInstance, NULL);
	hPrzycisk28 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK28, hInstance, NULL);
	hPrzycisk29 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK29, hInstance, NULL);
	hPrzycisk30 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK30, hInstance, NULL);
	hPrzycisk31 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK31, hInstance, NULL);
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

	hPrzycisk49 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK49, hInstance, NULL);
	hPrzycisk50 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK50, hInstance, NULL);
	hPrzycisk51 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK51, hInstance, NULL);
	hPrzycisk52 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK52, hInstance, NULL);
	hPrzycisk53 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK53, hInstance, NULL);
	hPrzycisk54 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK54, hInstance, NULL);
	hPrzycisk55 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK55, hInstance, NULL);
	hPrzycisk56 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 270, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK56, hInstance, NULL);

	hPrzycisk57 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK57, hInstance, NULL);
	hPrzycisk58 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK58, hInstance, NULL);
	hPrzycisk59 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK59, hInstance, NULL);
	hPrzycisk60 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK60, hInstance, NULL);
	hPrzycisk61 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK61, hInstance, NULL);
	hPrzycisk62 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK62, hInstance, NULL);
	hPrzycisk63 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK63, hInstance, NULL);
	hPrzycisk64 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK64, hInstance, NULL);

	hPrzycisk65 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK65, hInstance, NULL);
	hPrzycisk66 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK66, hInstance, NULL);
	hPrzycisk67 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK67, hInstance, NULL);
	hPrzycisk68 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK68, hInstance, NULL);
	hPrzycisk69 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK69, hInstance, NULL);
	hPrzycisk70 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK70, hInstance, NULL);
	hPrzycisk71 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK71, hInstance, NULL);
	hPrzycisk72 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK72, hInstance, NULL);

	hPrzycisk73 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK73, hInstance, NULL);
	hPrzycisk74 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK74, hInstance, NULL);
	hPrzycisk75 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK75, hInstance, NULL);
	hPrzycisk76 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK76, hInstance, NULL);
	hPrzycisk77 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK77, hInstance, NULL);
	hPrzycisk78 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK78, hInstance, NULL);
	hPrzycisk79 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK79, hInstance, NULL);
	hPrzycisk80 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK80, hInstance, NULL);

	hPrzycisk81 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK81, hInstance, NULL);
	hPrzycisk82 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK82, hInstance, NULL);
	hPrzycisk83 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK83, hInstance, NULL);
	hPrzycisk84 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK84, hInstance, NULL);
	hPrzycisk85 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK85, hInstance, NULL);
	hPrzycisk86 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK86, hInstance, NULL);
	hPrzycisk87 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK87, hInstance, NULL);
	hPrzycisk88 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK88, hInstance, NULL);

	hPrzycisk89 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK89, hInstance, NULL);
	hPrzycisk90 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK90, hInstance, NULL);
	hPrzycisk91 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK91, hInstance, NULL);
	hPrzycisk92 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK92, hInstance, NULL);
	hPrzycisk93 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK93, hInstance, NULL);
	hPrzycisk94 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK94, hInstance, NULL);
	hPrzycisk95 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK95, hInstance, NULL);
	hPrzycisk96 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 470, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK96, hInstance, NULL);

	hPrzycisk97 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK97, hInstance, NULL);
	hPrzycisk98 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK98, hInstance, NULL);
	hPrzycisk99 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK99, hInstance, NULL);
	hPrzycisk100 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK100, hInstance, NULL);
	hPrzycisk101 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK101, hInstance, NULL);
	hPrzycisk102 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK102, hInstance, NULL);
	hPrzycisk103 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK103, hInstance, NULL);
	hPrzycisk104 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 510, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK104, hInstance, NULL);

	hPrzycisk105 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK105, hInstance, NULL);
	hPrzycisk106 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK106, hInstance, NULL);
	hPrzycisk107 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK107, hInstance, NULL);
	hPrzycisk108 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK108, hInstance, NULL);
	hPrzycisk109 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK109, hInstance, NULL);
	hPrzycisk110 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK110, hInstance, NULL);
	hPrzycisk111 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK111, hInstance, NULL);
	hPrzycisk112 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 550, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK112, hInstance, NULL);

	hPrzycisk113 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK113, hInstance, NULL);
	hPrzycisk114 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK114, hInstance, NULL);
	hPrzycisk115 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK115, hInstance, NULL);
	hPrzycisk116 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK116, hInstance, NULL);
	hPrzycisk117 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK117, hInstance, NULL);
	hPrzycisk118 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK118, hInstance, NULL);
	hPrzycisk119 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK119, hInstance, NULL);
	hPrzycisk120 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 590, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK120, hInstance, NULL);

	hPrzycisk121 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK121, hInstance, NULL);
	hPrzycisk122 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK122, hInstance, NULL);
	hPrzycisk123 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK123, hInstance, NULL);
	hPrzycisk124 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK124, hInstance, NULL);
	hPrzycisk125 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK125, hInstance, NULL);
	hPrzycisk126 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK126, hInstance, NULL);
	hPrzycisk127 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK127, hInstance, NULL);
	hPrzycisk128 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 630, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK128, hInstance, NULL);

	hPrzycisk129 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK129, hInstance, NULL);
	hPrzycisk130 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK130, hInstance, NULL);
	hPrzycisk131 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK131, hInstance, NULL);
	hPrzycisk132 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK132, hInstance, NULL);
	hPrzycisk133 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK133, hInstance, NULL);
	hPrzycisk134 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK134, hInstance, NULL);
	hPrzycisk135 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK135, hInstance, NULL);
	hPrzycisk136 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 670, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK136, hInstance, NULL);

	hPrzycisk137 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK137, hInstance, NULL);
	hPrzycisk138 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK138, hInstance, NULL);
	hPrzycisk139 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK139, hInstance, NULL);
	hPrzycisk140 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK140, hInstance, NULL);
	hPrzycisk141 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK141, hInstance, NULL);
	hPrzycisk142 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK142, hInstance, NULL);
	hPrzycisk143 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK143, hInstance, NULL);
	hPrzycisk144 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 710, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK144, hInstance, NULL);

	hPrzycisk145 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK145, hInstance, NULL);
	hPrzycisk146 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK146, hInstance, NULL);
	hPrzycisk147 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK147, hInstance, NULL);
	hPrzycisk148 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK148, hInstance, NULL);
	hPrzycisk149 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK149, hInstance, NULL);
	hPrzycisk150 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK150, hInstance, NULL);
	hPrzycisk151 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK151, hInstance, NULL);
	hPrzycisk152 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK152, hInstance, NULL);

	hPrzycisk153 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK153, hInstance, NULL);
	hPrzycisk154 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK154, hInstance, NULL);
	hPrzycisk155 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK155, hInstance, NULL);
	hPrzycisk156 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK156, hInstance, NULL);
	hPrzycisk157 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK157, hInstance, NULL);
	hPrzycisk158 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK158, hInstance, NULL);
	hPrzycisk159 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK159, hInstance, NULL);
	hPrzycisk160 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 790, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK160, hInstance, NULL);

	hPrzycisk161 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK161, hInstance, NULL);
	hPrzycisk162 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK162, hInstance, NULL);
	hPrzycisk163 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK163, hInstance, NULL);
	hPrzycisk164 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK164, hInstance, NULL);
	hPrzycisk165 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK165, hInstance, NULL);
	hPrzycisk166 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK166, hInstance, NULL);
	hPrzycisk167 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK167, hInstance, NULL);
	hPrzycisk168 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 830, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK168, hInstance, NULL);

	hPrzycisk169 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK169, hInstance, NULL);
	hPrzycisk170 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK170, hInstance, NULL);
	hPrzycisk171 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK171, hInstance, NULL);
	hPrzycisk172 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK172, hInstance, NULL);
	hPrzycisk173 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK173, hInstance, NULL);
	hPrzycisk174 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK174, hInstance, NULL);
	hPrzycisk175 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK175, hInstance, NULL);
	hPrzycisk176 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 870, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK176, hInstance, NULL);

	hPrzycisk177 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK177, hInstance, NULL);
	hPrzycisk178 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK178, hInstance, NULL);
	hPrzycisk179 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/2", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK179, hInstance, NULL);
	hPrzycisk180 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK180, hInstance, NULL);
	hPrzycisk181 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/4", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK181, hInstance, NULL);
	hPrzycisk182 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "3/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK182, hInstance, NULL);
	hPrzycisk183 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/8", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK183, hInstance, NULL);
	hPrzycisk184 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "1/16", WS_CHILD | WS_VISIBLE | WS_BORDER, 910, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK184, hInstance, NULL);

	hPrzycisk185 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 330, 40, 40, hwnd, (HMENU)ID_PRZYCISK185, hInstance, NULL);
	hPrzycisk186 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 370, 40, 40, hwnd, (HMENU)ID_PRZYCISK186, hInstance, NULL);
	hPrzycisk187 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 410, 40, 40, hwnd, (HMENU)ID_PRZYCISK187, hInstance, NULL);
	hPrzycisk188 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 450, 40, 40, hwnd, (HMENU)ID_PRZYCISK188, hInstance, NULL);
	hPrzycisk189 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 490, 40, 40, hwnd, (HMENU)ID_PRZYCISK189, hInstance, NULL);
	hPrzycisk190 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 530, 40, 40, hwnd, (HMENU)ID_PRZYCISK190, hInstance, NULL);
	hPrzycisk191 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 570, 40, 40, hwnd, (HMENU)ID_PRZYCISK191, hInstance, NULL);
	hPrzycisk192 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 950, 610, 40, 40, hwnd, (HMENU)ID_PRZYCISK192, hInstance, NULL);

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
