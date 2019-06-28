#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "InputClass.h"
#include "GraphicsClass.h"
#include "SoundClass.h"
#include "fpsclass.h"
#include "cpuclass.h"
#include "timerclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass & otherSystem);
	virtual ~SystemClass();

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND,UINT,WPARAM,LPARAM);
private:

	bool Frame();
	void InitializeWindows(int&,int&);
	void ShutdownWindows();

	
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	SoundClass* m_Sound;

	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;
};

static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
static SystemClass * ApplicationHandle = nullptr;

