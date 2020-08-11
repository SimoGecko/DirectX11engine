#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
	{
		this->keyStates[i] = false;
	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (keyBuffer.empty())
	{
		return KeyboardEvent(); // invalid event
	}
	else
	{
		KeyboardEvent e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (charBuffer.empty())
	{
		return 0u; // NULL char
	}
	else
	{
		unsigned char c = charBuffer.front();
		charBuffer.pop();
		return c;
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	keyStates[key] = true;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	keyStates[key] = false;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return autoRepeatChars;
}
