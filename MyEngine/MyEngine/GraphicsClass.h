#pragma once

#include <windows.h>
#include "D3DClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include "Cameraclass.h"
#include "textureshaderclass.h"
#include "Lightshaderclass.h"
#include "LightClass.h"
#include "BitmapClass.h"
#include "Textclass.h"
#include "modellistclass.h"
#include "frustumclass.h"
#include "MultiTextureShaderClass.h"

const bool FULL_SCREEN = false;
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
	bool SetMousePosition(int mouseX,int mouseY);
	bool Frame(int fps, int cpu, float frameTime);
	
	Cameraclass* m_Camera;
private:
	bool Render();
private:
	D3DClass *m_D3D = nullptr;
	
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

	TextureshaderClass* m_TextureShader;

	Lightshaderclass * m_lightShader;
	LightClass * m_light;

	BitmapClass* m_Bitmap;

	TextClass* m_Text;

	ModelListClass * m_ModelList;
	FrustumClass* m_Frustum;
};

