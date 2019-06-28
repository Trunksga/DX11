#include "ModelListClass.h"



ModelListClass::ModelListClass()
{
	m_ModelInfoList = 0;
}


ModelListClass::ModelListClass(const ModelListClass& orther)
{
	int i;
	float red, green, blue;
}

ModelListClass::~ModelListClass()
{
	
}

bool ModelListClass::Initalize(int numModels)
{
	int i;
	float red, green, blue;
	m_modelCount = numModels;

	m_ModelInfoList = new ModelInfoType[m_modelCount];
	if (!m_ModelInfoList)
	{
		return false;
	}

	srand((unsigned int)time(NULL));

	for ( i = 0; i < m_modelCount;i++)
	{
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		m_ModelInfoList[i].color = D3DXVECTOR4(red, green, blue, 1.0f);

		m_ModelInfoList[i].positionX = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		m_ModelInfoList[i].positionY = (((float)rand() - (float)rand()) / RAND_MAX) * 10.0f;
		m_ModelInfoList[i].positionZ = ((((float)rand() - (float)rand()) / RAND_MAX) * 10.0f) + 5.0f;
	}
	return true;
}

void ModelListClass::Shutdown()
{
	if (m_ModelInfoList)
	{
		delete[] m_ModelInfoList;
	}
	return;
}

int ModelListClass::GetModelCount()
{
	return m_modelCount;
}

void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, D3DXVECTOR4& color)
{
	if (index < 0 || index >= GetModelCount())
	{
		positionX = positionY = positionZ = 0;
		color = D3DXVECTOR4(1,1,1,1);
		return;
	}
		

	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;

	return;
}
