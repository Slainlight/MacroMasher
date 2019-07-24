// Created by Matthew Periut in 2019

#include <Windows.h>
#include <thread>

void keyInteraction(int key, bool press = true)
{
	INPUT ip;
	//static bool init = false;

	//if (!init)
	{
		// Set up a generic keyboard event.
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0; // hardware scan code for key
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
		//init = true;
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

// TODO: Remove SFML Dependency

void setMousePosition(int x, int y)
{
	POINT mp;
	mp.x = x;
	mp.y = y;

	long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

	float fx = mp.x * (65535.0f / fScreenWidth);
	float fy = mp.y * (65535.0f / fScreenHeight);

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;

	SendInput(1, &Input, sizeof(INPUT));
}