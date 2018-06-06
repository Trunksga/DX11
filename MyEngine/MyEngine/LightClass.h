#pragma once
#include "DirectXMath.h"
using namespace DirectX;

class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	virtual ~LightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float R, float G, float B, float A);
	void SetDirection(float X, float Y, float Z);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();
	XMFLOAT4 GetSpecularColor();
	float GetSpecularPower();
private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
	XMFLOAT4 m_specularColor;
	float m_specularPower;
};

