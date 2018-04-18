#pragma once
#include "DirectXMath.h"
#include <D3D11.h>
#include "TextureClass.h"
#include "fstream"
using namespace std;


using namespace DirectX;
class ModelClass
{
private:
	struct VertexType 
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType 
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};


public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device* d3DDevice, char* ModelFileName, WCHAR* TextureFileName);
	void Shutdown();
	void Render(ID3D11DeviceContext* d3DDeviceContext);
	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();
private:
	bool InitializeBuffers(ID3D11Device* buffer);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* d3DDeviceContext);

	bool LoadTexture(ID3D11Device* device, WCHAR* imageName);
	void ReleaseTexture();
	
	bool LoadModel(char* ModelFileName);
	void ReleaseModel();
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;

	ModelType * m_model;
};

