#include "GraphicsClass.h"
#include <stdio.h>



GraphicsClass::GraphicsClass()
{
	m_D3D = nullptr;
}


GraphicsClass::GraphicsClass(const GraphicsClass&)
{

}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int& screenWidth, int& screenHeight, HWND & hwnd)
{
	bool result;

	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	char carNanme[128] = {0};
	int memory = 0;
	m_D3D->GetVideoCardInfo(carNanme, memory);

	HANDLE hFile = CreateFile(L"C://VedioCardInfo.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritenSize = 0;
		char writeInfo[256] = {0};
		sprintf_s(writeInfo, "VedioCardName = %s , Memory = %d", carNanme, memory);
		WriteFile(hFile, writeInfo, strlen(writeInfo), &dwWritenSize, nullptr);
		FlushFileBuffers(hFile);
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = nullptr;
	}
	return;
}

bool GraphicsClass::Frame()
{
	bool result;
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}

bool GraphicsClass::Render()
{
	m_D3D->BeginScene(1,1,0,1.0f);
	m_D3D->EndScene();
	return true;
}
