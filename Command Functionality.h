#pragma once

// Created by Matthew Periut in 2019

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Window.hpp>

using namespace std;

void funcKeyDown(istringstream& data);
void funcKeyUp(istringstream& data);
void funcMousePos(istringstream& data);
void funcClick(istringstream& data);
void funcSleep(istringstream& data);
void funcMouseReader(istringstream& data);
void funcWord(istringstream& data);
void funcKey(istringstream& data);