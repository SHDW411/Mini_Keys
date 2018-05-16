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

private:
	bool InitializeDirectSound(HWND);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

public:
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
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;

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