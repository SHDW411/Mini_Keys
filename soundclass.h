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

	//tabelka z nazwami plików dŸwiêkowych
	char filenames[22][24] = { "resources\\G#5_2.wav", "resources\\C6_2.wav", "resources\\C#6_2.wav", "resources\\F#5_2.wav", "resources\\D#5_4.wav", "resources\\A#5_2.wav", "resources\\B5_2.wav", "resources\\G#5_4.wav", "resources\\G#2_8.wav", "resources\\E2_8.wav", "resources\\F#2_8.wav", "resources\\G#3_2.wav", "resources\\D#4_2.wav", "resources\\G#4_2.wav", "resources\\B4_2.wav", "resources\\E3_2.wav", "resources\\B3_2.wav", "resources\\E4_2.wav", "resources\\F#3_2.wav", "resources\\C#4_2.wav", "resources\\F#4_2.wav", "resources\\A#4_2.wav" };
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