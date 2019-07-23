#include <Windows.h>
#include <SFML/Window.hpp>
#include <thread>

void mouseMove(int x, int y)
{
	sf::Mouse::setPosition(sf::Vector2i(x, y));
}

void keyInteraction(int key, bool press = true)
{
	static INPUT ip;
	static bool init = false;

	if (!init)
	{
		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		init = true;
	}

	ip.ki.wVk = key; // virtual-key code
	
	if (press)
	{
		//press
		ip.ki.dwFlags = 0;
		SendInput(1, &ip, sizeof(INPUT));
	}
	else
	{
		//release
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}
}

void Click(int button)
{
	INPUT Input = { 1 };													// Create our input.

	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	switch (button)
	{
	case 1:
		Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		break;
	case 2:
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		break;
	case 3:
		Input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		break;
	}
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.

	ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	switch (button)
	{
	case 1:
		Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		break;
	case 2:
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		break;
	case 3:
		Input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		break;
	}
	SendInput(1, &Input, sizeof(INPUT));
}

POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

void SetMousePosition(POINT& mp)
{
	long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx = mp.x * (65535.0f / fScreenWidth);
	float fy = mp.y * (65535.0f / fScreenHeight);

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;

	SendInput(1, &Input, sizeof(INPUT));
}