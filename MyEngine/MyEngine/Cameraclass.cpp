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


	position = XMVectorSet(m_positionX, m_positionY, m_positionZ,0.0f);
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

XMMATRIX Cameraclass::GetCameraMatrix()
{
	XMMATRIX p =  XMMatrixTranslation(m_positionX, m_positionY, m_positionZ);
	XMMATRIX s = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMMATRIX r = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_rotationX), XMConvertToRadians(m_rotationY), XMConvertToRadians(m_rotationZ));
	return p * s *r;
}

void Cameraclass::Forward(bool forward)
{

	float pitch = XMConvertToRadians(m_rotationX);
	float yaw = XMConvertToRadians(m_rotationY);
	float roll = XMConvertToRadians(m_rotationZ);

	XMMATRIX cm = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	XMVECTOR lookAt = XMVector3TransformCoord(XMVectorSet( forward ? 1 : -1, 0, 0, 0), cm);
	lookAt *= 0.1;
	XMFLOAT3 tmp;
	XMStoreFloat3(&tmp, lookAt);

	m_positionX += tmp.x;
	m_positionY += tmp.y;
	m_positionZ += tmp.z;
}

void Cameraclass::Right(bool right)
{
	 float pitch = XMConvertToRadians(m_rotationX);
	 float yaw = XMConvertToRadians(m_rotationY);
	 float roll = XMConvertToRadians(m_rotationZ);

	XMMATRIX cm = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	XMVECTOR lookAt = XMVector3TransformCoord(XMVectorSet(0, 0,right ? 1 : -1, 0), cm);
	lookAt *= 0.1;
	XMFLOAT3 tmp;
	XMStoreFloat3(&tmp, lookAt);

	m_positionX += tmp.x;
	m_positionY += tmp.y;
	m_positionZ += tmp.z;
}
