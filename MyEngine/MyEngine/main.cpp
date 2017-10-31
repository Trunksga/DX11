#pragma once

#include "SystemClass.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SystemClass * System = nullptr;
	bool result = false;

	System = new SystemClass();
	if (!System)
		return 0;
	

	result = System->Initialize();
	if (result)
		System->Run();
	
	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}