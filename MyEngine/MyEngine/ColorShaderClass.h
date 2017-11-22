#pragma once

#include <D3D11.h>
#include "DirectXMath.h"
using namespace DirectX;

class ColorShaderClass
{
private:
	struct MatrixBufferType 
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass& other);
	~ColorShaderClass();

	bool Initialze(ID3D11Device * device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext,int indexCount,XMMATRIX &worldMatrix,XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix);

private:
	bool InitialzeShader(ID3D11Device* device,HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3DBlob* blob,HWND hwnd,WCHAR* shaderFilename);
	bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX &worldMatrix,
		XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

