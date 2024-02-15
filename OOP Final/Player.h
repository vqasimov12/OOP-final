#pragma once

class Players
{
protected:
	string _username;
	string _password;

public:

	Players()
	{

	}

	Players(string username, string password)
	{
		SetUsername(username);
		SetPassword(password);
	}

	void SetUsername(string username)
	{
		if (username.size() < 3 || username.size() > 15)
			throw out_of_range("Username should contain min 3 and max 15 characters");
		this->_username = username;
	}

	void SetPassword(string password)
	{
		if (password.size() < 4 || password.size() > 10)
			throw out_of_range("Password should contain min 3 and max 10 characters");
		this->_password = password;
	}

	string GetUsername()
	{
		return _username;
	}

	string GetPassword()
	{
		return _password;
	}

};

class Player :public Players
{
	char* str1 = new char[11] {"Start Quiz" };
	char* str2 = new char[11] {"My Quizzes"};
	char* str3 = new char[5] {"Exit"};
	int size = 3;
	char** arr = new char* [size] {str1, str2, str3};

public:

	Player()
	{

	}

	Player(Players* newPlayer) :Players(newPlayer->GetUsername(), newPlayer->GetPassword())
	{

	}

	Player(string username, string password) :Players(username, password)
	{
		system("cls");
		Player_menu_control();
	}

	bool Exist(string username)
	{
		string name = "";
		string pass = "";
		string range = "";
		fstream file(playersNames, ios::in);
		if (!file.is_open())
			throw domain_error("File could not be opened");
		while (!file.eof())
		{
			getline(file, range, '#');
			if (file.eof())
				break;
			getline(file, name, '~');
			getline(file, pass, '~');
			if (username == name)
			{
				return 1;
				break;
			}
		}
		file.close();
		return 0;
	}

	bool Check(string username, string password)
	{
		string name = "";
		string pass = "";
		string range = "";
		fstream file(playersNames, ios::in);
		if (!file.is_open())
			throw domain_error("File could not be opened");
		while (!file.eof())
		{
			getline(file, range, '#');
			if (file.eof())
				break;
			getline(file, name, '~');
			getline(file, pass, '~');
			if (username == name && pass == password)
			{
				return 1;
				break;
			}
		}
		file.close();
		return 0;
	}

	void Player_menu_show(int option)
	{
		for (int i = 0; i < size; i++)
		{
			if (option == i)
				cout << red << "\t\t\t\t\t\t" << '[' << green << char(254) << red << "] " << blue << arr[i] << white << endl;
			else
				cout << "\t\t\t\t\t\t" << "[ ] " << arr[i] << endl;
		}
	}

	void Player_menu_control()
	{
		int option = 0;
		char control = 0;
		while (true)
		{
			cout << cyan << font << white;
			Player_menu_show(option);
			control = _getch();
			system("cls");
			if (control == 72 || control == 87 || control == 119)
				--option == -1 ? option = 2 : 0;
			else if (control == 80 || control == 83 || control == 115)
				++option == 3 ? option = 0 : 0;
			else if (control == 13)
				if (option == 0)
				{
					string location = Quiz_menu();
					if (location == "Null")
						continue;
					Quiz* q = new Quiz(quiz_name);
					q->read_question(location);
					q->Quiz_start(_username);
					system("pause");
					system("cls");
					delete q;
				}
				else if (option == 1)
				{
					Quiz q;
					q.My_quiz(location_players + _username + ".txt");
					system("pause");
					system("cls");
				}
				else
					break;

		}
	}

	void AddPlayer(string username, string password)
	{
		fstream file(playersNames, ios::app);
		if (!file.is_open())
			throw domain_error("File could not be opened");
		file << "Player: " << '#' << username << '~' << password << '~' << endl;
		file.close();
		fstream f(location_players + username + ".txt", ios::out);
		if (!f.is_open())
			throw domain_error("File could not be opened");
		f.close();

	}
};
