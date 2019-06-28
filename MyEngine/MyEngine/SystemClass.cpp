#include "SystemClass.h"
#include <dinput.h>



SystemClass::SystemClass()
{
	m_Input = nullptr;
	m_Graphics = nullptr;
	m_Sound = 0;

	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
}




SystemClass::SystemClass(const SystemClass & otherSystem)
{

}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth = 0 , screenHeight = 0;
	bool result = false;

	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass;
	if (!m_Input)
		return false;
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
		return false;
	

	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
		return false;
	result =  m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result)
		return false;
	
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	result = m_Sound->Initialize(m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
		return false;
	}

	//Create and initialize the FpsClass.

		// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();
	//Create and initialize the CpuClass.

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}

	// Initialize the cpu object.
	m_Cpu->Initialize();
	//Create and initialize the TimerClass.

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}


	return true;
}

void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));
	done = false;
	while (!done)
	{
		if (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if (!result)
			{
				MessageBox(m_hwnd, L"Frame Processing Failed", L"Error", MB_OK);
				done = true;
			}
		}

		if (m_Input->IsEscapePressed() == true)
		{
			done = true;
		}
	}
}

void SystemClass::Shutdown()
{
	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	if (m_Sound)
	{
		m_Sound->Shutdow();
		delete m_Sound;
		m_Sound = 0;
	}

	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = nullptr;
	}

	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = nullptr;
	}
	ShutdownWindows();
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

bool SystemClass::Frame()
{
	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	bool result = false;
	int mouseX, mouseY;
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	if (m_Input->IsKeyDown(DIK_W))
	{
		m_Graphics->m_Camera->Forward(true);
	}
	if (m_Input->IsKeyDown(DIK_S))
	{
		m_Graphics->m_Camera->Forward(false);
	}
	if (m_Input->IsKeyDown(DIK_D))
	{
		m_Graphics->m_Camera->Right(true);
	}
	if (m_Input->IsKeyDown(DIK_A))
	{
		m_Graphics->m_Camera->Right(false);
	}
	if (m_Input->IsKeyDown(DIK_Q))
	{
		m_Graphics->m_Camera->Up(false);
	}
	if (m_Input->IsKeyDown(DIK_E))
	{
		m_Graphics->m_Camera->Up(true);
	}
	if (m_Input->IsKeyDown(DIK_RIGHT))
	{
		m_Graphics->m_Camera->Yaw(true);
	}
	if (m_Input->IsKeyDown(DIK_LEFT))
	{
		m_Graphics->m_Camera->Yaw(false);
	}
	if (m_Input->IsKeyDown(DIK_UP))
	{
		m_Graphics->m_Camera->Pitch(true);
	}
	if (m_Input->IsKeyDown(DIK_DOWN))
	{
		m_Graphics->m_Camera->Pitch(false);
	}
	m_Input->GetMouseLocation(mouseX, mouseY);
	m_Graphics->SetMousePosition(mouseX, mouseY);
	result = m_Graphics->Frame(m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime());
	//result = m_Graphics->Frame(m_Timer->GetTime(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime());
	if (!result)
		return false;

	return true;

}

void SystemClass::InitializeWindows(int&screenWidth, int&screenHeight)
{
	WNDCLASSEX wc = {0};
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(nullptr);
	m_applicationName = L"Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	//wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIcon = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned int)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned int)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		screenWidth = 1024;
		screenHeight = 768;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN| WS_POPUP, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hinstance, nullptr);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	ShowCursor(false);
	return;
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(false);

	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	DestroyWindow(m_hwnd);

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = nullptr;
	ApplicationHandle = nullptr;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}