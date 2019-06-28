#pragma once

#include <d3dx10math.h>
#include <stdlib.h>
#include <time.h>

class ModelListClass
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX, positionY, positionZ;
	};
public:
	ModelListClass();
	ModelListClass(const ModelListClass& orther);
	virtual ~ModelListClass();

	bool Initalize(int numModels);
	void Shutdown();

	int GetModelCount();
	void GetData(int index, float& positionX, float& positionY, float& positionZ, D3DXVECTOR4& color);
private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

