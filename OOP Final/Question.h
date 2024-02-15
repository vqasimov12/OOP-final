#pragma once

class Question
{
	int _point;
	string _question;
	string _correct_answer;
	list<string>_wrong_answers;
public:
	Question(string question, string correct_answer, list<string> wrong_answers, int point)
	{
		SetQuestion(question);
		Set_Correct_Answer(correct_answer);
		Set_Wrong_Answers(wrong_answers);
		SetPoint(point);
	}

	void SetQuestion(string question)
	{
		if (question.size() < 10)
			throw invalid_argument("Question is too small");
		if (question[question.size() - 1] != '?')
			question += " ?";
		_question = question;
	}

	void Set_Correct_Answer(string answer)
	{
		if (answer.empty())
			throw invalid_argument("Answer can not be empty");
		_correct_answer = answer;
	}

	void Set_Wrong_Answers(list<string> wrong_answers)
	{
		for (auto i : wrong_answers)
		{
			if (i.empty())
				throw invalid_argument("Answer should not be empty");
			_wrong_answers.push_back(i);
		}
	}

	void SetPoint(int point)
	{
		if (point < 1 || point >20)
			throw out_of_range("point should between 1 and 20");
		_point = point;
	}

	string Get_Correct_Answer()
	{
		return _correct_answer;
	}

	string GetQuestion()
	{
		return _question;
	}

	int GetPoint()
	{
		return _point;
	}

	list<string> Get_Wrong_Answers()
	{
		return _wrong_answers;
	}

	list<string>Get_Shuffled_wrong_answers()
	{
		srand(time(0));
		list<string> new_list;
		list<int> indexes{};
		int counter = 0;
		while (counter < 3)
		{
			bool found = false;
			int index = rand() % 3;
			for (auto i : indexes)
				if (i == index)
					found = true;
			if (!found)
			{
				auto it = next(_wrong_answers.begin(), index);
				new_list.push_back(*it);
				indexes.push_back(index);
				counter++;
			}
		}
		return new_list;
	}
};

class Quiz
{
	string _name = "";
	list<Question> questions;
	int count;
	int total_point = 0;
	string path = "";

public:
	Quiz()
	{

	}

	Quiz(string name)
	{
		SetName(name);
	}

	Quiz(string file_path, string name)
	{
		SetName(name);
		read_question(file_path);
	}

	void read_question(string file_path)
	{
		fstream file(file_path, ios::in);
		if (!file)
			throw domain_error("File could not be opened");
		path = file_path;
		string range = "";
		while (getline(file, range, '#') && !file.eof())
		{
			int point = 0;
			string question = "";
			string correct = "";
			string temp;
			list<string>wrong_answers;
			getline(file, question, '*');
			getline(file, correct, '~');
			temp = "";
			int a = 0;
			while (a < 3)
			{
				getline(file, temp, '~');
				wrong_answers.push_back(temp);
				a++;
			}
			file >> point;
			file >> temp;
			Add_question(new Question(question, correct, wrong_answers, point));
			total_point += point;
		}
		file.close();
	}

	void save_questions(string file_path)
	{
		ofstream file(file_path, ios::out);
		if (!file.is_open())
			throw domain_error("File could not be opened for writing ");

		int i = 1;
		for (auto question : questions)
		{
			const list<string> wrong_answers = question.Get_Wrong_Answers();
			file << "Question " << i++ << '#' << question.GetQuestion() << '*'
				<< question.Get_Correct_Answer() << '~';
			for (auto wrong_answer : wrong_answers)
				file << wrong_answer << '~';
			file << question.GetPoint() << '@' << endl;
		}
		file.close();
		string location = "";

		if (_type == "Easy")
		{
			location = location_quiz_easy;
			fstream fl(location + "EasyQuizzes.txt", ios::app);
			if (!fl.is_open())
				throw domain_error("File could not be opened for writing ");
			fl << "Easy:" << _name << "~" << endl;

			fl.close();
		}

		else if (_type == "Medium")
		{
			location = location_quiz_medium;
			fstream fl(location + "MediumQuizzes.txt", ios::app);
			if (!fl.is_open())
				throw domain_error("File could not be opened for writing ");
			fl << "Medium:" << _name << "~" << endl;

			fl.close();
		}

		else if (_type == "Hard")
		{
			location = location_quiz_hard;
			fstream fl(location + "HardQuizzes.txt", ios::app);
			if (!fl.is_open())
				throw domain_error("File could not be opened for writing ");
			fl << "Hard:" << _name << "~" << endl;
			fl.close();
		}

		ofstream f(location + _name + "Scores.txt", ios::out);
		if (!f.is_open())
			throw domain_error("File could not be opened for writing ");
		f.close();

	}

	void Add_question(Question* newquestion)
	{
		questions.push_back(*newquestion);
		count++;
		delete newquestion;
	}

	void SetName(string name)
	{
		if (name.size() < 3)
			throw invalid_argument("Quiz name should contain min 3 character");
		_name = name;
	}

	string GetName()
	{
		return _name;
	}

	list<Question> GetQuestion()
	{
		return questions;
	}

	list<Question> Get_Shuffled_Questions()
	{
		srand(time(0));
		list<Question> new_list;
		list<int> indexes{};
		int counter = 0;
		while (counter < count)
		{
			bool found = false;
			int index = rand() % count;

			for (auto i : indexes)
				if (i == index)
					found = true;

			if (!found)
			{
				auto it = next(questions.begin(), index);
				new_list.push_back(*it);
				indexes.push_back(index);
				counter++;
			}
		}

		return new_list;
	}

	int GetCount()
	{
		return count;
	}

	bool Exist(string quiz_name)
	{
		string type = "";
		string name = "";

		fstream file(location_quiz_easy + "EasyQuizzes.txt");
		if (!file.is_open())
			throw domain_error("File could not be opened");

		while (!file.eof())
		{
			getline(file, type, ':');
			if (file.eof())
				break;
			getline(file, name, '~');
			if (name == quiz_name)
				return 1;
		}
		file.close();

		fstream f(location_quiz_medium + "MediumQuizzes.txt");
		if (!f.is_open())
			throw domain_error("File could not be opened");

		while (!f.eof())
		{
			getline(f, type, ':');
			if (f.eof())
				break;
			getline(f, name, '~');
			if (name == quiz_name)
				return 1;
		}
		f.close();

		fstream fl(location_quiz_hard + "HardQuizzes.txt");
		if (!fl.is_open())
			throw domain_error("File could not be opened");

		while (!fl.eof())
		{
			getline(fl, type, ':');
			if (fl.eof())
				break;
			getline(fl, name, '~');
			if (name == quiz_name)
				return 1;
		}
		fl.close();
		return 0;
	}

	int Get_Total_point()
	{
		return total_point;
	}

	string Get_path()
	{
		return path;
	}

	void Save_data(string* arr, string username, int point, int correct, int wrong)
	{
		string location = "";
		_type == "Easy" ? location = location_quiz_easy + _name + "Scores.txt" : _type == "Medium" ? location = location_quiz_medium + _name + "Scores.txt" :
			_type = "Hard" ? location = location_quiz_hard + _name + "Scores.txt" : location = "Null";
		if (location == "Null")
			throw domain_error("Incorrect location");
		fstream file(location, ios::app);
		if (!file.is_open())
			throw domain_error("Error happend while openning file");
		file << "Username:" << username << "~" << point << '~' << total_point << "~" << endl;
		file.close();

		if (username == "admin")
		{
			fstream f(location_admin + "admin.txt", ios::app);
			if (!f.is_open())
				throw domain_error("Error happend while openning file");
			f << "Quiz name:" << quiz_name << "~";
			for (int i = 0; i < correct + wrong; i++)
				f << arr[i] << "~";
			f << ':' << '~' << point << "~" << correct << "~" << wrong << "~" << endl;
			f.close();
		}

		else
		{
			fstream f(location_players + username + ".txt", ios::app);
			if (!f.is_open())
				throw domain_error("Error happend while openning file");
			f << "Quiz name:" << quiz_name << "~";
			for (int i = 0; i < correct + wrong; i++)
				f << arr[i] << "~";
			f << ':' << '~' << point << "~" << correct << "~" << wrong << "~" << endl;
			f.close();
		}
	}

	void Show(string*& str, int option)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == option)
				cout << dark_red << (i == 0 ? " A. " : i == 1 ? " B. " : i == 2 ? " C. " : " D. ") << str[i] << white << endl;
			else
				cout << (i == 0 ? " A. " : i == 1 ? " B. " : i == 2 ? " C. " : " D. ") << str[i] << endl;
		}
	}

	void Quiz_start(string username)
	{
		list<Question>questions = Get_Shuffled_Questions();
		int correct_count = 0;
		int wrong_count = this->count;
		int point = 0;
		int option = 0;
		char control;
		int count = 0;
		string* all_answers = new string[count];
		while (true)
		{
			auto i = questions.begin();
			string* answers;
			bool change = 1;
			int correct;
			while (true)
			{
				Question question(i->GetQuestion(), i->Get_Correct_Answer(), i->Get_Shuffled_wrong_answers(), i->GetPoint());
				if (change)
				{
					correct = 1 + rand() % 4;
					change = 0;
					if (correct == 1)
						answers = Mix_if_correct_A(question.Get_Correct_Answer(), question.Get_Wrong_Answers());
					else if (correct == 2)
						answers = Mix_if_correct_B(question.Get_Correct_Answer(), question.Get_Wrong_Answers());

					else if (correct == 3)
						answers = Mix_if_correct_C(question.Get_Correct_Answer(), question.Get_Wrong_Answers());

					else if (correct == 4)
						answers = Mix_if_correct_D(question.Get_Correct_Answer(), question.Get_Wrong_Answers());

				}
				system("cls");
				cout << cyan << font << white << endl;
				cout << green << question.GetQuestion() << white << endl << endl;
				Show(answers, option);
				control = _getch();

				if (control == 72 || control == 87 || control == 119)
					--option == -1 ? option = 3 : 0;

				else if (control == 80 || control == 83 || control == 115)
					++option == 4 ? option = 0 : 0;

				else if (control == 77 || control == 68 || control == 100)
				{
					i++;
					if (i == questions.end())
					{
						char cont = 0;
						int num = 1;
						while (true)
						{
							system("cls");
							cout << cyan << font << white << endl;
							cout << green << "\t\t Do You want to finish the quiz even though  there are unanswered questions?" << white << endl << endl;
							if (num)
								cout << red << "  " << "\t\t\t\t\t\t\tYes\n" << white << "\t\t\t\t\t\t\tNo" << endl;
							else
								cout << "  " << "\t\t\t\t\t\t\tYes\n" << red << "\t\t\t\t\t\t\tNo" << white << endl;
							cont = _getch();
							if (cont == 72 || cont == 87 || cont == 119)
								--num == -1 ? num = 1 : 0;

							else if (cont == 80 || cont == 83 || cont == 115)
								++num == 2 ? num = 0 : 0;

							else if (cont == 13)
								if (num)
								{
									system("cls");
									cout << cyan << font << white;
									cout << green << "Correct Answers: " << dark_red << correct_count << endl;
									cout << green << "Wrong Answers:   " << dark_red << wrong_count << endl;
									cout << green << "Total point:     " << dark_red << point << "/" << total_point << white << endl << endl;
									try
									{
										Save_data(all_answers, username, point, correct_count, wrong_count);
									}
									catch (domain_error e)
									{
										cout << e.what() << endl << endl;
										system("pause");
										system("cls");
									}
									return;
								}

								else
								{
									i = questions.begin();
									option = 0;
									break;
								}
						}
					}
					change = 1;
				}

				else if (control == 75 || control == 65 || control == 97)
				{
					if (i != questions.begin())
						i--;
					change = 1;
				}

				else if (control == 27)
					return;

				else if (control == 13)
				{
					if (option + 1 == correct)
					{
						correct_count++;
						point += i->GetPoint();
						wrong_count--;
					}
					try
					{
						i = questions.erase(i);
					}
					catch (...)
					{

					}
					Add_string(all_answers, count, answers[option]);
					option = 0;
					change = 1;
					break;
				}

			}
			if (questions.size() == 0)
			{
				system("cls");
				cout << cyan << font << white;
				cout << green << "Correct Answers: " << dark_red << correct_count << endl;
				cout << green << "Wrong Answers:   " << dark_red << wrong_count << endl;
				cout << green << "Total point:     " << dark_red << point << "/" << total_point << white << endl << endl;
				try
				{
					Save_data(all_answers, username, point, correct_count, wrong_count);
				}
				catch (domain_error e)
				{
					cout << e.what() << endl << endl;
					system("pause");
					system("cls");
				}
				return;
			}

		}
	}

	void Top10()
	{
		map<string, string>top_10;

		string location = "";
		Quiz_menu();
		if (_type == "Easy")
			location = location_quiz_easy + quiz_name + "Scores.txt";
		else if (_type == "Medium")
			location = location_quiz_medium + quiz_name + "Scores.txt";
		else if (_type == "Hard")
			location = location_quiz_hard + quiz_name + "Scores.txt";
		else if (_type == "Null")return;
		fstream f(location, ios::in);
		if (!f.is_open())
			throw domain_error("Error occupied while openning file");
		string temp;
		string username;
		string point;
		string total_point;
		while (!f.eof())
		{
			getline(f, temp, ':');
			if (f.eof())break;
			getline(f, username, '~');
			getline(f, point, '~');
			getline(f, total_point, '~');
			top_10[username] = point;
		}
		f.close();
		vector<pair<string, string>> top_10_vector(top_10.begin(), top_10.end());
		sort(top_10_vector.begin(), top_10_vector.end(),
			[](pair<string, string>& a, pair<string, string>& b)->bool {
				return stoi(a.second) > stoi(b.second);
			});
		cout << cyan << font << white;
		cout << green << "Top 10 Scores:\n\n" << white << endl;
		int count = 0;
		for (auto& i : top_10_vector) {
			{
				cout << "Username: " << dark_red << i.first << white;
				for (int j = 0; j < 15 - i.first.size(); j++)
					cout << " ";
				cout << "Points: " << green << i.second << white << "/" << red << total_point << white << endl;

				if (++count >= 10)
					break;
			}
		}
		cout << endl << endl;
	}

	void My_quiz(string file_path)
	{
		system("cls");
		cout << cyan << font << white;
		int i = 1;
		string temp;
		string name;
		string answer;
		string point;
		string correct;
		string wrong;
		int count = 0, l = 1;
		fstream file(file_path, ios::in);
		if (!file.is_open())
			throw domain_error("Error occupied while openning file");
		while (!file.eof())
		{
			l = 1;
			list<string> answers;
			getline(file, temp, ':');
			if (file.eof())break;
			getline(file, name, '~');
			while (true)
			{
				getline(file, answer, '~');
				if (answer == ":")break;
				answers.push_back(answer);
			}
			getline(file, point, '~');
			getline(file, correct, '~');
			getline(file, wrong, '~');
			cout << endl << i++ << (i < 10 ? ". " : ".") << "Quiz name: " << green << name << white << endl;
			cout << "\n Answers:\n";
			for (auto k : answers)
				cout << " " << l++ << ". " << yellow << k << white << endl;
			cout << "\n Total point:     " << yellow << point << white << "\n Correct answers: " << yellow << correct << white << "\n Wrong answers:   " << yellow << wrong << white << endl << endl;
		}
		file.close();
		cout << endl << endl;
	}
};
