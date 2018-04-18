#include "iostream"
#include "fstream"

using namespace std;


typedef struct  
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

void GetModelFilename(char*);
bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount);



bool LoadDataStructures(char*filename, int vertexCount, int textureCount, int normalCount, int faceCount);

int main()
{
	bool result;
	char filename[256];
	int vertexCount, textureCount, normalCount, faceCount;
	char garbage;

	GetModelFilename(filename);

	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	cout << endl;
	cout << "Vertices: " << vertexCount << endl;
	cout << "UVs:      " << textureCount << endl;
	cout << "Normals:  " << normalCount << endl;
	cout << "Face:     " << faceCount << endl;
	
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return -1;
	}

	cout << "\nFile has been converted." << endl;
	cout << "\nDo you wish to exit(y/n)" << endl;
	cin >> garbage;
	return 0;
}

void GetModelFilename(char* filename)
{
	bool done;
	ifstream fin;
	done = false;
	while (!done)
	{
		cin >> filename;
		fin.open(filename);
		if (fin.good())
		{
			done = true;
		}
		else
		{
			fin.clear();
			cout << "File" << filename << "could not be opened." << endl << endl;
		}
	}
	return;
}

bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;

	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	fin.open(filename);
	if (fin.fail() == true)
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; };
			if (input == 't') { textureCount++; };
			if (input == 'n') { normalCount++; };
		}

		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; };
		}

		while (input!='\n')
		{
			fin.get(input);
		}
		fin.get(input);
	}
	fin.close();
	return true;
}

bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexType *vertices, *texcoords, *normals;
}