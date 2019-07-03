#include "TextureClass.h"
#include <D3DX11tex.h>



TextureClass::TextureClass()
{

}


TextureClass::TextureClass(const TextureClass&)
{

}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, vector<wstring> imageName)
{
	HRESULT result;
	int imageNameCount = imageName.size();
	ReleaseTextur();
	m_texture.resize(imageNameCount);
	for (int i = 0; i < imageNameCount;  i++)
	{
		result = D3DX11CreateShaderResourceViewFromFile(device, imageName[i].data(), nullptr, nullptr, &m_texture[i], nullptr);
		if (FAILED(result))
		{
			return false;
		}
	}

	
	return true;
}

void TextureClass::Shutdown()
{
	ReleaseTextur();
	return;
}

void TextureClass::ReleaseTextur()
{
	vector<ID3D11ShaderResourceView*>::iterator it;
	for (it = m_texture.begin(); it != m_texture.end(); it++)
	{
		if ((*it))
		{
			(*it)->Release();
			*it = NULL;
		}
	}
	m_texture.clear();
}

vector<ID3D11ShaderResourceView*> TextureClass::GetTextureArray()
{
	return m_texture;
}
