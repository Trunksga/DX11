#pragma once

#include <windows.h>
#include "D3DClass.h"

const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	virtual ~GraphicsClass();

	bool Initialize(int& screenWidth,int& screenHeight, HWND & m_hwnd);
	void Shutdown();
	bool Frame();
private:
	bool Render();
private:
	D3DClass *m_D3D = nullptr;
};

