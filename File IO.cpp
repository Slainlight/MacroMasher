#include <sstream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <iostream>

using namespace std;

inline string getFileName()
{
	string temp = "";
	ifstream* option = new ifstream("option.txt");

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
