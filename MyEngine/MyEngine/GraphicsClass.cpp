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
	m_Bitmap = 0;
	m_Text = 0;
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
	XMMATRIX baseViewMatrix;

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
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

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
	m_light->SetDirection(0.0f, 0.0f, 1.0f);
	m_light->SetSpecularColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_light->SetSpecularPower(32.0f);

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"decal.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

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

bool GraphicsClass::Frame(int mouseX,int mouseY)
{
	bool result = false;

#if 1 

	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
#endif

	result = Render();
	if (!result)
		return false;


	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	m_D3D->BeginScene(0,0,0,1.0f);

	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->GetWorlMatrix(worldMatrix);
	m_D3D->TurnOnAlphaBlending();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
#if 1
	m_D3D->TurnZBufferOn();
	m_Model->Render(m_D3D->GetDeviceContext());
	result = m_lightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_light->GetDirection(), m_light->GetAmbientColor(), m_light->GetDiffuseColor(), m_Camera->GetPosition(), m_light->GetSpecularColor(), m_light->GetSpecularPower());

	if (!result)
	{
		return false;
	}
#endif



#if 1
	m_D3D->TurnZBufferOn();
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 0, 0);
	if (!result)
	{
		return false;
	}
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}
#endif

#if 1
	m_D3D->TurnZBufferOff();
	//m_Text->SetbaseViewMatrix(viewMatrix);
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	// Turn off alpha blending after rendering the text.
#endif

	m_D3D->EndScene();
	return true;
}
