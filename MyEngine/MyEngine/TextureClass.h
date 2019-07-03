#pragma once
#include <D3D11.h>
#include "vector"
#include <string>
using namespace std;
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device* device, vector<wstring> imagesName);
	void Shutdown();
	
	vector<ID3D11ShaderResourceView*> GetTextureArray();

private:
	void ReleaseTextur();
	vector<ID3D11ShaderResourceView*>  m_texture;
};

