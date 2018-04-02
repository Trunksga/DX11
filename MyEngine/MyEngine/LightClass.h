#pragma once
#include "DirectXMath.h"
using namespace DirectX;

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	virtual ~LightClass();

	void SetDiffuseColor(float R, float G, float B, float A);
	void SetDirection(float X, float Y, float Z);

	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();
private:
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
};

