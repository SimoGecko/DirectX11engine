#include "WindowContainer.h"

LRESULT WindowContainer::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//OutputDebugStringA("Windnow proc from window container\n");
	//
	unsigned char keycode = static_cast<unsigned char>(wParam);
	unsigned char ch = static_cast<unsigned char>(wParam);
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	switch (uMsg)
	{
	// Keyboard messages
	case WM_KEYDOWN:
	{
		if (keyboard.IsKeysAutoRepeat())
		{
			keyboard.OnKeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & (1 << 30);
			if (!wasPressed)
			{
				keyboard.OnKeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_KEYUP:
	{
		keyboard.OnKeyReleased(keycode);
		return 0;
	}
	case WM_CHAR:
	{
		if (keyboard.IsCharsAutoRepeat())
		{
			keyboard.OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & (1 << 30);
			if (!wasPressed)
			{
				keyboard.OnChar(ch);
			}
		}
		return 0;
	}
	// Mouse messages
	case WM_MOUSEMOVE:
	{
		mouse.OnMouseMove(x, y);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		mouse.OnLeftPressed(x, y);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		mouse.OnRightPressed(x, y);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		mouse.OnMiddlePressed(x, y);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		mouse.OnLeftReleased(x, y);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		mouse.OnRightReleased(x, y);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		mouse.OnMiddleReleased(x, y);
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (delta > 0)
		{
			mouse.OnWheelUp(x, y);
		}
		else if(delta < 0)
		{
			mouse.OnWheelDown(x, y);
		}
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
