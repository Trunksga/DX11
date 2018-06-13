#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYCOUNT 256

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass& otherInput);
	virtual ~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	bool Initialize();
	void Shutdown();
	bool Frame();
	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);

	bool IsKeyDown(unsigned int Key);
	void KeyDown(unsigned int Key);
	void KeyUp(unsigned int Key);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	bool m_keys[KEYCOUNT];

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;
	unsigned char m_keyboardState[256] = {0};
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

