#include "RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(window_class);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(
		0,
		this->window_class_wide.c_str(), // class name
		this->window_title_wide.c_str(), // class title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, // window position
		this->width, this->height, // window size
		NULL, // handle to parent
		NULL, // handle to menu or child window
		this->hInstance, // handle to the module instance
		nullptr // param to create window
	);

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + this->window_title);
		return false;
	}

	// bring window to screen and focus
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	// handle the windows messages
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	if (PeekMessage( // PeekMessage is non-blocking
		&msg,
		this->handle,
		0, // minimum filter value
		0, // maximum filter value
		PM_REMOVE
	))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// check if window was closed
	if (msg.message == WM_NULL) // look at WM_QUIT if you just have one window
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}
	return true;
}

RenderWindow::~RenderWindow()
{
	if (hInstance != NULL)
	{
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);
}
