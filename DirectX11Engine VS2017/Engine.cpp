#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	return this->render_window.Initialize(this, hInstance, window_title, window_class, width, height);
	// initialize graphics for directX stuff
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}
