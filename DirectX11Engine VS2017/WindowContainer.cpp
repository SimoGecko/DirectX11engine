#include "WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringA("Windnow proc from window container\n");
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
