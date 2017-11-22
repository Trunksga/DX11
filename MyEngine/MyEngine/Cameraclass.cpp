#include "Cameraclass.h"
#include <DirectXMathConvert.inl>





Cameraclass::Cameraclass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

Cameraclass::Cameraclass(Cameraclass& other)
{

}

Cameraclass::~Cameraclass()
{

}


void Cameraclass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

void Cameraclass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}

XMFLOAT3 Cameraclass::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 Cameraclass::GetRotation()
{
	return XMFLOAT3(m_rotationX,m_rotationY,m_rotationZ);
}

void Cameraclass::Render()
{
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	position = XMVectorSet(m_positionX, m_positionY, m_positionZ,1.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	pitch = XMConvertToRadians(m_rotationX);
	yaw = XMConvertToRadians(m_rotationY);
	roll = XMConvertToRadians(m_rotationZ);

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	lookAt += position;

	m_viewMatrix =  XMMatrixLookAtLH(position, lookAt, up);

}

void Cameraclass::GetViewMatrix(XMMATRIX& matrix)
{
	matrix = m_viewMatrix;
}
