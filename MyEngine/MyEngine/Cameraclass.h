#pragma once
#include "DirectXMath.h"
using namespace DirectX;

__declspec(align(16)) class Cameraclass
{
public:
	void * operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
	void operator delete(void *p)
	{
		_mm_free(p);
	}

	Cameraclass();
	Cameraclass(Cameraclass& other);
	~Cameraclass();

	void SetPosition(float x,float y,float z);
	void SetRotation(float x,float y,float z);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX& matrix);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	XMMATRIX m_viewMatrix;
};

