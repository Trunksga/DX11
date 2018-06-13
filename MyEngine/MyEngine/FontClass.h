#pragma once
#include <DirectXMath.h>
#include "TextureClass.h"
#include <fstream>
#include <iosfwd>

using namespace DirectX;
using namespace std;
class FontClass
{
private:
	
	struct FontType
	{
		float left, right;
		int size;
	};
	

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
	
	void BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY, XMFLOAT2 drawSize = XMFLOAT2(100,100));

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	TextureClass* m_Texture;
};

