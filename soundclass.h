#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_
#include <Windows.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
class SoundClass
{
private:

	//nag³ówek pliku dŸwiêkowego, potrzebny do sprawdzenia, czy plik dŸwiêkowy ma odpowiednie parametry
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();

	bool Initialize(HWND);
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void Shutdown();
	void ShutdownDirectSound();
	bool PlayWaveFile(IDirectSoundBuffer8**, long volume);
	void playback();

private:
	bool InitializeDirectSound(HWND);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

public:

	//zmienne potrzebne przy odtwarzaniu ca³ej melodii
	int counter1;
	int counter2;
	int counter3;
	int counter4;
	int counter5;
	int until_next_note;
	int until_next_note1;
	int until_next_note2;
	int until_next_note3;
	int until_next_note4;
	int until_next_note5;
	int current_layer = 1;
	int octaves = 1;

	//tabelka z nazwami plików dŸwiêkowych
	char filenames[579][24] = { "resources\\pause.wav", "resources\\B7_1.wav", "resources\\B7_2.wav", "resources\\B7_3.wav", "resources\\B7_4.wav", "resources\\B7_6.wav", "resources\\B7_8.wav", "resources\\B7_12.wav", "resources\\B7_16.wav", "resources\\A#7_1.wav", "resources\\A#7_2.wav", "resources\\A#7_3.wav", "resources\\A#7_4.wav", "resources\\A#7_6.wav", "resources\\A#7_8.wav", "resources\\A#7_12.wav", "resources\\A#7_16.wav", "resources\\A7_1.wav", "resources\\A7_2.wav", "resources\\A7_3.wav", "resources\\A7_4.wav", "resources\\A7_6.wav", "resources\\A7_8.wav", "resources\\A7_12.wav", "resources\\A7_16.wav", "resources\\G#7_1.wav", "resources\\G#7_2.wav", "resources\\G#7_3.wav", "resources\\G#7_4.wav", "resources\\G#7_6.wav", "resources\\G#7_8.wav", "resources\\G#7_12.wav", "resources\\G#7_16.wav", "resources\\G7_1.wav", "resources\\G7_2.wav", "resources\\G7_3.wav", "resources\\G7_4.wav", "resources\\G7_6.wav", "resources\\G7_8.wav", "resources\\G7_12.wav", "resources\\G7_16.wav", "resources\\F#7_1.wav", "resources\\F#7_2.wav", "resources\\F#7_3.wav", "resources\\F#7_4.wav", "resources\\F#7_6.wav", "resources\\F#7_8.wav", "resources\\F#7_12.wav", "resources\\F#7_16.wav", "resources\\F7_1.wav", "resources\\F7_2.wav", "resources\\F7_3.wav", "resources\\F7_4.wav", "resources\\F7_6.wav", "resources\\F7_8.wav", "resources\\F7_12.wav", "resources\\F7_16.wav", "resources\\E7_1.wav", "resources\\E7_2.wav", "resources\\E7_3.wav", "resources\\E7_4.wav", "resources\\E7_6.wav", "resources\\E7_8.wav", "resources\\E7_12.wav", "resources\\E7_16.wav", "resources\\D#7_1.wav", "resources\\D#7_2.wav", "resources\\D#7_3.wav", "resources\\D#7_4.wav", "resources\\D#7_6.wav", "resources\\D#7_8.wav", "resources\\D#7_12.wav", "resources\\D#7_16.wav", "resources\\D7_1.wav", "resources\\D7_2.wav", "resources\\D7_3.wav", "resources\\D7_4.wav", "resources\\D7_6.wav", "resources\\D7_8.wav", "resources\\D7_12.wav", "resources\\D7_16.wav", "resources\\C#7_1.wav", "resources\\C#7_2.wav", "resources\\C#7_3.wav", "resources\\C#7_4.wav", "resources\\C#7_6.wav", "resources\\C#7_8.wav", "resources\\C#7_12.wav", "resources\\C#7_16.wav", "resources\\C7_1.wav", "resources\\C7_2.wav", "resources\\C7_3.wav", "resources\\C7_4.wav", "resources\\C7_6.wav", "resources\\C7_8.wav", "resources\\C7_12.wav", "resources\\C7_16.wav", "resources\\B6_1.wav", "resources\\B6_2.wav", "resources\\B6_3.wav", "resources\\B6_4.wav", "resources\\B6_6.wav", "resources\\B6_8.wav", "resources\\B6_12.wav", "resources\\B6_16.wav", "resources\\A#6_1.wav", "resources\\A#6_2.wav", "resources\\A#6_3.wav", "resources\\A#6_4.wav", "resources\\A#6_6.wav", "resources\\A#6_8.wav", "resources\\A#6_12.wav", "resources\\A#6_16.wav", "resources\\A6_1.wav", "resources\\A6_2.wav", "resources\\A6_3.wav", "resources\\A6_4.wav", "resources\\A6_6.wav", "resources\\A6_8.wav", "resources\\A6_12.wav", "resources\\A6_16.wav", "resources\\G#6_1.wav", "resources\\G#6_2.wav", "resources\\G#6_3.wav", "resources\\G#6_4.wav", "resources\\G#6_6.wav", "resources\\G#6_8.wav", "resources\\G#6_12.wav", "resources\\G#6_16.wav", "resources\\G6_1.wav", "resources\\G6_2.wav", "resources\\G6_3.wav", "resources\\G6_4.wav", "resources\\G6_6.wav", "resources\\G6_8.wav", "resources\\G6_12.wav", "resources\\G6_16.wav", "resources\\F#6_1.wav", "resources\\F#6_2.wav", "resources\\F#6_3.wav", "resources\\F#6_4.wav", "resources\\F#6_6.wav", "resources\\F#6_8.wav", "resources\\F#6_12.wav", "resources\\F#6_16.wav", "resources\\F6_1.wav", "resources\\F6_2.wav", "resources\\F6_3.wav", "resources\\F6_4.wav", "resources\\F6_6.wav", "resources\\F6_8.wav", "resources\\F6_12.wav", "resources\\F6_16.wav", "resources\\E6_1.wav", "resources\\E6_2.wav", "resources\\E6_3.wav", "resources\\E6_4.wav", "resources\\E6_6.wav", "resources\\E6_8.wav", "resources\\E6_12.wav", "resources\\E6_16.wav", "resources\\D#6_1.wav", "resources\\D#6_2.wav", "resources\\D#6_3.wav", "resources\\D#6_4.wav", "resources\\D#6_6.wav", "resources\\D#6_8.wav", "resources\\D#6_12.wav", "resources\\D#6_16.wav", "resources\\D6_1.wav", "resources\\D6_2.wav", "resources\\D6_3.wav", "resources\\D6_4.wav", "resources\\D6_6.wav", "resources\\D6_8.wav", "resources\\D6_12.wav", "resources\\D6_16.wav", "resources\\C#6_1.wav", "resources\\C#6_2.wav", "resources\\C#6_3.wav", "resources\\C#6_4.wav", "resources\\C#6_6.wav", "resources\\C#6_8.wav", "resources\\C#6_12.wav", "resources\\C#6_16.wav", "resources\\C6_1.wav", "resources\\C6_2.wav", "resources\\C6_3.wav", "resources\\C6_4.wav", "resources\\C6_6.wav", "resources\\C6_8.wav", "resources\\C6_12.wav", "resources\\C6_16.wav", "resources\\B5_1.wav", "resources\\B5_2.wav", "resources\\B5_3.wav", "resources\\B5_4.wav", "resources\\B5_6.wav", "resources\\B5_8.wav", "resources\\B5_12.wav", "resources\\B5_16.wav", "resources\\A#5_1.wav", "resources\\A#5_2.wav", "resources\\A#5_3.wav", "resources\\A#5_4.wav", "resources\\A#5_6.wav", "resources\\A#5_8.wav", "resources\\A#5_12.wav", "resources\\A#5_16.wav", "resources\\A5_1.wav", "resources\\A5_2.wav", "resources\\A5_3.wav", "resources\\A5_4.wav", "resources\\A5_6.wav", "resources\\A5_8.wav", "resources\\A5_12.wav", "resources\\A5_16.wav", "resources\\G#5_1.wav", "resources\\G#5_2.wav", "resources\\G#5_3.wav", "resources\\G#5_4.wav", "resources\\G#5_6.wav", "resources\\G#5_8.wav", "resources\\G#5_12.wav", "resources\\G#5_16.wav", "resources\\G5_1.wav", "resources\\G5_2.wav", "resources\\G5_3.wav", "resources\\G5_4.wav", "resources\\G5_6.wav", "resources\\G5_8.wav", "resources\\G5_12.wav", "resources\\G5_16.wav", "resources\\F#5_1.wav", "resources\\F#5_2.wav", "resources\\F#5_3.wav", "resources\\F#5_4.wav", "resources\\F#5_6.wav", "resources\\F#5_8.wav", "resources\\F#5_12.wav", "resources\\F#5_16.wav", "resources\\F5_1.wav", "resources\\F5_2.wav", "resources\\F5_3.wav", "resources\\F5_4.wav", "resources\\F5_6.wav", "resources\\F5_8.wav", "resources\\F5_12.wav", "resources\\F5_16.wav", "resources\\E5_1.wav", "resources\\E5_2.wav", "resources\\E5_3.wav", "resources\\E5_4.wav", "resources\\E5_6.wav", "resources\\E5_8.wav", "resources\\E5_12.wav", "resources\\E5_16.wav", "resources\\D#5_1.wav", "resources\\D#5_2.wav", "resources\\D#5_3.wav", "resources\\D#5_4.wav", "resources\\D#5_6.wav", "resources\\D#5_8.wav", "resources\\D#5_12.wav", "resources\\D#5_16.wav", "resources\\D5_1.wav", "resources\\D5_2.wav", "resources\\D5_3.wav", "resources\\D5_4.wav", "resources\\D5_6.wav", "resources\\D5_8.wav", "resources\\D5_12.wav", "resources\\D5_16.wav", "resources\\C#5_1.wav", "resources\\C#5_2.wav", "resources\\C#5_3.wav", "resources\\C#5_4.wav", "resources\\C#5_6.wav", "resources\\C#5_8.wav", "resources\\C#5_12.wav", "resources\\C#5_16.wav", "resources\\C5_1.wav", "resources\\C5_2.wav", "resources\\C5_3.wav", "resources\\C5_4.wav", "resources\\C5_6.wav", "resources\\C5_8.wav", "resources\\C5_12.wav", "resources\\C5_16.wav", "resources\\B4_1.wav", "resources\\B4_2.wav", "resources\\B4_3.wav", "resources\\B4_4.wav", "resources\\B4_6.wav", "resources\\B4_8.wav", "resources\\B4_12.wav", "resources\\B4_16.wav", "resources\\A#4_1.wav", "resources\\A#4_2.wav", "resources\\A#4_3.wav", "resources\\A#4_4.wav", "resources\\A#4_6.wav", "resources\\A#4_8.wav", "resources\\A#4_12.wav", "resources\\A#4_16.wav", "resources\\A4_1.wav", "resources\\A4_2.wav", "resources\\A4_3.wav", "resources\\A4_4.wav", "resources\\A4_6.wav", "resources\\A4_8.wav", "resources\\A4_12.wav", "resources\\A4_16.wav", "resources\\G#4_1.wav", "resources\\G#4_2.wav", "resources\\G#4_3.wav", "resources\\G#4_4.wav", "resources\\G#4_6.wav", "resources\\G#4_8.wav", "resources\\G#4_12.wav", "resources\\G#4_16.wav", "resources\\G4_1.wav", "resources\\G4_2.wav", "resources\\G4_3.wav", "resources\\G4_4.wav", "resources\\G4_6.wav", "resources\\G4_8.wav", "resources\\G4_12.wav", "resources\\G4_16.wav", "resources\\F#4_1.wav", "resources\\F#4_2.wav", "resources\\F#4_3.wav", "resources\\F#4_4.wav", "resources\\F#4_6.wav", "resources\\F#4_8.wav", "resources\\F#4_12.wav", "resources\\F#4_16.wav", "resources\\F4_1.wav", "resources\\F4_2.wav", "resources\\F4_3.wav", "resources\\F4_4.wav", "resources\\F4_6.wav", "resources\\F4_8.wav", "resources\\F4_12.wav", "resources\\F4_16.wav", "resources\\E4_1.wav", "resources\\E4_2.wav", "resources\\E4_3.wav", "resources\\E4_4.wav", "resources\\E4_6.wav", "resources\\E4_8.wav", "resources\\E4_12.wav", "resources\\E4_16.wav", "resources\\D#4_1.wav", "resources\\D#4_2.wav", "resources\\D#4_3.wav", "resources\\D#4_4.wav", "resources\\D#4_6.wav", "resources\\D#4_8.wav", "resources\\D#4_12.wav", "resources\\D#4_16.wav", "resources\\D4_1.wav", "resources\\D4_2.wav", "resources\\D4_3.wav", "resources\\D4_4.wav", "resources\\D4_6.wav", "resources\\D4_8.wav", "resources\\D4_12.wav", "resources\\D4_16.wav", "resources\\C#4_1.wav", "resources\\C#4_2.wav", "resources\\C#4_3.wav", "resources\\C#4_4.wav", "resources\\C#4_6.wav", "resources\\C#4_8.wav", "resources\\C#4_12.wav", "resources\\C#4_16.wav", "resources\\C4_1.wav", "resources\\C4_2.wav", "resources\\C4_3.wav", "resources\\C4_4.wav", "resources\\C4_6.wav", "resources\\C4_8.wav", "resources\\C4_12.wav", "resources\\C4_16.wav", "resources\\B3_1.wav", "resources\\B3_2.wav", "resources\\B3_3.wav", "resources\\B3_4.wav", "resources\\B3_6.wav", "resources\\B3_8.wav", "resources\\B3_12.wav", "resources\\B3_16.wav", "resources\\A#3_1.wav", "resources\\A#3_2.wav", "resources\\A#3_3.wav", "resources\\A#3_4.wav", "resources\\A#3_6.wav", "resources\\A#3_8.wav", "resources\\A#3_12.wav", "resources\\A#3_16.wav", "resources\\A3_1.wav", "resources\\A3_2.wav", "resources\\A3_3.wav", "resources\\A3_4.wav", "resources\\A3_6.wav", "resources\\A3_8.wav", "resources\\A3_12.wav", "resources\\A3_16.wav", "resources\\G#3_1.wav", "resources\\G#3_2.wav", "resources\\G#3_3.wav", "resources\\G#3_4.wav", "resources\\G#3_6.wav", "resources\\G#3_8.wav", "resources\\G#3_12.wav", "resources\\G#3_16.wav", "resources\\G3_1.wav", "resources\\G3_2.wav", "resources\\G3_3.wav", "resources\\G3_4.wav", "resources\\G3_6.wav", "resources\\G3_8.wav", "resources\\G3_12.wav", "resources\\G3_16.wav", "resources\\F#3_1.wav", "resources\\F#3_2.wav", "resources\\F#3_3.wav", "resources\\F#3_4.wav", "resources\\F#3_6.wav", "resources\\F#3_8.wav", "resources\\F#3_12.wav", "resources\\F#3_16.wav", "resources\\F3_1.wav", "resources\\F3_2.wav", "resources\\F3_3.wav", "resources\\F3_4.wav", "resources\\F3_6.wav", "resources\\F3_8.wav", "resources\\F3_12.wav", "resources\\F3_16.wav", "resources\\E3_1.wav", "resources\\E3_2.wav", "resources\\E3_3.wav", "resources\\E3_4.wav", "resources\\E3_6.wav", "resources\\E3_8.wav", "resources\\E3_12.wav", "resources\\E3_16.wav", "resources\\D#3_1.wav", "resources\\D#3_2.wav", "resources\\D#3_3.wav", "resources\\D#3_4.wav", "resources\\D#3_6.wav", "resources\\D#3_8.wav", "resources\\D#3_12.wav", "resources\\D#3_16.wav", "resources\\D3_1.wav", "resources\\D3_2.wav", "resources\\D3_3.wav", "resources\\D3_4.wav", "resources\\D3_6.wav", "resources\\D3_8.wav", "resources\\D3_12.wav", "resources\\D3_16.wav", "resources\\C#3_1.wav", "resources\\C#3_2.wav", "resources\\C#3_3.wav", "resources\\C#3_4.wav", "resources\\C#3_6.wav", "resources\\C#3_8.wav", "resources\\C#3_12.wav", "resources\\C#3_16.wav", "resources\\C3_1.wav", "resources\\C3_2.wav", "resources\\C3_3.wav", "resources\\C3_4.wav", "resources\\C3_6.wav", "resources\\C3_8.wav", "resources\\C3_12.wav", "resources\\C3_16.wav", "resources\\B2_1.wav", "resources\\B2_2.wav", "resources\\B2_3.wav", "resources\\B2_4.wav", "resources\\B2_6.wav", "resources\\B2_8.wav", "resources\\B2_12.wav", "resources\\B2_16.wav", "resources\\A#2_1.wav", "resources\\A#2_2.wav", "resources\\A#2_3.wav", "resources\\A#2_4.wav", "resources\\A#2_6.wav", "resources\\A#2_8.wav", "resources\\A#2_12.wav", "resources\\A#2_16.wav", "resources\\A2_1.wav", "resources\\A2_2.wav", "resources\\A2_3.wav", "resources\\A2_4.wav", "resources\\A2_6.wav", "resources\\A2_8.wav", "resources\\A2_12.wav", "resources\\A2_16.wav", "resources\\G#2_1.wav", "resources\\G#2_2.wav", "resources\\G#2_3.wav", "resources\\G#2_4.wav", "resources\\G#2_6.wav", "resources\\G#2_8.wav", "resources\\G#2_12.wav", "resources\\G#2_16.wav", "resources\\G2_1.wav", "resources\\G2_2.wav", "resources\\G2_3.wav", "resources\\G2_4.wav", "resources\\G2_6.wav", "resources\\G2_8.wav", "resources\\G2_12.wav", "resources\\G2_16.wav", "resources\\F#2_1.wav", "resources\\F#2_2.wav", "resources\\F#2_3.wav", "resources\\F#2_4.wav", "resources\\F#2_6.wav", "resources\\F#2_8.wav", "resources\\F#2_12.wav", "resources\\F#2_16.wav", "resources\\F2_1.wav", "resources\\F2_2.wav", "resources\\F2_3.wav", "resources\\F2_4.wav", "resources\\F2_6.wav", "resources\\F2_8.wav", "resources\\F2_12.wav", "resources\\F2_16.wav", "resources\\E2_1.wav", "resources\\E2_2.wav", "resources\\E2_3.wav", "resources\\E2_4.wav", "resources\\E2_6.wav", "resources\\E2_8.wav", "resources\\E2_12.wav", "resources\\E2_16.wav", "resources\\D#2_1.wav", "resources\\D#2_2.wav", "resources\\D#2_3.wav", "resources\\D#2_4.wav", "resources\\D#2_6.wav", "resources\\D#2_8.wav", "resources\\D#2_12.wav", "resources\\D#2_16.wav", "resources\\D2_1.wav", "resources\\D2_2.wav", "resources\\D2_3.wav", "resources\\D2_4.wav", "resources\\D2_6.wav", "resources\\D2_8.wav", "resources\\D2_12.wav", "resources\\D2_16.wav", "resources\\C#2_1.wav", "resources\\C#2_2.wav", "resources\\C#2_3.wav", "resources\\C#2_4.wav", "resources\\C#2_6.wav", "resources\\C#2_8.wav", "resources\\C#2_12.wav", "resources\\C#2_16.wav", "resources\\C2_1.wav", "resources\\C2_2.wav", "resources\\C2_3.wav", "resources\\C2_4.wav", "resources\\C2_6.wav", "resources\\C2_8.wav", "resources\\C2_12.wav", "resources\\C2_16.wav", };
	//wskaŸnik na powy¿sz¹ tabelkê, potrzebny ¿eby przekazaæ nazwy do funkcji
	char* fn = filenames[0];
	//zmienna do sprawdzania, czy na którejœ warstwie s¹ jeszcze jakieœ dŸwiêki
	int sound_playing = 5;

	struct layer
	{
		unsigned int note_length;
		unsigned int note_id;
		long note_volume;
	};

	//5 warstw dŸwiêku z licznikami ich aktualnej pozycji w czasie
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
	int time = 0;

	void wyswietl(int layer_id, int octaves, int time, HDC* hdc, HDC* hdcNowy, HDC* hdcNowy2);

	IDirectSound8* m_DirectSound;

	//master
	IDirectSoundBuffer* m_primaryBuffer;

	//sk³adowe bufory mastera, po 4 na wartwê dŸwiêku
	IDirectSoundBuffer8* m_secondaryBuffer1;
	IDirectSoundBuffer8* m_secondaryBuffer2;
	IDirectSoundBuffer8* m_secondaryBuffer3;
	IDirectSoundBuffer8* m_secondaryBuffer4;
	IDirectSoundBuffer8* m_secondaryBuffer5;
	IDirectSoundBuffer8* m_secondaryBuffer6;
	IDirectSoundBuffer8* m_secondaryBuffer7;
	IDirectSoundBuffer8* m_secondaryBuffer8;
	IDirectSoundBuffer8* m_secondaryBuffer9;
	IDirectSoundBuffer8* m_secondaryBuffer10;
	IDirectSoundBuffer8* m_secondaryBuffer11;
	IDirectSoundBuffer8* m_secondaryBuffer12;
	IDirectSoundBuffer8* m_secondaryBuffer13;
	IDirectSoundBuffer8* m_secondaryBuffer14;
	IDirectSoundBuffer8* m_secondaryBuffer15;
	IDirectSoundBuffer8* m_secondaryBuffer16;
	IDirectSoundBuffer8* m_secondaryBuffer17;
	IDirectSoundBuffer8* m_secondaryBuffer18;
	IDirectSoundBuffer8* m_secondaryBuffer19;
	IDirectSoundBuffer8* m_secondaryBuffer20;

};

#endif