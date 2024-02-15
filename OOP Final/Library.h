#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<algorithm>
#include<list>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include <random>    
#include <chrono>    
using namespace std;

#pragma region colors

#define red "\x1B[31m"
#define dark_red "\x1B[1;31m"
#define white "\x1B[0m"
#define green "\x1B[32m"
#define purple "\x1B[35m"
#define yellow "\x1B[33m"
#define blue "\x1B[34m"
#define cyan "\x1B[36m"
#define orange "\x1B[38;5;208m"
#pragma endregion

#pragma region font
string font = R"(
                                       ____        _            ______           ______ 
                                      / __ \__  __(_)___       / ____/________ _/ __/ /_
                                     / / / / / / / /_  /      / /   / ___/ __ `/ /_/ __/
                                    / /_/ / /_/ / / / /_     / /___/ /  / /_/ / __/ /_  
                                    \___\_\__,_/_/ /___/     \____/_/   \__,_/_/  \__/  





)";

#pragma endregion

string _type;
string quiz_name="";
string location_admin = "files\\Admin\\";
string location_players = "files\\Players\\";
string playersNames = "files\\Players\\PlayersNames.txt";
string location_quiz_hard = "files\\Quiz\\Hard\\";
string location_quiz_easy = "files\\Quiz\\Easy\\";
string location_quiz_medium = "files\\Quiz\\Medium\\";
#include"Functions.h"
#include"Question.h"
#include"Player.h"
#include"admin.h"
#include"GameMenu.h"



