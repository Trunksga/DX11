#pragma once
#include <d3d11.h>
#include "DirectXMath.h"

using namespace DirectX;

__declspec(align(16)) class D3DClass
{
public:
	void * operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
	void operator delete(void *p)
	{
		_mm_free(p);
	}


	D3DClass();
	D3DClass(const D3DClass& otherObject);
	~D3DClass();

	bool Initialize(unsigned int screenWidth,unsigned int screenHeight,bool vsuncEnable ,HWND hwnd,bool fullScreen,float screenDepth,float screenNear);
	void Shutdown();
	void BeginScene(float ,float ,float ,float );
	void EndScene();

	ID3D11Device * GetDevice();
	ID3D11DeviceContext *GetDeviceContext();

	void GetProjectionMatrix(XMMATRIX& outMatrix);
	void GetWorlMatrix(XMMATRIX&outMatrix);
	void GetOrthoMatrix(XMMATRIX&outMatrix);

	void GetVideoCardInfo(char* outString,int& memory);


	void TurnZBufferOn();
	void TurnZBufferOff();
private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState *m_depthStencilState;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RasterizerState*m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;

	ID3D11DepthStencilState * m_depthDisabledStencilState;
};

