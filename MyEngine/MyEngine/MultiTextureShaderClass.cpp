#include "MultiTextureShaderClass.h"



MultiTextureShaderClass::MultiTextureShaderClass()
{
	vsFileName = psFileName = L"Multitexture.hlsl";
	vsShaderName = "MultiTextureVertexShader";
	psShaderName = "MultiTexturePixelShader";
}


MultiTextureShaderClass::MultiTextureShaderClass(const MultiTextureShaderClass& orther)
{

}

MultiTextureShaderClass::~MultiTextureShaderClass()
{
}
