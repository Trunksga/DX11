#include "LightClass.h"



LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass&)
{
	
}

LightClass::~LightClass()
{

}


void LightClass::SetAmbientColor(float R, float G, float B, float A)
{
	m_ambientColor = XMFLOAT4(R, G, B, A);
}

void LightClass::SetDiffuseColor(float R, float G, float B, float A)
{
	m_diffuseColor = XMFLOAT4(R, G, B, A);
}

void LightClass::SetDirection(float X, float Y, float Z)
{
	m_direction = XMFLOAT3(X, Y, Z);
}

DirectX::XMFLOAT4 LightClass::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 LightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT3 LightClass::GetDirection()
{
	return m_direction;
}
