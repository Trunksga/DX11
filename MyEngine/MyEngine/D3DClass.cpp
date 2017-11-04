#include "D3DClass.h"



D3DClass::D3DClass()
{
	m_swapChain = 0;
	m_device = 0;
	m_deviceContext = 0;
	m_renderTargetView = 0;
	m_depthStencilBuffer = 0;
	m_depthStencilState = 0;
	m_depthStencilView = 0;
	m_rasterState = 0;
}


D3DClass::D3DClass(const D3DClass& otherObject)
{

}

D3DClass::~D3DClass()
{
}

bool D3DClass::Initialize(unsigned int screenWidth, unsigned int screenHeight, bool vsuncEnable, HWND hwnd, bool fullScreen, float screenDepth, float screenNear)
{

}

void D3DClass::Shutdown()
{

}

void D3DClass::BeginScene(float, float, float, float)
{

}

void D3DClass::EndScene()
{

}

ID3D11Device * D3DClass::GetDevice()
{

}

ID3D11DeviceContext * D3DClass::GetDeviceContext()
{

}

void D3DClass::GetProjectionMatrix(XMMATRIX& outMatrix)
{

}

void D3DClass::GetWorlMatrix(XMMATRIX&outMatrix)
{

}

void D3DClass::GetOrhiMatrix(XMMATRIX&outMatrix)
{

}

void D3DClass::GetVideoCardInfo(char* outString, int& stingLen)
{

}
