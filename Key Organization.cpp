#include <sstream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

int strToVK(string key)
{
	ifstream vk("resources/virtualKeys.txt");
	string line;

	while (getline(vk, line))
	{
		string leKey;
		string hexNum;
		istringstream data(line);
		data >> leKey >> hexNum;

		unsigned int regNum;
		stringstream ss;
		ss << hex << hexNum;
		ss >> regNum;

		if (key == leKey)
		{
			return regNum;
		}
	}

	return 0;
}

int stringToEnum(string t) //for type
{
	int i = -1; //for identifier

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

	return i;
}