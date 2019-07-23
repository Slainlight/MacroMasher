// Macro Masher.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

void keyInteraction(int key, bool press = true);
void mouseMove(int x, int y);
void Click(int button);
int stringToEnum(string t);
int strToVK(string key);
string getString(char x);
inline string getFileName();

enum types
{
	keyDown, keyUp,
	mousePos, click,
	loop, loopEnd,
	sleep, mouseReader,
	word
};



int commander()
{
	static bool copy = false;
	static ifstream commands(getFileName());

	string line;
	int lineNum;
	static ofstream debug;
	debug.open("lineAnalysis.txt");
	while (getline(commands, line))
	{
		istringstream data(line);

		string type;
		data >> type;

		int typeOrganized = stringToEnum(type);
		debug << typeOrganized << " " << type;
		if (typeOrganized == -1)
		{
			debug << " ERROR ON LINE";
		}
		debug << "\n";
		

		int milliseconds;
		string key;
		string side;
		string msg;
		ofstream myfile;
		int x{ 0 }, y{ 0 };

		switch (typeOrganized)
		{
		case keyDown:
			data >> key;
			keyInteraction(strToVK(key));
			break;
		case keyUp:
			data >> key;
			keyInteraction(strToVK(key), false);
			break;
		case mousePos:
			data >> x >> y;
			mouseMove(x, y);
			break;
		case click:
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

			break;
		case loop:
			copy = true;
			break;
		case loopEnd:
			copy = false;
			break;
		case mouseReader:
			myfile.open("output.txt");
			while (true)
			{
				this_thread::sleep_for(chrono::milliseconds(500));
				cout << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << endl;
				myfile << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
			}
			myfile.close();
			break;
		case sleep:
			data >> milliseconds;
			this_thread::sleep_for(chrono::milliseconds(milliseconds));
			break;
		case word:
			data >> msg;
			for (string::iterator it = msg.begin(); it != msg.end(); ++it)
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

			break;
		default:
			break;
		}

		// process pair (a,b)
	}
	debug.close();
}


#if _DEBUG
int main()
#else
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd)
#endif // _DEBUG
{
	int loops = 1;
	string temp;
	ifstream* option = new ifstream("loops.txt");

	while (getline(*option, temp))
	{
		istringstream iss(temp);
		iss >> loops;
	}

	for (int i = 0; i < loops; i++)
	{
		commander();
	}
	

#if _DEBUG
	system("pause");
#endif // _DEBUG
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
