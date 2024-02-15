#pragma once

void Add_string(string*& str, int& count, string name)
{
	if (name.empty())
		return;
	string* newStr = new string[count + 1];
	for (int i = 0; i < count; i++)
		newStr[i] = str[i];
	newStr[count++] = name;
	str = newStr;
}

string Select_Quiz(string location)
{
	int count = 0;
	string* str = new string[count];
	string name = "";
	string type = "";
	fstream file(location, ios::in);
	if (!file.is_open())
		throw domain_error("File could not be opened");
	while (!file.eof())
	{
		getline(file, type, ':');
		if (file.eof())
			break;
		getline(file, name, '~');
		Add_string(str, count, name);
	}

	if (!count)
		throw domain_error("No exist");

	int option = 0;
	char control = 0;
	file.close();

	while (true)
	{
		system("cls");
		cout << cyan << font << white;
		cout << green << "Select Quiz :\n " << white << endl;
		for (int i = 0; i < count; i++)
			if (i == option)
				cout << dark_red << " " << char(254) << purple << " " << str[i] << white << endl;
			else
				cout << "   " << str[i] << endl;

		cout << "\n\nPress " << "\"" << red << "esc" << white << "\" to go back" << endl;
		control = _getch();
		if (control == 72 || control == 87 || control == 119)
			--option == -1 ? option = count - 1 : 0;

		else if (control == 80 || control == 83 || control == 115)
			++option == count ? option = 0 : 0;

		else if (control == 27)
		{
			system("cls");
			return "Null";
		}

		else if (control == 13)
		{
			system("cls");
			quiz_name = str[option];
			return str[option];
		}

	}
}

string Select_type()
{
	int option = 0;
	char control = 0;

	while (true)
	{
		system("cls");
		cout << cyan << font << white;
		cout << green << "\t\t\t\t\t   Choose Quiz type:" << white << endl << endl;
		if (option == 0)
			cout << dark_red << "\t\t\t\t\t\tEasy\n" << white << "\t\t\t\t\t\tMedium\n\t\t\t\t\t\tHard\n";
		else if (option == 1)
			cout << "\t\t\t\t\t\tEasy\n" << dark_red << "\t\t\t\t\t\tMedium" << white << "\n\t\t\t\t\t\tHard\n";
		else if (option == 2)
			cout << "\t\t\t\t\t\tEasy\n" << "\t\t\t\t\t\tMedium" << dark_red << "\n\t\t\t\t\t\tHard\n" << white;
		cout << "\n Press " << "\"" << red << "esc" << white << "\" to go back" << endl;
		control = _getch();
		if (control == 72 || control == 87 || control == 119)
			--option == -1 ? option = 2 : 0;

		else if (control == 80 || control == 83 || control == 115)
			++option == 3 ? option = 0 : 0;

		else if (control == 27)
			break;

		else if (control == 13)
		{

			system("cls");
			if (option == 0)
			{
				_type = "Easy";
				return "Easy";
			}

			else if (option == 1)
			{
				_type = "Medium";
				return "Medium";
			}
			else if (option == 2)
			{
				_type = "Hard";
				return "Hard";
			}
		}
	}
	system("cls");
	return "Null";
}

string Quiz_menu()
{
	string location = "Null";
	string type = Select_type();
	try
	{
		if (type == "Null")
			return "Null";
		else if (type == "Easy")
		{
			location = location_quiz_easy;
			string loc = Select_Quiz(location_quiz_easy + "EasyQuizzes.txt");
			if (loc == "Null")
				return loc;
			location += loc + ".txt";
		}

		else if (type == "Medium")
		{
			location = location_quiz_medium;
			string loc = Select_Quiz(location_quiz_medium + "MediumQuizzes.txt");
			if (loc == "Null")
				return loc;
			location += loc + ".txt";
		}

		else if (type == "Hard")
		{
			location = location_quiz_hard;
			string loc = Select_Quiz(location_quiz_hard + "HardQuizzes.txt");
			if (loc == "Null")
				return loc;
			location += loc + ".txt";

		}
	}

	catch (domain_error e)
	{
		cout << e.what() << endl;
		system("pause");
		system("cls");
		return "Null";
	}

	catch (exception e)
	{
		cout << e.what() << endl;
		system("pause");
		system("cls");
		return "Null";
	}
	return location;
}

string* Mix_if_correct_A(string correct, list<string>wrong_aswers)
{
	string* str = new string[4];
	str[0] = correct;
	auto i = wrong_aswers.begin();
	str[1] = *i++;
	str[2] = *i++;
	str[3] = *i;
	return str;
}

string* Mix_if_correct_B(string correct, list<string>wrong_aswers)
{
	string* str = new string[4];
	auto i = wrong_aswers.begin();
	str[0] = *i++;
	str[1] = correct;
	str[2] = *i++;
	str[3] = *i;
	return str;
}

string* Mix_if_correct_C(string correct, list<string>wrong_aswers)
{
	string* str = new string[4];
	auto i = wrong_aswers.begin();
	str[0] = *i++;
	str[1] = *i++;
	str[2] = correct;
	str[3] = *i;
	return str;
}

string* Mix_if_correct_D(string correct, list<string>wrong_aswers)
{
	string* str = new string[4];
	auto i = wrong_aswers.begin();
	str[0] = *i++;
	str[1] = *i++;
	str[2] = *i;
	str[3] = correct;
	return str;
}
