#pragma once
void logKeyPress();
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
void processKeyStroke(PKBDLLHOOKSTRUCT virtualKeyCode);