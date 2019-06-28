#pragma once
#include <D3DX10math.h>



class FrustumClass
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass &orther);
	virtual ~FrustumClass();
	
	void ConstructFrustum(float, D3DXMATRIX, D3DXMATRIX);

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float xCenter, float yCenter, float zCenter, float radius);
	bool CheckRectangle(float, float, float, float, float, float);
private:
	D3DXPLANE m_planes[6];
};

