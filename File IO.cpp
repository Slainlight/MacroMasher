// Created by Matthew Periut in 2019

#include "File IO.h"
#include "Key Organization.h"

int getIntFile(string file)
{
	string temp;
	int returnable = 0;
	ifstream* option = new ifstream(file);

	while (getline(*option, temp))
	{
		istringstream iss(temp);
		iss >> returnable;
	}
	return returnable;
}

string getFileName()
{
	string temp = "";
	ifstream* option = new ifstream("scripts/option.txt");

	while (getline(*option, temp))
	{
		istringstream iss(temp);
		iss >> temp;
	}

	if (temp == "")
	{
		cout << "error" << endl;
		MessageBox(NULL, L"No File Chosen.", NULL, MB_OK);
	}

#if _DEBUG
	cout << temp << endl;
#endif

	delete option;
	return temp;
}
