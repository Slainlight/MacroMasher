// Macro Masher.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Created by Matthew Periut in 2019

#include "Command Functionality.h"
#include "Key Organization.h"
#include "File IO.h"

enum types
{
	keyDown, keyUp,
	mousePos, click,
	loop, loopEnd,
	sleep, mouseReader,
	word, key
};

void debugCommands(string type, bool end = false);

void commander()
{
	ifstream commands(getFileName());
	string line;

	while (getline(commands, line))
	{
		istringstream data(line);

		string type;
		data >> type;
		int typeOrganized = stringToEnum(type);
		debugCommands(type);

		switch (typeOrganized)
		{
		case keyDown:
			funcKeyDown(data);
			break;
		case keyUp:
			funcKeyUp(data);
			break;
		case mousePos:
			funcMousePos(data);
			break;
		case click:
			funcClick(data);
			break;
		case loop:
			// obsolute
			// TODO: temporary file storage for infile loops
			break;
		case loopEnd:
			// obsolute
			break;
		case sleep:
			funcSleep(data);
			break;
		case mouseReader:
			funcMouseReader(data);
			break;
		case word:
			funcWord(data);
			break;
		case key:
			funcKey(data);
			break;
		default:
			cout << "improper line" << endl;
			break;
		}
	}
}

#if _DEBUG
int main()
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main(int argc, char* argv[])
#endif
{
	for (int i = 0; i < getIntFile("scripts/loops.txt"); i++)
	{
		commander();
	}
}