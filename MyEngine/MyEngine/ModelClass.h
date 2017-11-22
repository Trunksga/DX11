#pragma once
#include "DirectXMath.h"
#include <D3D11.h>

using namespace DirectX;
class ModelClass
{
private:
	struct VertexType 
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device* d3DDevice);
	void Shutdown();
	void Render(ID3D11DeviceContext* d3DDeviceContext);

private:
	bool InitializeBuffers(ID3D11Device* buffer);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* d3DDeviceContext);

	int GetIndexCount();
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

};

