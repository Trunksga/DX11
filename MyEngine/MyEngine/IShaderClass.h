#pragma once

#include <D3D11.h>
#include "DirectXMath.h"
using namespace DirectX;

class IShaderClass
{
protected:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	IShaderClass();
	~IShaderClass();

	virtual bool Initialze(ID3D11Device * device, HWND hwnd) { return true; };
	virtual void Shutdown() {};
	virtual bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX &worldMatrix, XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix) { return true;};


private:
	virtual bool InitialzeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename) { return true; };
	virtual void ShutdownShader() {};
	virtual void OutputShaderErrorMessage(ID3DBlob* blob, HWND hwnd, WCHAR* shaderFilename) {};
	virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX &worldMatrix,
		XMMATRIX &viewMatrix, XMMATRIX &projectionMatrix) {
		return true;
	};
	virtual void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount) {};
};

