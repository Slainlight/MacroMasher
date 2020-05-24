// Created by Matthew Periut in 2019

#include "Command Functionality.h"
#include "Input Masher.hpp"

// VK = Virtual Key
int strToVK(string key);
string getString(char x);

void funcKeyDown(istringstream& data)
{
	string key;
	data >> key;
	keyInteraction(strToVK(key));
}

void funcKeyUp(istringstream& data)
{
	string key;
	data >> key;
	keyInteraction(strToVK(key), false);
}

void funcMousePos(istringstream& data)
{
	int x{ 0 }, y{ 0 };
	data >> x >> y;
	mouseMove(x, y);
}

void funcClick(istringstream& data)
{
	string side;
	data >> side;
	if (side == "left")
	{
		Click(1);
	}
	else if (side == "right")
	{
		Click(2);
	}
	else if (side == "middle")
	{
		Click(3);
	}
}

void funcSleep(istringstream& data)
{
	int milliseconds;
	data >> milliseconds;
	this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void funcMouseReader(istringstream& data)
{
	ofstream output;
	output.open("scripts/output.txt");
	int loops = 10;
	data >> loops;
	for (int i = 0; i < loops; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(500));

		int x{ sf::Mouse::getPosition().x };
		int y{ sf::Mouse::getPosition().y };
		string msg = x + ", " + y;

		cout << msg << endl;
		output << msg << endl;
	}
	output.close();
}

void funcWord(istringstream& data)
{
	string word;
	data >> word;
	for (string::iterator it = word.begin(); it != word.end(); ++it)
	{
		if (getString(*it) == " ")
		{
			keyInteraction(strToVK("VK_SPACE"));
		}
		else
		{
			keyInteraction(strToVK(getString(*it)));
			keyInteraction(strToVK(getString(*it)), false);
		}
	}
}

void funcKey(istringstream& data)
{
	string key;
	bool caps = false;
	data >> key >> caps;
	if(caps)
		keyInteraction(strToVK("VK_SHIFT"), true);
	keyInteraction(strToVK(key), true);
	keyInteraction(strToVK(key), false);
	if(caps)
		keyInteraction(strToVK("VK_SHIFT"), false);
}