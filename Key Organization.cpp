// Created by Matthew Periut in 2019

#include "Key Organization.h"

int strToVK(string key)
{
	ifstream vk("resources/virtualKeys.txt");
	string line;

	// extract variables
	string identity;
	string hexNum;

	while (getline(vk, line))
	{
		istringstream data(line);
		stringstream ss;

		// extract data
		data >> identity >> hexNum;
		if (key == identity)
		{
			unsigned int dec;

			// convert from hex to deci
			ss << hex << hexNum;
			ss >> dec;

			return dec;
		}
	}

	return 0;
}

/*
	This is a workaround for no string switches in cpp
	There is most definitely a better way and I would look
	into it if my set of strings was much larger.
*/
int stringToEnum(string t) // t for type
{
	int i = -1; // i for identifier

	if (t == "keyDown")
	{
		i = 0;
	}
	else if (t == "keyUp")
	{
		i = 1;
	}
	else if (t == "mousePos")
	{
		i = 2;
	}
	else if (t == "click")
	{
		i = 3;
	}
	else if (t == "loop")
	{
		i = 4;
	}
	else if (t == "loopEnd")
	{
		i = 5;
	}
	else if (t == "sleep")
	{
		i = 6;
	}
	else if (t == "mouseReader")
	{
		i = 7;
	}
	else if (t == "word")
	{
		i = 8;
	}
	else if (t == "key")
	{
		i = 9;
	}

	return i;
}