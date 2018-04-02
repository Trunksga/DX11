#include "TextureClass.h"
#include <D3DX11tex.h>



TextureClass::TextureClass()
{

	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass&)
{

}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* imageName)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, imageName, nullptr, nullptr, &m_texture, nullptr);

	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void TextureClass::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
