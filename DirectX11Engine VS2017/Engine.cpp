#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height)
{
	//keyboard.EnableAutoRepeatChars();
	if (! render_window.Initialize(this, hInstance, window_title, window_class, width, height))
	{
		return false;
	}
	if (!gfx.Initialize(render_window.GetHWND(), width, height))
	{
		return false;
	}
	// initialize graphics for directX stuff
}

bool Engine::ProcessMessages()
{
	return this->render_window.ProcessMessages();
}

void Engine::Update()
{
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
		{
			//std::string outmsg = "Char: ";
			//outmsg += ch;
			//outmsg += "\n";
			//OutputDebugStringA(outmsg.c_str());
		}
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		{
			//std::string outmsg = "";
			//if (kbe.IsPress())
			//{
			//	outmsg += "Keycode (PRESS): ";
			//}
			//else
			//{
			//	outmsg += "Keycode (RELEASE): ";
			//}
			//outmsg += keycode;
			//outmsg += "\n";
			//OutputDebugStringA(outmsg.c_str());
		}
	}
	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		{
			//char c[64];
			//sprintf_s(c, "X: %d, Y: %d\n", me.GetPosX(), me.GetPosY());
			//OutputDebugStringA(c);
		}
		{
			if (me.GetType() == MouseEvent::EventType::WheelUp)
			{
				OutputDebugStringA("MouseWheelUp\n");
			}
			if (me.GetType() == MouseEvent::EventType::WheeelDown)
			{
				OutputDebugStringA("MouseWheelDown\n");
			}
		}
		{
			if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
			{
				char c[64];
				sprintf_s(c, "X: %d, Y: %d\n", me.GetPosX(), me.GetPosY());
				OutputDebugStringA(c);
			}
		}
	}
}

void Engine::RenderFrame()
{
	gfx.RenderFrame();
}
