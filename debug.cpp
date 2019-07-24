// Created by Matthew Periut in 2019

#include <iostream>
#include <fstream>

using namespace std;

int stringToEnum(string t);

void debugCommands(string type, bool end = false)
{
	static bool init = false;
	static ofstream debug;
	if (!init)
	{
		debug.open("scripts/lineAnalysis.txt");
		init = true;
	}

	if (!end)
	{
		int typeOrganized = stringToEnum(type);

		debug << typeOrganized << " " << type;
		if (typeOrganized == -1)
		{
			debug << " ERROR ON LINE";
		}
		debug << endl;
	}
	else
	{
		debug.close();
	}
}