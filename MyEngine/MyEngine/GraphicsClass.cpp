#include "GraphicsClass.h"
#include <stdio.h>
#include "DirectXMath.h"



GraphicsClass::GraphicsClass()
{
	m_D3D = nullptr;
	m_ColorShader = nullptr;
	m_Model = nullptr;
	m_Camera = 0;
	m_TextureShader = 0;
	m_TextureShader = 0;
	m_light = 0;
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

	m_Camera = new Cameraclass;
	if (!m_Camera)
	{
		return false;
	}

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	result = m_Model->Initialize(m_D3D->GetDevice(), "model.txt", L"decal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	result = m_ColorShader->Initialze(m_D3D->GetDevice(),hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not Initialize the color shader object",L"Error",MB_OK);
	}

	m_TextureShader = new TextureshaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	m_lightShader = new Lightshaderclass;
	if (!m_lightShader)
	{
		return false;
	}

	result = m_lightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_light = new LightClass;
	if (!m_light)
	{
		return false;
	}

	m_light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->SetDiffuseColor(1.0, 1.0, 1.0, 1.0);
	m_light->SetDirection(1.0f, 0.0f, 0.0f);


	return true;
}

void GraphicsClass::Shutdown()
{

	// Release the light object.
	if (m_light)
	{
		delete m_light;
		m_light = 0;
	}

	// Release the light shader object.
	if (m_lightShader)
	{
		m_lightShader->Shutdown();
		delete m_lightShader;
		m_lightShader = 0;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	char carNanme[128] = {0};
	int memory = 0;
	m_D3D->GetVideoCardInfo(carNanme, memory);

	HANDLE hFile = CreateFile(L"C://VedioCardInfo.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwWritenSize = 0;
		char writeInfo[256] = {0};
		sprintf_s(writeInfo, "VedioCardName = %s , Memory = %d", carNanme, memory);
		WriteFile(hFile, writeInfo, (DWORD)strlen(writeInfo), &dwWritenSize, nullptr);
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
	static float rotation = 0.0f;

	rotation += (float)XM_PI*0.005f;
	bool result;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	result = Render(rotation);
	if (!result)
	{
		return false;
	}
	return true;
}

bool GraphicsClass::Render(float delta)
{
	XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;
	m_D3D->BeginScene(0,0,0,1.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetWorlMatrix(worldMatrix);

	worldMatrix *= XMMatrixRotationY(delta);


	m_Model->Render(m_D3D->GetDeviceContext());
// 	result = m_ColorShader->Render(m_D3D->GetDeviceContext(),m_Model->GetIndexCount(),worldMatrix,viewMatrix,projectionMatrix);
// 	if (!result)
// 	{
// 		return false;
// 	}
	//m_light->SetDirection(1.0, 1.0, delta / 360.f);
	result = m_lightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_light->GetDirection(), m_light->GetAmbientColor(),m_light->GetDiffuseColor());

	if (!result)
	{
		return false;
	}


	m_D3D->EndScene();
	return true;
}
