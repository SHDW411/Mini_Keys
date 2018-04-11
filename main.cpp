#include <Windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "soundclass.h"
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

char filenames[8][24] = { "resources\\D6_4.wav", "resources\\G5_8.wav", "resources\\F5_2.wav", "resources\\A5_2.wav", "resources\\A#5_2.wav", "resources\\C6_2.wav", "resources\\D6_2.wav", "resources\\F6_2.wav" };
char* fn = filenames[0];
int sound_playing = 5;
int counter = 0;
SoundClass m_Sound;

struct layer
{
	unsigned int note_length;
	unsigned int note_id;
};

layer layer1[1000], layer2[1000], layer3[1000], layer4[1000], layer5[1000];
int layer1_counter = 0;
int layer2_counter = 0;
int layer3_counter = 0;
int layer4_counter = 0;
int layer5_counter = 0;
bool layer1_playing = 1;
bool layer2_playing = 1;
bool layer3_playing = 1;
bool layer4_playing = 1;
bool layer5_playing = 1;

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
	m_secondaryBuffer11= 0;
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

SoundClass::SoundClass(const SoundClass& other)
{
}

SoundClass::~SoundClass()
{
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

	// Load a wave audio file onto a secondary buffer.
//	result = LoadWaveFile(fn, &m_secondaryBuffer1);

//	if (!result)
//	{
//		return false;
//	}

	// Play the wave file now that it has been loaded.
//	result = PlayWaveFile();
//	if (!result)
//	{
//		return false;
//	}

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
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
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

bool SoundClass::PlayWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	HRESULT result;


	// Set position at the beginning of the sound buffer.
	result = (*secondaryBuffer)->SetCurrentPosition(0);

	if (FAILED(result))
	{
		return false;
	}

	// Set volume of the buffer to 100%.
	result = (*secondaryBuffer)->SetVolume(DSBVOLUME_MAX);

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


MSG info;
#define ID_PRZYCISK1 101
#define ID_PRZYCISK2 102

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_PRZYCISK1:
		{
			MessageBox(hwnd, "No nieüle", "Info", MB_ICONINFORMATION);

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
			counter = 0;
			m_Sound.Initialize(hwnd);

			while (sound_playing)
			{
				switch (counter)
				{
				case 0:
				{
					if (layer1[layer1_counter].note_length == 0)
					{
						layer1_playing = 0;
						counter += 4;
						break;
					}
					fn += 24 * layer1[layer1_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer1);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer1);
					Sleep(layer1[layer1_counter].note_length * 120);
					fn -= 24 * layer1[layer1_counter].note_id;
					layer1_counter++;
					counter++;
					break;
				}
				case 1:
				{
					if (layer1[layer1_counter].note_length == 0)
					{
						layer1_playing = 0;
						counter += 3;
						break;
					}
					fn += 24 * layer1[layer1_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer2);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer2);
					Sleep(layer1[layer1_counter].note_length * 120);
					fn -= 24 * layer1[layer1_counter].note_id;
					layer1_counter++;
					counter++;
					break;
				}
				case 2:
				{
					if (layer1[layer1_counter].note_length == 0)
					{
						layer1_playing = 0;
						counter += 2;
						break;
					}
					fn += 24 * layer1[layer1_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer3);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer3);
					Sleep(layer1[layer1_counter].note_length * 120);
					fn -= 24 * layer1[layer1_counter].note_id;
					layer1_counter++;
					counter++;
					break;
				}
				case 3:
				{
					if (layer1[layer1_counter].note_length == 0)
					{
						layer1_playing = 0;
						counter++;
						break;
					}
					fn += 24 * layer1[layer1_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer4);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer4);
					Sleep(layer1[layer1_counter].note_length * 120);
					fn -= 24 * layer1[layer1_counter].note_id;
					layer1_counter++;
					counter++;
					break;
				}
				case 4:
				{
					if (layer2[layer2_counter].note_length == 0)
					{
						layer2_playing = 0;
						counter += 4;
						break;
					}
					fn += 24 * layer2[layer2_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer5);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer5);
					Sleep(layer2[layer2_counter].note_length * 120);
					fn -= 24 * layer2[layer2_counter].note_id;
					layer2_counter++;
					counter++;
					break;
				}
				case 5:
				{
					if (layer2[layer2_counter].note_length == 0)
					{
						layer2_playing = 0;
						counter += 3;
						break;
					}
					fn += 24 * layer2[layer2_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer6);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer6);
					Sleep(layer2[layer2_counter].note_length * 120);
					fn -= 24 * layer2[layer2_counter].note_id;
					layer2_counter++;
					counter++;
					break;
				}
				case 6:
				{
					if (layer2[layer2_counter].note_length == 0)
					{
						layer2_playing = 0;
						counter += 2;
						break;
					}
					fn += 24 * layer2[layer2_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer7);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer7);
					Sleep(layer2[layer2_counter].note_length * 120);
					fn -= 24 * layer2[layer2_counter].note_id;
					layer2_counter++;
					counter++;
					break;
				}
				case 7:
				{
					if (layer2[layer2_counter].note_length == 0)
					{
						layer2_playing = 0;
						counter++;
						break;
					}
					fn += 24 * layer2[layer2_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer8);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer8);
					Sleep(layer2[layer2_counter].note_length * 120);
					fn -= 24 * layer2[layer2_counter].note_id;
					layer2_counter++;
					counter++;
					break;
				}
				case 8:
				{
					if (layer3[layer3_counter].note_length == 0)
					{
						layer3_playing = 0;
						counter += 4;
						break;
					}
					fn += 24 * layer3[layer3_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer9);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer9);
					Sleep(layer3[layer3_counter].note_length * 120);
					fn -= 24 * layer3[layer3_counter].note_id;
					layer3_counter++;
					counter++;
					break;
				}
				case 9:
				{
					if (layer3[layer3_counter].note_length == 0)
					{
						layer3_playing = 0;
						counter += 3;
						break;
					}
					fn += 24 * layer3[layer3_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer10);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer10);
					Sleep(layer3[layer3_counter].note_length * 120);
					fn -= 24 * layer3[layer3_counter].note_id;
					layer3_counter++;
					counter++;
					break;
				}
				case 10:
				{
					if (layer3[layer3_counter].note_length == 0)
					{
						layer3_playing = 0;
						counter += 2;
						break;
					}
					fn += 24 * layer3[layer3_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer11);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer11);
					Sleep(layer3[layer3_counter].note_length * 120);
					fn -= 24 * layer3[layer3_counter].note_id;
					layer3_counter++;
					counter++;
					break;
				}
				case 11:
				{
					if (layer3[layer3_counter].note_length == 0)
					{
						layer3_playing = 0;
						counter++;
						break;
					}
					fn += 24 * layer3[layer3_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer12);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer12);
					Sleep(layer3[layer3_counter].note_length * 120);
					fn -= 24 * layer3[layer3_counter].note_id;
					layer3_counter++;
					counter++;
					break;
				}
				case 12:
				{
					if (layer4[layer4_counter].note_length == 0)
					{
						layer4_playing = 0;
						counter += 4;
						break;
					}
					fn += 24 * layer4[layer4_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer13);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer13);
					Sleep(layer4[layer4_counter].note_length * 120);
					fn -= 24 * layer4[layer4_counter].note_id;
					layer4_counter++;
					counter++;
					break;
				}
				case 13:
				{
					if (layer4[layer4_counter].note_length == 0)
					{
						layer4_playing = 0;
						counter += 3;
						break;
					}
					fn += 24 * layer4[layer4_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer14);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer14);
					Sleep(layer4[layer4_counter].note_length * 120);
					fn -= 24 * layer4[layer4_counter].note_id;
					layer4_counter++;
					counter++;
					break;
				}
				case 14:
				{
					if (layer4[layer4_counter].note_length == 0)
					{
						layer4_playing = 0;
						counter += 2;
						break;
					}
					fn += 24 * layer4[layer4_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer15);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer15);
					Sleep(layer4[layer4_counter].note_length * 120);
					fn -= 24 * layer4[layer4_counter].note_id;
					layer4_counter++;
					counter++;
					break;
				}
				case 15:
				{
					if (layer4[layer4_counter].note_length == 0)
					{
						layer4_playing = 0;
						counter++;
						break;
					}
					fn += 24 * layer4[layer4_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer16);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer16);
					Sleep(layer4[layer4_counter].note_length * 120);
					fn -= 24 * layer4[layer4_counter].note_id;
					layer4_counter++;
					counter++;
					break;
				}
				case 16:
				{
					if (layer5[layer5_counter].note_length == 0)
					{
						layer5_playing = 0;
						counter = 0;
						break;
					}
					fn += 24 * layer5[layer5_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer17);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer17);
					Sleep(layer5[layer5_counter].note_length * 120);
					fn -= 24 * layer5[layer5_counter].note_id;
					layer5_counter++;
					counter++;
					break;
				}
				case 17:
				{
					if (layer5[layer5_counter].note_length == 0)
					{
						layer5_playing = 0;
						counter = 0;
						break;
					}
					fn += 24 * layer5[layer5_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer18);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer18);
					Sleep(layer5[layer5_counter].note_length * 120);
					fn -= 24 * layer5[layer5_counter].note_id;
					layer5_counter++;
					counter++;
					break;
				}
				case 18:
				{
					if (layer5[layer5_counter].note_length == 0)
					{
						layer5_playing = 0;
						counter = 0;
						break;
					}
					fn += 24 * layer5[layer5_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer19);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer19);
					Sleep(layer5[layer5_counter].note_length * 120);
					fn -= 24 * layer5[layer5_counter].note_id;
					layer5_counter++;
					counter++;
					break;
				}
				case 19:
				{
					if (layer5[layer5_counter].note_length == 0)
					{
						layer5_playing = 0;
						counter = 0;
						break;
					}
					fn += 24 * layer5[layer5_counter].note_id;
					m_Sound.LoadWaveFile(fn, &m_Sound.m_secondaryBuffer20);
					m_Sound.PlayWaveFile(&m_Sound.m_secondaryBuffer20);
					Sleep(layer5[layer5_counter].note_length * 120);
					fn -= 24 * layer5[layer5_counter].note_id;
					layer5_counter++;
					counter = 0;
					break;
				}
				default:
				{
					break;
				}
				
				}

				sound_playing = layer1_playing + layer2_playing + layer3_playing + layer4_playing + layer5_playing;
			}
			Sleep(6000);
			m_Sound.Shutdown();
			m_Sound.ShutdownDirectSound();
			break;
		}
		case ID_PRZYCISK2:
			MessageBox(hwnd, "Przykro mi", "Info2", MB_ICONINFORMATION);
			break;
		default:
			break;
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
	LPSTR NazwaKlasy = "Window Class";

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
		MessageBox(NULL, "Failed to create window class", "Error" , MB_ICONEXCLAMATION | MB_OK);
		return TRUE;
	}

	HWND hwnd, hPrzycisk1, hPrzycisk2;

	for (int i = 0; i < 1000; i++)
	{
		layer1[i].note_id = 0;
		layer1[i].note_length = 0;
		layer2[i].note_id = 0;
		layer2[i].note_length = 0;
		layer3[i].note_id = 0;
		layer3[i].note_length = 0;
		layer4[i].note_id = 0;
		layer4[i].note_length = 0;
		layer5[i].note_id = 0;
		layer5[i].note_length = 0;
	}

	//test
	layer1[0].note_id = 0;
	layer1[0].note_length = 4;
	layer1[1].note_id = 1;
	layer1[1].note_length = 8;
	layer1[2].note_id = 2;
	layer1[2].note_length = 2;
	layer1[3].note_id = 1;
	layer1[3].note_length = 8;
	layer1[4].note_id = 3;
	layer1[4].note_length = 2;
	layer1[5].note_id = 4;
	layer1[5].note_length = 2;
	layer1[6].note_id = 5;
	layer1[6].note_length = 2;
	layer1[7].note_id = 6;
	layer1[7].note_length = 2;
	layer1[8].note_id = 7;
	layer1[8].note_length = 2;

	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, NazwaKlasy, "Main window", WS_OVERLAPPEDWINDOW+WS_HSCROLL+WS_VSCROLL, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, hInstance, NULL);

	hPrzycisk1 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Pszycisk1", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 100, 150, 30, hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);
	hPrzycisk2 = CreateWindowEx(WS_EX_CLIENTEDGE, "BUTTON", "Pszycisk2", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 150, 150, 30, hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);
	HWND hText = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 5, 250, 150, 150, hwnd, NULL, hInstance, NULL);
	SetWindowText(hText, "...");
	HWND hCombo = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST, 300, 5, 150, 200, hwnd, NULL, hInstance, NULL);
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Element 1");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"Element 2");
	HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 5, 5, 100, 200, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic, "Hello!");
	HWND hStaticIcon = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_ICON, 100, 5, 48, 48, hwnd, NULL, hInstance, NULL);
	SendMessage(hStaticIcon, STM_SETICON, (WPARAM)LoadIcon(NULL, IDI_APPLICATION), 0);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Failed to create main window", "Error", MB_ICONEXCLAMATION);
		return TRUE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&info, NULL, 0, 0))
	{
		TranslateMessage(&info);
		DispatchMessage(&info);
	}
	return info.wParam;
	MessageBox(NULL, "No i fajnie", "Hehe XD", MB_ICONINFORMATION | MB_OKCANCEL);


	return 0;
}
