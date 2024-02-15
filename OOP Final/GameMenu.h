#pragma once
class Game
{
	int size = 5;
	char* str1 = new char[8] { "Sign In" };
	char* str2 = new char[8] { "Sign Un" };
	char* str3 = new char[6] { "About" };
	char* str4 = new char[7] { "Top 10" };
	char* str5 = new char[5] { "Exit" };
	char** arr = new char* [size] {str1, str2, str3, str4, str5};

public:

	Game()
	{
		this->start();
	}

	void Menu_Print(int option)
	{
		for (int i = 0; i < size; i++)
			if (option == i)
				cout << green << "\t\t\t\t\t\t" << arr[i] << white << endl;
			else
				cout << "\t\t\t\t\t\t" << arr[i] << endl;
	}

	void start()
	{
		int option = 0;
		char control = 0;
		while (true)
		{
			cout << cyan << font << white;
			Menu_Print(option);
			control = _getch();
			system("cls");

			if (control == 72 || control == 87 || control == 119)
				--option == -1 ? option = 4 : 0;

			else if (control == 80 || control == 83 || control == 115)
				++option == 5 ? option = 0 : 0;

			else if (control == 13)
			{
				if (option == 0)
				{
					string username = "";
					string password = "";
					cout << "Enter Username: ";
					getline(cin, username);
					cout << "Enter Password: ";
					getline(cin, password);

					if (username == "admin")
					{
						if (password == "admin123")
						{
							system("cls");
							Admin a;
						}
						else
						{
							cout << "Incorrect Password" << endl;
							system("pause");
						}
					}

					else
					{
						try
						{
							Player p;
							if (p.Exist(username))
							{
								if (!p.Check(username, password))
								{
									cout << "Incorrect password" << endl << endl;
									system("pause");
									system("cls");
									continue;
								}
								system("cls");
								p.SetUsername(username);
								p.SetPassword(password);
								p.Player_menu_control();
							}

							else
							{
								cout << "Username could not be found" << endl << endl;
								system("pause");
							}

						}
						catch (invalid_argument a)
						{
							cout << a.what() << endl << endl;
							system("pause");
						}

						catch (domain_error e)
						{
							cout << e.what() << endl << endl;
							system("pause");
						}
					}
				}

				else if (option == 1)
				{
					string username = "";
					string password = "";
					cout << "Enter Username: ";
					getline(cin, username);
					cout << "Enter Password: ";
					getline(cin, password);
					try
					{
						Players players(username, password);
						Player p(&players);
						if (username == "admin" || p.Exist(username))
						{
							cout << "This username has already been used" << endl;
							system("pause");
							system("cls");
							continue;
						}

						try
						{
							p.AddPlayer(username, password);
						}
						catch (invalid_argument i)
						{
							cout << i.what() << endl;
							system("pause");
						}
						catch (domain_error e)
						{
							cout << e.what() << endl;
							system("pause");
						}
						catch (exception e)
						{
							cout << e.what() << endl;
							system("pause");
						}

					}
					catch (invalid_argument a)
					{
						cout << a.what() << endl;
						system("pause");
						system("cls");
						continue;
					}
					catch (domain_error e)
					{
						cout << e.what() << endl;
						system("pause");
						system("cls");
						continue;
					}
					catch (exception e)
					{
						cout << e.what() << endl;
						system("pause");
						system("cls");
						continue;
					}
				}

				else if (option == 2)
				{
					about();
				}

				else if (option == 3)
				{
					try
					{
						Quiz q;
						q.Top10();
					}
					catch (domain_error e)
					{
					}

					catch (exception e)
					{
					}
					system("pause");
					system("cls");
				}

				else
					break;
				system("cls");
			}
		}
	}

	void about()
	{

		system("cls");
		char* aboutTitle = new char[] {" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ About Quiz Game ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n"};
		char* aboutText = new char[] { R"(Welcome to the Quiz Game!This quiz will test your knowledge on various topics. 
 Good luck and have fun!

)"};
		char* Top10 = new char[] {"Compete for glory! Our Top 10 feature showcases the highest scorers. Can you make it to the leaderboard?\n\n"};
		char* Admin = new char[] {"Admins spice up the game! They add fresh quizzes for an ever - exciting experience.Dive into the challenge!\n\n"};
		char* Sign_up = new char[] {"Sign Up, Unlock your quiz journey! Sign up for personalized access to quizzes, scores, and friendly competition. Join us now\n\n"};
		char* Sign_in = new char[] {"Sign In, quiz enthusiast! Sign in to access your dashboard, review scores, and dive into quizzes. Let the quizzing continue\n\n"};
		char* type = new char[] {R"(Choose your challenge! Hard Quiz for the daring, Medium Quiz for a balanced experience, and
 Easy Quiz for a relaxed start. Tailor your quiz journey to your level and enjoy the fun!

)"};
		char** arr = new char* [7] {aboutTitle, aboutText, Top10, Admin, Sign_up, Sign_in, type};
		for (size_t i = 0; i < 7; i++)
			for (size_t j = 0; arr[i][j] != '\0'; j++)
			{
				if (_kbhit())
				{
					cin.ignore();
					system("cls");
					for (size_t k = 0; k <= i; k++)
						cout << arr[k];
					break;
				}
				cout << arr[i][j];
				Sleep(40);
			}
		system("pause");
		for (int i = 0; i < 7; i++)
			delete arr[i];
		delete arr;
	}

	~Game()
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
