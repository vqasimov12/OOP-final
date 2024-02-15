#pragma once

class Admin :public Players
{

	char* str1 = new char[11] {"Start Quiz" };
	char* str2 = new char[12] {"Create Quiz"};
	char* str3 = new char[12] {"All players"};
	char* str4 = new char[12] {"All quizzes"};
	char* str5 = new char[11] {"My quizzes"};
	char* str6 = new char[5] {"Exit"};
	int size = 6;
	char** arr = new char* [size] {str1, str2, str3, str4, str5, str6};
public:

	Admin() :Players("admin", "admin123")
	{
		Admin_menu_control();
	}

	void All_Players()
	{
		string name = "";
		string pass = "";
		string range = "";
		fstream file(playersNames, ios::in);
		if (!file.is_open())
			throw domain_error("File could not be opened");
		int i = 1;
		cout << cyan << font << white;
		while (!file.eof())
		{
			getline(file, range, '#');
			if (file.eof())
				break;
			getline(file, name, '~');
			getline(file, pass, '~');
			cout << " " << green << i++ << (i < 10 ? ". " : ".") << white;
			cout << " Username: " << dark_red << name << white;
			for (int f = 0; f < 15 - name.size(); f++)
				cout << " ";
			cout << "Password: " << yellow << pass[0];
			for (int j = 0; j < pass.size() - 2; j++)
				cout << '*';
			cout << pass[pass.size() - 1] << white << endl;
		}
		cout << endl;
		system("pause");
		system("cls");
		file.close();
	}

	void Admin_menu_show(int option)
	{
		for (int i = 0; i < size; i++)
		{
			if (option == i)
				cout << cyan << "\t\t\t\t\t\t" << '[' << red << char(254) << cyan << "] " << green << arr[i] << white << endl;
			else
				cout << "\t\t\t\t\t\t" << "[ ] " << arr[i] << endl;
		}
	}

	void Admin_menu_control()
	{
		int option = 0;
		char control = 0;
		while (true)
		{
			cout << cyan << font << white;
			Admin_menu_show(option);
			control = _getch();
			system("cls");

			if (control == 72 || control == 87 || control == 119)
				--option == -1 ? option = 5 : 0;

			else if (control == 80 || control == 83 || control == 115)
				++option == 6 ? option = 0 : 0;

			else if (control == 13)

				if (option == 0)
				{
					try
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
					catch (exception e)
					{
						cout << e.what() << endl << endl;
						system("pause");
						system("cls");
					}
					catch (domain_error e)
					{
						cout << e.what() << endl << endl;
						system("pause");
						system("cls");
					}
					catch (...)
					{
						cout << "Something went wrong try again" << endl << endl;
						system("pause");
						system("cls");
					}
				}

				else if (option == 1)
				{
					Add_Quiz();
				}

				else if (option == 2)
				{
					try
					{
						All_Players();
					}
					catch (domain_error e)
					{
						cout << e.what() << endl << endl;
						system("pause");
						system("cls");
					}
				}

				else if (option == 3)
				{
					try
					{
						All_Quizs();
					}
					catch (domain_error e)
					{
						cout << e.what() << endl << endl;
						system("pause");
						system("cls");
					}
				}

				else if (option == 4)
				{
					Quiz q;
					try
					{
						q.My_quiz(location_admin + "admin.txt");
					}
					catch (domain_error e)
					{
						cout << e.what() << endl << endl;
					}
					system("pause");
					system("cls");
				}

				else
				{
					break;
				}
		}
	}

	void All_Quizs()
	{
		string type = "";
		string name = "";
		int i = 1;
		cout << cyan << font << white;
		fstream file(location_quiz_easy + "EasyQuizzes.txt", ios::in);
		if (!file.is_open())
			throw domain_error("File could not be opened");
		cout << purple << "Easy Quizzes: " << white << endl << endl;
		while (!file.eof())
		{
			getline(file, type, ':');
			if (file.eof())
				break;
			getline(file, name, '~');
			cout << i++ << (i < 10 ? ".  " : ". ") << green << name << white << endl;
		}
		file.close();
		cout << red << (i == 1 ? "Not any quiz available" : "") << white << endl;

		i = 1;
		fstream f(location_quiz_medium + "MediumQuizzes.txt", ios::in);
		if (!f.is_open())
			throw domain_error("File could not be opened");
		cout << purple << "\n\nMedium Quizzes: " << white << endl << endl;
		while (!f.eof())
		{
			getline(f, type, ':');
			if (f.eof())
				break;
			getline(f, name, '~');
			cout << i++ << (i < 10 ? ".  " : ". ") << orange << name << white << endl;
		}
		f.close();
		cout << red << (i == 1 ? "Not any quiz available" : "") << white << endl;

		i = 1;
		fstream fl(location_quiz_hard + "HardQuizzes.txt", ios::in);
		if (!fl.is_open())
			throw domain_error("File could not be opened");
		cout << purple << "\n\nHard Quizzzes: " << white << endl << endl;
		while (!fl.eof())
		{
			getline(fl, type, ':');
			if (fl.eof())
				break;
			getline(fl, name, '~');
			cout << i++ << (i < 10 ? ".  " : ". ") << dark_red << name << white << endl;
		}
		fl.close();
		cout << red << (i == 1 ? "Not any quiz available" : "") << white << endl;

		cout << endl;
		system("pause");
		system("cls");
	}

	void Add_Quiz()
	{
		int option = 0;
		char control = 0;
		string quiz_type = "";
		string quiz_name = "";

		system("cls");
		quiz_type = Select_type();
		if (quiz_type == "Null")return;

		system("cls");
		Quiz q;

		while (true)
		{
			cout << "Enter quiz name: ";
			getline(cin, quiz_name);
			try
			{
				if (!q.Exist(quiz_name))
					break;
			}
			catch (domain_error e)
			{
				cout << e.what() << endl << endl;
				system("pause");
				system("cls");
				continue;
			}
			cout << "This name has already been used\nEnter new name:" << endl;
		}

		string question = "";
		string correct = "";
		string wrong = "";
		int point = 0;

		try
		{
			int count = 0;
			q.SetName(quiz_name);
			for (int i = 0; ; i++)
			{
				system("cls");
				list<string>wrong_answers;
				cout << "Enter question " << i + 1 << ": " << endl;
				getline(cin, question);
				cout << "Enter correct answer: ";
				getline(cin, correct);
				for (int j = 0; j < 3; j++)
				{
					cout << "Enter wrong answer " << j + 1 << " : ";
					getline(cin, wrong);
					wrong_answers.push_back(wrong);
				}
				cout << "Enter point: ";
				cin >> point;
				cin.ignore();
				try
				{
					q.Add_question(new Question(question, correct, wrong_answers, point));
					count++;
				}

				catch (exception e)
				{
					cout << e.what() << endl;
					system("pause");
					i--;
				}
				int num = 1;
				char cont;
				bool if_break = 0;
				if (count)
					while (true)
					{
						system("cls");
						cout << cyan << font << white << endl;
						if (num == 1)
							cout << red << "  " << "\t\t\t\t\t\t\tNew Question\n" << white << "\t\t\t\t\t\t\tSave and Exit\n\t\t\t\t\t\t\tExit" << endl;
						else if (num == 2)
							cout << "  " << "\t\t\t\t\t\t\tNew Question\n" << red << "\t\t\t\t\t\t\tSave and Exit\n" << white << "\t\t\t\t\t\t\tExit" << endl;
						else
							cout << "  " << "\t\t\t\t\t\t\tNew Question\n" << "\t\t\t\t\t\t\tSave and Exit\n" << red << "\t\t\t\t\t\t\tExit" << white << endl;
						cont = _getch();
						if (cont == 72 || cont == 87 || cont == 119)
							--num == -1 ? num = 2 : 0;

						else if (cont == 80 || cont == 83 || cont == 115)
							++num == 3 ? num = 0 : 0;

						else if (cont == 13)
							if (num == 1)
								break;
							else if (num == 2)
							{
								if_break = 1;
								break;
							}
							else
							{
								system("cls");
								return;
							}

					}
				if (if_break)break;
			}
			try
			{
				if (quiz_type == "Easy")
				{
					q.save_questions(location_quiz_easy + quiz_name + ".txt");
					fstream f(location_quiz_easy + quiz_name + "Scores.txt");
					f.close();
				}
				else if (quiz_type == "Medium")
				{
					q.save_questions(location_quiz_medium + quiz_name + ".txt");
					fstream f(location_quiz_medium + quiz_name + "Scores.txt");
					f.close();
				}
				else if (quiz_type == "Hard")
				{
					q.save_questions(location_quiz_hard + quiz_name + ".txt");
					fstream f(location_quiz_hard + quiz_name + "Scores.txt");
					f.close();
				}

			}
			catch (domain_error e)
			{
				cout << e.what() << endl;
			}
			catch (...)
			{
				cout << "File could not be opened" << endl;
			}

		}

		catch (exception a)
		{
			cout << a.what() << endl;
			system("pause");
		}

		system("cls");
	}

	~Admin()
	{
		if (arr)
		{
			for (int i = 0; i < size; i++)
				if (arr[i])
					delete arr[i];
			delete[]arr;
		}

	}
};
