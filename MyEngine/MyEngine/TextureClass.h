#pragma once
#include <D3D11.h>
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device* device, WCHAR* imageName);
	void Shutdown();
	

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};

