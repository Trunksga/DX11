#pragma once
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

#include "windows.h"
#include "mmsystem.h"
#include "dsound.h"
#include "stdio.h"

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
	virtual ~SoundClass();

	bool Initialize(HWND handle);
	void Shutdow();

private:
	bool InitialzeDirectSound(HWND handle);
	void ShuntdowDirectSound();

	bool LoadWaveFile(char * fileName, IDirectSoundBuffer8** buffer);
	void ShutdownWaveFile(IDirectSoundBuffer8** buffer);

	bool PlayWaveFile();

private:
	IDirectSound8 * m_DirectSound;
	IDirectSoundBuffer* m_primaryBNuffer;

	IDirectSoundBuffer8* m_secondaryBuffer1;

};

