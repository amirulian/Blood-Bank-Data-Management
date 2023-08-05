#include "Header.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	LoadingScreen();
LoginBack:
	system("color 70");
	int AdLog, Wlog;
	string exchoice, choicePosition;
	string email, password;
	cout << "\n\n\t\t########################################################################################\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t       BLOOD BANK MANAGEMENT SYSTEM\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t   ROLE SELECTION MENU\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t       1) Admin\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t       2) Worker\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t" << date_time << endl;
	cout << "\t\tEnter 0 To Go EXIT";
	cout << "\n\t\tChoose(1/2) : ";
	cin >> choicePosition;

	system("CLS");
	try
	{
		if (choicePosition == "0") { atexit(logout); }
		
		else if (choicePosition == "1")
		{
			AdLog = AdminLogin();
			if (AdLog == 1) { AdminHandle(); }
			else goto LoginBack;
		}
		else if (choicePosition == "2")
		{
			Wlog = WorkerLogin();
			if (Wlog == 2)
			{
				WorkerMenu();
			}
			else goto LoginBack;
		}
		else {
			throw 99;
		}
	}
	catch (int e)
	{
		cout << "\n\n\t\tDO YOU WANT TO EXIT ? [Y/N] : ";
		cin >> exchoice;
		if (exchoice == "y" || exchoice == "Y")
		{
			atexit(logout);
		}
		else
		{
			system("cls");
			goto LoginBack;
		}

	}
}