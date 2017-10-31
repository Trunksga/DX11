#pragma once

#define KEYCOUNT 256

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass& otherInput);
	virtual ~InputClass();

	bool Initialize();
	bool IsKeyDown(unsigned int Key);
	void KeyDown(unsigned int Key);
	void KeyUp(unsigned int Key);
private:
	bool m_keys[KEYCOUNT];
};

