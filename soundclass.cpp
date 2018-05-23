#include <Windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "soundclass.h"
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


SoundClass::SoundClass(const SoundClass& other)
{
}

SoundClass::~SoundClass()
{
}

//pocz¹tek systemu odtwarzania dŸwiêku

SoundClass::SoundClass()
{
	m_DirectSound = 0;
	m_primaryBuffer = 0;
	m_secondaryBuffer1 = 0;
	m_secondaryBuffer2 = 0;
	m_secondaryBuffer3 = 0;
	m_secondaryBuffer4 = 0;
	m_secondaryBuffer5 = 0;
	m_secondaryBuffer6 = 0;
	m_secondaryBuffer7 = 0;
	m_secondaryBuffer8 = 0;
	m_secondaryBuffer9 = 0;
	m_secondaryBuffer10 = 0;
	m_secondaryBuffer11 = 0;
	m_secondaryBuffer12 = 0;
	m_secondaryBuffer13 = 0;
	m_secondaryBuffer14 = 0;
	m_secondaryBuffer15 = 0;
	m_secondaryBuffer16 = 0;
	m_secondaryBuffer17 = 0;
	m_secondaryBuffer18 = 0;
	m_secondaryBuffer19 = 0;
	m_secondaryBuffer20 = 0;
}


bool SoundClass::Initialize(HWND hwnd)
{
	bool result;
	// Initialize direct sound and the primary sound buffer
	result = InitializeDirectSound(hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void SoundClass::Shutdown()
{
	// Release the secondary buffer.
	ShutdownWaveFile(&m_secondaryBuffer1);
	ShutdownWaveFile(&m_secondaryBuffer2);
	ShutdownWaveFile(&m_secondaryBuffer3);
	ShutdownWaveFile(&m_secondaryBuffer4);
	ShutdownWaveFile(&m_secondaryBuffer5);
	ShutdownWaveFile(&m_secondaryBuffer6);
	ShutdownWaveFile(&m_secondaryBuffer7);
	ShutdownWaveFile(&m_secondaryBuffer8);
	ShutdownWaveFile(&m_secondaryBuffer9);
	ShutdownWaveFile(&m_secondaryBuffer10);
	ShutdownWaveFile(&m_secondaryBuffer11);
	ShutdownWaveFile(&m_secondaryBuffer12);
	ShutdownWaveFile(&m_secondaryBuffer13);
	ShutdownWaveFile(&m_secondaryBuffer14);
	ShutdownWaveFile(&m_secondaryBuffer15);
	ShutdownWaveFile(&m_secondaryBuffer16);
	ShutdownWaveFile(&m_secondaryBuffer17);
	ShutdownWaveFile(&m_secondaryBuffer18);
	ShutdownWaveFile(&m_secondaryBuffer19);
	ShutdownWaveFile(&m_secondaryBuffer20);
	return;
}

bool SoundClass::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;


	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &m_DirectSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = m_DirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}
	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Get control of the primary sound buffer on the default sound device.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}
	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the primary buffer to be the wave format specified.
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void SoundClass::ShutdownDirectSound()
{
	// Release the primary sound buffer pointer.
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// Release the direct sound interface pointer.
	if (m_DirectSound)
	{
		m_DirectSound->Release();
		m_DirectSound = 0;
	}

	return;
}

bool SoundClass::LoadWaveFile(char* filename, IDirectSoundBuffer8** secondaryBuffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;

	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if (waveFileHeader.numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_DirectSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	return true;
}

void SoundClass::ShutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	// Release the secondary sound buffer.
	if (*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = 0;
	}

	return;
}


bool SoundClass::PlayWaveFile(IDirectSoundBuffer8** secondaryBuffer, long volume)
{
	HRESULT result;

	// Set position at the beginning of the sound buffer.
	result = (*secondaryBuffer)->SetCurrentPosition(0);

	if (FAILED(result))
	{
		return false;
	}

	// Set volume of the buffer to 100%.
	result = (*secondaryBuffer)->SetVolume(DSBVOLUME_MAX + volume);

	if (FAILED(result))
	{
		return false;
	}

	// Play the contents of the secondary sound buffer.
	result = (*secondaryBuffer)->Play(0, 0, 0);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void SoundClass::wyswietl(int layer, int octaves, int time, HDC* hdc, HDC* hdcNowy, HDC* hdcNowy2)
{
	 int pixel_x = 30;
	 int pixel_y = 40;
	 int temp = 0;

	if (octaves == 1)
	{
		switch (layer)
		{
		case 1:
			for (int i = 1; i < 289; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer1[j].note_id >= i && layer1[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer1[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;
			
		case 2:
			for (int i = 1; i < 289; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer2[j].note_id >= i && layer2[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer2[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 3:
			for (int i = 1; i < 289; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer3[j].note_id >= i && layer3[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer3[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 4:
			for (int i = 1; i < 289; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer4[j].note_id >= i && layer4[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer4[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 5:
			for (int i = 1; i < 289; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer5[j].note_id >= i && layer5[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer5[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		default:
			break;
		}
	}
	else
	{
		switch (layer)
		{
		case 1:
			for (int i = 289; i < 577; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer1[j].note_id >= i && layer1[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer1[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 2:
			for (int i = 289; i < 577; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer2[j].note_id >= i && layer2[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer2[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 3:
			for (int i = 289; i < 577; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer3[j].note_id >= i && layer3[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer3[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 4:
			for (int i = 289; i < 577; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer4[j].note_id >= i && layer4[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer4[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		case 5:
			for (int i = 289; i < 577; i += 8)
			{
				for (int j = time; j < time + 32; j++)
				{
					if (layer5[j].note_id >= i && layer5[j].note_id < i + 8)
					{
						temp = j;
						for (int k = 0; k < layer5[temp].note_length; k++)
						{
							BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy2, 0, 0, SRCCOPY);
							j++;
							pixel_x += 29;
						}
						j--;
					}
					else
					{
						BitBlt(*hdc, pixel_x, pixel_y, 28, 7, *hdcNowy, 0, 0, SRCCOPY);
						pixel_x += 29;
					}
				}
				pixel_y += 8;
				pixel_x = 30;
			}
			break;

		default:
			break;
		}
	}
}

void SoundClass::AddNote(HWND hwnd, int layer, int note_id, int note_length, int note_volume)
{
	switch (layer)
	{
	case 1:
		layer1[layer1_counter].note_id = note_id;
		layer1[layer1_counter].note_length = note_length;
		layer1[layer1_counter].note_volume = note_volume;
		fn += 24 * layer1[layer1_counter].note_id;
		InitializeDirectSound(hwnd);
		LoadWaveFile(fn, &m_secondaryBuffer1);
		PlayWaveFile(&m_secondaryBuffer1, volume);
		Sleep(layer1[layer1_counter].note_length * 116 + 1000);
		Shutdown();
		ShutdownDirectSound();
		fn -= 24 * layer1[layer1_counter].note_id;
		layer1_counter += layer1[layer1_counter].note_length;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case 2:
		layer2[layer2_counter].note_id = note_id;
		layer2[layer2_counter].note_length = note_length;
		layer2[layer2_counter].note_volume = note_volume;
		layer2_counter++;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case 3:
		layer3[layer3_counter].note_id = note_id;
		layer3[layer3_counter].note_length = note_length;
		layer3[layer3_counter].note_volume = note_volume;
		layer3_counter++;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case 4:
		layer4[layer4_counter].note_id = note_id;
		layer4[layer4_counter].note_length = note_length;
		layer4[layer4_counter].note_volume = note_volume;
		layer4_counter++;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		break;
	case 5:
		layer5[layer5_counter].note_id = note_id;
		layer5[layer5_counter].note_length = note_length;
		layer5[layer5_counter].note_volume = note_volume;
		layer5_counter++;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
		break;
	}

}


void SoundClass::playback()
{
	//przygotowanie wszystkich zmiennych potrzebnych do odtwarzania
	sound_playing = 5;
	layer1_counter = 0;
	layer2_counter = 0;
	layer3_counter = 0;
	layer4_counter = 0;
	layer5_counter = 0;
	layer1_playing = 1;
	layer2_playing = 1;
	layer3_playing = 1;
	layer4_playing = 1;
	layer5_playing = 1;
	counter1 = 0;
	counter2 = 0;
	counter3 = 0;
	counter4 = 0;
	counter5 = 0;
	until_next_note = 0;
	until_next_note1 = 0;
	until_next_note2 = 0;
	until_next_note3 = 0;
	until_next_note4 = 0;
	until_next_note5 = 0;

	//pêtla odtwarzaj¹ca dŸwiêk ze wszystkich warstw
	while (sound_playing)
	{
		//je¿eli czas do nastêpnej nuty=0 i nadal s¹ jeszcze jakieœ nuty do odtworzenia
		if (until_next_note1 == 0 && layer1_playing != 0)
		{
			//odtwarzanie nut na zmianê w ka¿dym z 4 buforów, ¿eby dŸwiêk siê nagle nie urywa³ przy za³adowaniu nastêpnego do bufora
			switch (counter1)
			{
			case 0:
			{
				//je¿eli nie ma wiêcej dŸwiêków na warstwie, zmienna zmieniana na "false"
				if (layer1[layer1_counter].note_length == 0)
				{
					layer1_playing = 0;
					//niewa¿ne xd
					until_next_note1 = 100000;
					break;
				}
				//wskaŸnik na nazwy plików przechodzi na nazwê pliku dŸwiêkowego aktualnej nuty
				fn += 24 * layer1[layer1_counter].note_id;

				//nuta jest wczytywana do bufora i odtwarzana
				LoadWaveFile(fn, &m_secondaryBuffer1);
				PlayWaveFile(&m_secondaryBuffer1, layer1[layer1_counter].note_volume);

				//wskaŸnik wraca na domyœln¹ pozycjê
				fn -= 24 * layer1[layer1_counter].note_id;

				//sprawdzana jest odleg³oœæ w czasie do nastêpnego dŸwiêku na warstwie
				until_next_note1 = layer1[layer1_counter].note_length;

				//licznik okreœlaj¹cy pozycjê w czasie na warstwie przechodzi na nastêpny dŸwiêk
				layer1_counter += layer1[layer1_counter].note_length;

				//zmienna okreœlaj¹ca, z którego bufora korzystamy
				counter1++;
				break;
			}
			case 1:
			{
				if (layer1[layer1_counter].note_length == 0)
				{
					layer1_playing = 0;
					until_next_note1 = 100000;
					break;
				}
				fn += 24 * layer1[layer1_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer2);
				PlayWaveFile(&m_secondaryBuffer2, layer1[layer1_counter].note_volume);
				fn -= 24 * layer1[layer1_counter].note_id;
				until_next_note1 = layer1[layer1_counter].note_length;
				layer1_counter += layer1[layer1_counter].note_length;
				counter1++;
				break;
			}
			case 2:
			{
				if (layer1[layer1_counter].note_length == 0)
				{
					layer1_playing = 0;
					until_next_note1 = 100000;
					break;
				}
				fn += 24 * layer1[layer1_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer3);
				PlayWaveFile(&m_secondaryBuffer3, layer1[layer1_counter].note_volume);
				fn -= 24 * layer1[layer1_counter].note_id;
				until_next_note1 = layer1[layer1_counter].note_length;
				layer1_counter += layer1[layer1_counter].note_length;
				counter1++;
				break;
			}
			case 3:
			{
				if (layer1[layer1_counter].note_length == 0)
				{
					layer1_playing = 0;
					until_next_note1 = 100000;
					break;
				}
				fn += 24 * layer1[layer1_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer4);
				PlayWaveFile(&m_secondaryBuffer4, layer1[layer1_counter].note_volume);
				fn -= 24 * layer1[layer1_counter].note_id;
				until_next_note1 = layer1[layer1_counter].note_length;
				layer1_counter += layer1[layer1_counter].note_length;
				counter1 = 0;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		if (until_next_note2 == 0 && layer2_playing != 0)
		{
			switch (counter2)
			{
			case 0:
			{
				if (layer2[layer2_counter].note_length == 0)
				{
					layer2_playing = 0;
					until_next_note2 = 100000;
					break;
				}
				fn += 24 * layer2[layer2_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer5);
				PlayWaveFile(&m_secondaryBuffer5, layer2[layer2_counter].note_volume);
				fn -= 24 * layer2[layer2_counter].note_id;
				until_next_note2 = layer2[layer2_counter].note_length;
				layer2_counter += layer2[layer2_counter].note_length;
				counter2++;
				break;
			}

			case 1:
			{
				if (layer2[layer2_counter].note_length == 0)
				{
					layer2_playing = 0;
					until_next_note2 = 100000;
					break;
				}
				fn += 24 * layer2[layer2_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer6);
				PlayWaveFile(&m_secondaryBuffer6, layer2[layer2_counter].note_volume);
				fn -= 24 * layer2[layer2_counter].note_id;
				until_next_note2 = layer2[layer2_counter].note_length;
				layer2_counter += layer2[layer2_counter].note_length;
				counter2++;
				break;
			}
			case 2:
			{
				if (layer2[layer2_counter].note_length == 0)
				{
					layer2_playing = 0;
					until_next_note2 = 100000;
					break;
				}
				fn += 24 * layer2[layer2_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer7);
				PlayWaveFile(&m_secondaryBuffer7, layer2[layer2_counter].note_volume);
				fn -= 24 * layer2[layer2_counter].note_id;
				until_next_note2 = layer2[layer2_counter].note_length;
				layer2_counter += layer2[layer2_counter].note_length;
				counter2++;
				break;
			}
			case 3:
			{
				if (layer2[layer2_counter].note_length == 0)
				{
					layer2_playing = 0;
					until_next_note2 = 100000;
					break;
				}
				fn += 24 * layer2[layer2_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer8);
				PlayWaveFile(&m_secondaryBuffer8, layer2[layer2_counter].note_volume);
				fn -= 24 * layer2[layer2_counter].note_id;
				until_next_note2 = layer2[layer2_counter].note_length;
				layer2_counter += layer2[layer2_counter].note_length;
				counter2 = 0;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		if (until_next_note3 == 0 && layer3_playing != 0)
		{
			switch (counter3)
			{
			case 0:
			{
				if (layer3[layer3_counter].note_length == 0)
				{
					layer3_playing = 0;
					until_next_note3 = 100000;
					break;
				}
				fn += 24 * layer3[layer3_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer9);
				PlayWaveFile(&m_secondaryBuffer9, layer3[layer3_counter].note_volume);
				fn -= 24 * layer3[layer3_counter].note_id;
				until_next_note3 = layer3[layer3_counter].note_length;
				layer3_counter += layer3[layer3_counter].note_length;
				counter3++;
				break;
			}
			case 1:
			{
				if (layer3[layer3_counter].note_length == 0)
				{
					layer3_playing = 0;
					until_next_note3 = 100000;
					break;
				}
				fn += 24 * layer3[layer3_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer10);
				PlayWaveFile(&m_secondaryBuffer10, layer3[layer3_counter].note_volume);
				fn -= 24 * layer3[layer3_counter].note_id;
				until_next_note3 = layer3[layer3_counter].note_length;
				layer3_counter += layer3[layer3_counter].note_length;
				counter3++;
				break;
			}
			case 2:
			{
				if (layer3[layer3_counter].note_length == 0)
				{
					layer3_playing = 0;
					break;
				}
				fn += 24 * layer3[layer3_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer11);
				PlayWaveFile(&m_secondaryBuffer11, layer3[layer3_counter].note_volume);
				fn -= 24 * layer3[layer3_counter].note_id;
				until_next_note3 = layer3[layer3_counter].note_length;
				layer3_counter += layer3[layer3_counter].note_length;
				counter3++;
				break;
			}
			case 3:
			{
				if (layer3[layer3_counter].note_length == 0)
				{
					layer3_playing = 0;
					until_next_note3 = 100000;
					break;
				}
				fn += 24 * layer3[layer3_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer12);
				PlayWaveFile(&m_secondaryBuffer12, layer3[layer3_counter].note_volume);
				fn -= 24 * layer3[layer3_counter].note_id;
				until_next_note3 = layer3[layer3_counter].note_length;
				layer3_counter += layer3[layer3_counter].note_length;
				counter3 = 0;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		if (until_next_note4 == 0 && layer4_playing != 0)
		{
			switch (counter4)
			{
			case 0:
			{
				if (layer4[layer4_counter].note_length == 0)
				{
					layer4_playing = 0;
					until_next_note4 = 100000;
					break;
				}
				fn += 24 * layer4[layer4_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer13);
				PlayWaveFile(&m_secondaryBuffer13, layer4[layer4_counter].note_volume);
				fn -= 24 * layer4[layer4_counter].note_id;
				until_next_note4 = layer4[layer4_counter].note_length;
				layer4_counter += layer4[layer4_counter].note_length;
				counter4++;
				break;
			}
			case 1:
			{
				if (layer4[layer4_counter].note_length == 0)
				{
					layer4_playing = 0;
					until_next_note4 = 100000;
					break;
				}
				fn += 24 * layer4[layer4_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer14);
				PlayWaveFile(&m_secondaryBuffer14, layer4[layer4_counter].note_volume);
				fn -= 24 * layer4[layer4_counter].note_id;
				until_next_note4 = layer4[layer4_counter].note_length;
				layer4_counter += layer4[layer4_counter].note_length;
				counter4++;
				break;
			}
			case 2:
			{
				if (layer4[layer4_counter].note_length == 0)
				{
					layer4_playing = 0;
					until_next_note4 = 100000;
					break;
				}
				fn += 24 * layer4[layer4_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer15);
				PlayWaveFile(&m_secondaryBuffer15, layer4[layer4_counter].note_volume);
				fn -= 24 * layer4[layer4_counter].note_id;
				until_next_note4 = layer4[layer4_counter].note_length;
				layer4_counter += layer4[layer4_counter].note_length;
				counter4++;
				break;
			}
			case 3:
			{
				if (layer4[layer4_counter].note_length == 0)
				{
					layer4_playing = 0;
					until_next_note4 = 100000;
					break;
				}
				fn += 24 * layer4[layer4_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer16);
				PlayWaveFile(&m_secondaryBuffer16, layer4[layer4_counter].note_volume);
				fn -= 24 * layer4[layer4_counter].note_id;
				until_next_note4 = layer4[layer4_counter].note_length;
				layer4_counter += layer4[layer4_counter].note_length;
				counter4 = 0;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		if (until_next_note5 == 0 && layer5_playing != 0)
		{
			switch (counter5)
			{
			case 0:
			{
				if (layer5[layer5_counter].note_length == 0)
				{
					layer5_playing = 0;
					until_next_note5 = 100000;
					break;
				}
				fn += 24 * layer5[layer5_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer17);
				PlayWaveFile(&m_secondaryBuffer17, layer5[layer5_counter].note_volume);
				fn -= 24 * layer5[layer5_counter].note_id;
				until_next_note5 = layer5[layer5_counter].note_length;
				layer5_counter += layer5[layer5_counter].note_length;
				counter5++;
				break;
			}
			case 1:
			{
				if (layer5[layer5_counter].note_length == 0)
				{
					layer5_playing = 0;
					until_next_note5 = 100000;
					break;
				}
				fn += 24 * layer5[layer5_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer18);
				PlayWaveFile(&m_secondaryBuffer18, layer5[layer5_counter].note_volume);
				fn -= 24 * layer5[layer5_counter].note_id;
				until_next_note5 = layer5[layer5_counter].note_length;
				layer5_counter += layer5[layer5_counter].note_length;
				counter5++;
				break;
			}
			case 2:
			{
				if (layer5[layer5_counter].note_length == 0)
				{
					layer5_playing = 0;
					until_next_note5 = 100000;
					break;
				}
				fn += 24 * layer5[layer5_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer19);
				PlayWaveFile(&m_secondaryBuffer19, layer5[layer5_counter].note_volume);
				fn -= 24 * layer5[layer5_counter].note_id;
				until_next_note5 = layer5[layer5_counter].note_length;
				layer5_counter += layer5[layer5_counter].note_length;
				counter5++;
				break;
			}
			case 3:
			{
				if (layer5[layer5_counter].note_length == 0)
				{
					layer5_playing = 0;
					until_next_note5 = 100000;
					break;
				}
				fn += 24 * layer5[layer5_counter].note_id;
				LoadWaveFile(fn, &m_secondaryBuffer20);
				PlayWaveFile(&m_secondaryBuffer20, layer5[layer5_counter].note_volume);
				fn -= 24 * layer5[layer5_counter].note_id;
				until_next_note5 = layer5[layer5_counter].note_length;
				layer5_counter += layer5[layer5_counter].note_length;
				counter5 = 0;
				break;
			}
			default:
			{
				break;
			}
			}
		}

		//sprawdzenie, czy na którejœ warstwie jest jeszcze jakiœ dŸwiêk
		sound_playing = layer1_playing + layer2_playing + layer3_playing + layer4_playing + layer5_playing;

		//je¿eli odleg³oœæ w czasie do nastêpnej nuty na ka¿dej warstwie jest>0, program czeka przez czas pozosta³y do nastêpnego dŸwiêku
		if (until_next_note1 > 0 && until_next_note2 > 0 && until_next_note3 > 0 && until_next_note4 > 0 && until_next_note5 > 0)
		{
			if (sound_playing == 0)
			{
				until_next_note1 = 0;
			}
			until_next_note = until_next_note1;
			if (until_next_note2 < until_next_note)
			{
				until_next_note = until_next_note2;
			}
			else if (until_next_note3 < until_next_note)
			{
				until_next_note = until_next_note3;
			}
			else if (until_next_note4 < until_next_note)
			{
				until_next_note = until_next_note4;
			}
			else if (until_next_note5 < until_next_note)
			{
				until_next_note = until_next_note5;
			}

			//i zmienia pozosta³e odleg³oœci w czasie
			until_next_note1 -= until_next_note;
			until_next_note2 -= until_next_note;
			until_next_note3 -= until_next_note;
			until_next_note4 -= until_next_note;
			until_next_note5 -= until_next_note;
			Sleep(until_next_note * 116);
			until_next_note = 0;
		}

	}

	//po zakoñczeniu odtwarzania program czeka jeszcze sekundê na zanikniêcie wszystkich dŸwiêków, pog³osu itp.
	Sleep(1000);

	//i sprz¹ta po systemie odtwarzania dŸwiêku
	Shutdown();
	ShutdownDirectSound();
}

//koniec systemu odtwarzania dŸwiêku
