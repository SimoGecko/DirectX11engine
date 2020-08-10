#pragma once
#include "RenderWindow.h"

class WindowContainer
{
public:
	// mouse
	// keyboard
	// windowProc (for messages)
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	RenderWindow render_window;

private:

};