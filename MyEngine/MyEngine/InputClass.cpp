#include "InputClass.h"



InputClass::InputClass()
{
}


InputClass::InputClass(const InputClass& otherInput)
{

}

InputClass::~InputClass()
{
}

bool InputClass::Initialize()
{
	for (int i = 0;i<KEYCOUNT;i++)
		m_keys[i] = false;
	
	return true;
}

bool InputClass::IsKeyDown(unsigned int Key)
{

	if (Key >= 0 && Key < KEYCOUNT)
	{
		return m_keys[Key];
	}
	return false;
}

void InputClass::KeyDown(unsigned int Key)
{
	if (Key >=0 && Key < KEYCOUNT)
	{
		m_keys[Key] = true;
	}
	
}

void InputClass::KeyUp(unsigned int Key)
{
	if (Key >= 0 && Key < KEYCOUNT)
	{
		m_keys[Key] = false;
	}
}
