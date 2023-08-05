#include <stdio.h>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <cstring>
#include <iostream>
#include <mysql.h>
#include <sstream>
#include <time.h>
using namespace std;

int valid, valid2, qstate, qstate2;
string user, id;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* result;
time_t now = time(0);
char* date_time = ctime(&now);
void LoadingScreen();
void AdminHandle();
void addWorker();
void deleteWorker(string workerid3);
void SearchWorker(int guide);
void ModifyWorker(string workerid2);
void addDonor(int guide);
void deleteDonor(string donorid1);
void viewBloodDonatedSTOCK(int guide6);
void viewBloodDetail(int guide2);
void viewBloodSTOCK(int guide);
void CreateOrder();
void SearchOrder(int guide);
void deleteOrder();
void SearchDonor(int guide3, int guide2);
void ModifyDonor(string donorid2, int guide);
void UpdateBlood(int guide7, int guide);
int AdminLogin();
int WorkerLogin();
void WorkerMenu();
void AdminHandleDonorMenu();
void HandleWorkerMenu();
void ShowPPD(int guide);
void ShowHospital(int guide);
void EditHospital();
void EnterHospital();
void deleteHospital();
void EnterPPD();
void deletePPD();
void EditPPD();
void AdjustBloodStock();
void AdjustBloodStatus();
void RemoveBloodDonated();
void HandleBlood(int guide);
void viewOrder();
void logout();
void editOrder(string invoiceid);


//DONE
class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "\t\t\t\t\tDatabase Initiated and Connecting\n\n" << endl;
			system("pause");
			system("cls");
		}
		else
			cout << "Failed To Connect" << mysql_errno(conn) << endl;


		conn = mysql_real_connect(conn, "localhost", "root", "", "bloodbankmanagement", 3306, NULL, 0);
		if (conn)
		{
			cout << "\n\n\n\n\n\n\t\t\t\t\t---+ Database Connected Successfully +---" << endl;
			cout << "\n\n\t\t\t\t\t        " << date_time;
			system("PAUSE");
			system("CLS");
		}
		else
		{
			cout << "\t\t\t\t\tFAILED TO CONNECT TO DATABASE" << mysql_errno(conn) << endl;
			system("PAUSE");
			exit(3);
		}
	}
};

/////////////////////////// LOGIN AND MENU //////////////////////////
//DONE
int AdminLogin() {
AdminReLogin:
	system("color b0");
	int counter;
	char password[32];
	string email;
	cout << "\n\n\t\t########################################################################################\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t       BLOOD BANK MANAGEMENT SYSTEM\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t   ADMIN LOGIN MENU\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t" << date_time << endl;
	cout << "\t\tEnter 0 To Go Back";
	cout << "\n\t\tEmail :";
	cin >> email;
	counter = 0;
	while (counter < email.length())
	{
		if (isupper(email[counter]))
		{
			email[counter] = tolower(email[counter]);
		}
		counter++;
	}
	cout << endl;
	cout << "\t\tPassword :";
	counter = 0;
	char a;
	for (counter = 0;;)//infinite loop
	{
		a = _getch();//stores char typed in a
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
			//check if a is numeric or alphabet
		{
			password[counter] = a;//stores a in pass
			++counter;
			cout << "*";
		}
		if (a == '\b' && counter >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--counter;
		}
		if (a == '\r')//if enter is pressed
		{
			password[counter] = '\0';//null means end of string.
			break;//break the loop
		}
	}

	counter = 0;
	while (counter < 32)
	{
		if (isupper(password[counter]))
		{
			password[counter] = tolower(password[counter]);
		}
		counter++;
	}

	system("CLS");
	if (email == "0" && password[0] == '0')
	{
		return 3;
	}
	string checkAdmin_query = "SELECT admin.email, logindetail.password FROM admin INNER JOIN logindetail ON admin.email = logindetail.email WHERE  admin.email = '" + email + "' AND logindetail.password = '" + password + "'";
	const char* cA = checkAdmin_query.c_str();
	valid = mysql_query(conn, cA);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //Find User
		{
			string checkUserAdmin_query = "select * from admin where email = '" + email + "'";
			const char* cuA = checkUserAdmin_query.c_str();
			qstate = mysql_query(conn, cuA);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				while (row = mysql_fetch_row(result))
				{
					user = row[3];
					id = row[1];
				}
				return 1;
			}
			else
			{
				goto AdminReLogin;
			}
		}
		else
		{
			goto AdminReLogin;
		}
	}
	else {
		goto AdminReLogin;
	}
}

//DONE
int WorkerLogin() {
	system("color 30");
WorkerReLogin:
	int counter;
	char password[32];
	string email;
	char ch;
	cout << "\n\n\t\t****************************************************************************************\n";
	cout << "\t\t*\t\t\t\t\t\t\t\t\t\t       *\n";
	cout << "\t\t*\t\t\t       BLOOD BANK MANAGEMENT SYSTEM\t\t\t       *\n";
	cout << "\t\t*\t\t\t\t\t\t\t\t\t\t       *\n";
	cout << "\t\t*\t\t\t\t\t\t\t\t\t\t       *\n";
	cout << "\t\t*\t\t\t\t   WORKER LOGIN MENU\t\t\t\t       *\n";
	cout << "\t\t*\t\t\t\t\t\t\t\t\t\t       *\n";
	cout << "\t\t****************************************************************************************\n";
	cout << "\t\t" << date_time << endl;
	cout << "\t\tEnter 0 To Go Back";
	cout << "\n\t\tEmail :";
	cin >> email;
	counter = 0;
	while (counter < email.length())
	{
		if (isupper(email[counter]))
		{
			email[counter] = tolower(email[counter]);
		}
		counter++;
	}
	cout << endl;
	cout << "\t\tPassword :";
	counter = 0;
	char a;
	for (counter = 0;;)//infinite loop
	{
		a = _getch();//stores char typed in a
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
			//check if a is numeric or alphabet
		{
			password[counter] = a;//stores a in pass
			++counter;
			cout << "*";
		}
		if (a == '\b' && counter >= 1)//if user typed backspace
			//i should be greater than 1.
		{
			cout << "\b \b";//rub the character behind the cursor.
			--counter;
		}
		if (a == '\r')//if enter is pressed
		{
			password[counter] = '\0';//null means end of string.
			break;//break the loop
		}
	}

	counter = 0;
	while (counter < 32)
	{
		if (isupper(password[counter]))
		{
			password[counter] = tolower(password[counter]);
		}
		counter++;
	}

	system("CLS");
	if (email == "0" && password[0] == '0')
	{
		return 3;
	}
	counter = 0;
	string checkAdmin_query = "SELECT worker.email, logindetail.password FROM worker INNER JOIN logindetail ON worker.email = logindetail.email WHERE  worker.email = '" + email + "' AND logindetail.password = '" + password + "'";
	const char* cA = checkAdmin_query.c_str();
	valid = mysql_query(conn, cA);

	if (email == "0" && password == "0")
	{
		return 3;
	}
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //Find User
		{
			string checkUserWorker_query = "select * from worker where email = '" + email + "'";
			const char* cuW = checkUserWorker_query.c_str();
			qstate = mysql_query(conn, cuW);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				while (row = mysql_fetch_row(result))
				{
					user = row[2];
					id = row[1];
				}
				return 2;
			}
			else
			{
				goto WorkerReLogin;
			}
		}
		else
		{
			goto WorkerReLogin;
		}
	}
	else {
		goto WorkerReLogin;
	}
}

//DONE
void LoadingScreen() {
	system("color 1E");
	cout << "\n\n\n\n\n\t\t\t\t\tLOADING\t\t";
	char x = 219;
	for (int i = 0; i < 35; i++)
	{
		cout << x;
		Sleep(50);
	}
	cout << "\n\n\t";
	system("color 0C");
	db_response::ConnectionFunction();
	system("color 07");
}

//DONE
void WorkerMenu()
{
	system("cls");
	string option,exchoice;
	cout << "\n\n\n\t\t########################################################################################\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\tBLOOD BANK MANAGEMENT SYSTEM \t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t   Welcome To Worker Menu\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t1) Add Donor\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t2) Search Donor\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t3) Modify Donor\t\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t4) Manage Blood Data\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t5) Show All Pusat Derma Darah\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t6) Show All Hospital\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t\t\t\t\t\t\t       #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t" << date_time << endl;
	cout << "\t\tEnter \"0\" To Logout\n";
	cout << "\t\tChoice :";
	try
	{
		cin >> option;
		if (option == "1")
		{
			addDonor(2);
		}
		else if (option == "2")
		{
			SearchDonor(2, 2);
		}
		else if (option == "3")
		{
			SearchDonor(2, 3);
		}
		else if (option == "4")
		{
			HandleBlood(2);
		}
		else if (option == "5")
		{
			ShowPPD(2);
		}
		else if (option == "6")
		{
			ShowHospital(2);
		}
		else
		{
			system("cls");
			throw 99;
		}

	}
	catch (int x)
	{
		system("cls");
		cout << "\n\n\t\tDO YOU WANT TO EXIT ? [Y/N] : ";
		cin >> exchoice;
		if (exchoice == "y" || exchoice == "Y")
		{
			atexit(logout);
		}
		else
		{
			system("cls");
			WorkerMenu();
		}
	}

}

//DONE
void AdminHandle() {
	system("CLS");
main:
	string option1,exchoice;
	cout << "\n\n\t########################################################################################################\n";
	cout << "\t#                                                                                                      #\n";
	cout << "\t#\t\t\t\t\tBLOOD BANK MANAGEMENT SYSTEM\t\t\t\t       #\n";
	cout << "\t#                                                                                                      #\n";
	cout << "\t########################################################################################################\n";
	cout << "\n\t\t\t\t\t\t    ADMIN MAIN MENU\t\t\t\t\t       \n\n";
	cout << "\t________________________________________________________________________________________________________\n";
	cout << "\t|                                                                                                      |\n";
	cout << "\t|\t\t\t\t\t1-   Donor's Data\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t2-   Worker's Data\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t3-   Blood Data\t\t\t\t\t\t       |\n";
	cout << "\t|                                                                                                      |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t            PUSAT DERMA DARAH\t\t\t\t\t       |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t\t4-   Show All Pusat Derma Darah\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t5-   Modify Pusat Derma Darah Detail\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t6-   Add Pusat Derma Darah\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t7-   Delete Pusat Derma Darah\t\t\t\t       |\n";
	cout << "\t|                                                                                                      |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t\t\tHOSPITAL\t\t\t\t\t       |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t\t8-   Show All Hospital\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t9-   Modify Hospital Detail\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t10-  Add Hospital\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t11-  Delete Hospital\t\t\t\t\t       |\n";
	cout << "\t|                                                                                                      |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t\t      ORDER BLOOD\t\t\t\t\t       |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t|\t\t\t\t\t12-  View Order\t\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t13-  Create Order\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t14-  Search Order\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t15-  Delete Order\t\t\t\t\t       |\n";
	cout << "\t|\t\t\t\t\t16-  Modify Order Detail\t\t\t\t       |\n";
	cout << "\t|______________________________________________________________________________________________________|\n";
	cout << "\t " << date_time << endl;
	cout << "\n\t ENTER \"0\" To Exit\n";
	cout << "\t Choose : ";
	cin >> option1;
	try
	{

		if (option1 == "0")
		{
			system("cls");
			atexit(logout);
		}
		else if (option1 == "1")
		{
			system("cls");
			AdminHandleDonorMenu();
		}
		else if (option1 == "2")
		{
			system("cls");
			HandleWorkerMenu();
		}
		else if (option1 == "3")
		{
			system("cls");
			HandleBlood(1);
		}
		else if (option1 == "4")
		{
			system("cls");
			ShowPPD(1);
		}
		else if (option1 == "5")
		{
			EditPPD();
			system("cls");
		}
		else if (option1 == "6")
		{
			EnterPPD();
			system("cls");
		}
		else if (option1 == "7")
		{
			deletePPD();
			system("cls");
		}
		else if (option1 == "8")
		{
			ShowHospital(1);
			system("cls");
		}
		else if (option1 == "9")
		{
			EditHospital();
			system("cls");
		}
		else if (option1 == "10")
		{
			EnterHospital();
			system("cls");
		}
		else if (option1 == "11")
		{
			deleteHospital();
			system("cls");
		}
		else if (option1 == "12")
		{
			viewOrder();
			system("cls");
		}
		else if (option1 == "13")
		{
			CreateOrder();
			system("cls");
		}
		else if (option1 == "14")
		{
			SearchOrder(1);
			system("cls");
		}
		else if (option1 == "15")
		{
			deleteOrder();
			system("cls");
		}
		else if (option1 == "16")
		{
			SearchOrder(2);
			system("cls");

		}
		else
		{
			throw 99;
		}

	}
	catch (int x)
	{
		system("cls");
		cout << "\n\n\t\tDO YOU WANT TO EXIT ? [Y/N] : ";
		cin >> exchoice;
		if (exchoice == "y" || exchoice == "Y")
		{
			atexit(logout);
		}
		else
		{
			system("cls");
			AdminHandle();
		}
	}
}

//DONE
void logout() {
	system("cls");
	cout << "\n\n\t\t\t\t\t\tLOG OUT SUCCESSFULLY !\n\n";
	cout << "\t  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "\t  *                                                                                           *" << endl;
	cout << "\t  *\t**********  ****    ****     ********     ****    ****  ****   ****  ********       *" << endl;
	cout << "\t  *\t**********  ****    ****     ********     *****   ****  ****  ****   ********       *" << endl;
	cout << "\t  *\t   ****     ****    ****    ****  ****    ******  ****  **** ****    ****           *" << endl;
	cout << "\t  *\t   ****     ************    ****  ****    ******* ****  ********     ********       *" << endl;
	cout << "\t  *\t   ****     ************   ************   **** *******  ********     ********       *" << endl;
	cout << "\t  *\t   ****     ****    ****   ************   ****  ******  **** ****        ****       *" << endl;
	cout << "\t  *\t   ****     ****    ****  ****      ****  ****   *****  ****  ****   ********       *" << endl;
	cout << "\t  *\t   ****     ****    ****  ****      ****  ****    ****  ****   ****  ********       *" << endl;
	cout << "\t  *                                                                                           *" << endl;
	cout << "\t  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	exit(0);
}

//DONE
void AdminHandleDonorMenu() {
	system("CLS");
HandleDonorGate:
	string option1;
	string exchoice;
	cout << "\n\n\n\t\t########################################################################################\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t\tBLOOD BANK MANAGEMENT SYSTEM\t\t\t       #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t\t  DONOR MANAGEMENT MENU\t\t\t               #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t            1) Add Donor\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t            2) Search Donor\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t            3) Modify Donor\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t            4) Delete Donor\t\t\t\t       #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tEnter \"0\" To Go Back\n";
	cout << "\t\tChoice :";
	try
	{
		cin >> option1;
		if (option1 == "1")
		{
			addDonor(1);
		}
		else if (option1 == "2")
		{
			SearchDonor(1, 2);
		}
		else if (option1 == "3")
		{
			SearchDonor(1, 3);
		}
		else if (option1 == "4")
		{
			SearchDonor(1, 4);
		}
		else if (option1 == "0")
		{
			AdminHandle();
		}
		else
		{
			throw 99;
		}
	}
	catch (int x)
	{
		system("cls");
		cout << "\n\n\t\tDO YOU WANT TO EXIT ? [Y/N] : ";
		cin >> exchoice;
		if (exchoice == "y" || exchoice == "Y")
		{
			atexit(logout);
		}
		else
		{
			system("cls");
			AdminHandleDonorMenu();
		}
	}
}

///////////////////////////////// ADMIN HANDLE WORKER ////////////////////////
//DONE
void HandleWorkerMenu() {
	system("CLS");
	string option;
	string exchoice;
	cout << "\n\n\n\t\t########################################################################################\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t\tBLOOD BANK MANAGEMENT SYSTEM\t\t\t       #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t\t  WORKER MANAGEMENT MENU\t\t\t       #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t#\t\t\t\t    1) Add Worker\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t    2) Search Worker\t\t\t               #\n";
	cout << "\t\t#\t\t\t\t    3) Modify Worker\t\t\t\t       #\n";
	cout << "\t\t#\t\t\t\t    4) Delete Worker\t\t\t\t       #\n";
	cout << "\t\t#                                                                                      #\n";
	cout << "\t\t########################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tChoice :";
	try
	{
		cin >> option;
		if (option == "1") { addWorker(); }
		else if (option == "2") { SearchWorker(2); }
		else if (option == "3") { SearchWorker(3); }
		else if (option == "4") { SearchWorker(4); }
		else  if (option == "0") { AdminHandle(); }
		else
		{
			throw 99;
		}
	}
	catch (int x)
	{
		system("cls");
		cout << "\n\n\t\tDO YOU WANT TO EXIT ? [Y/N] : ";
		cin >> exchoice;
		if (exchoice == "y" || exchoice == "Y")
		{
			atexit(logout);
		}
		else
		{
			system("cls");
			HandleWorkerMenu();
		}
	}

}

//DONE
void addWorker() {
addWorkerGate:
	int counter = 0;
	string name, Email, HomeAddress, MailingAddress, IDCard, AccountID, WorkerID, Password, Choice, AcID, WkID, numberLogin, numberWorker;
	WkID = "w";
	AcID = "ac";
	system("CLS");
	cout << "\n\n\t\t****************************************************************************************************\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*\t\t\t\t        WORKER REGISTER MENU\t\t\t\t           *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t****************************************************************************************************\n";
	cout << "\t\t" << date_time << "\n\n";
	cin.ignore();
	cout << "\t\t\t\tEnter Worker's Name : ";
	getline(cin, name);
	while (counter < name.length())
	{
		if (isupper(name[counter]))
		{
			name[counter] = tolower(name[counter]);
		}
		counter++;
	}
	if (name == "cancel") { goto addWorkerGate; }
	if (name == "0") { AdminHandle(); }
	cin.ignore();
	cout << "\t\t\t\tEnter Worker's Home Address : ";
	getline(cin, HomeAddress);
	counter = 0;
	while (counter < HomeAddress.length())
	{
		if (isupper(HomeAddress[counter]))
		{
			HomeAddress[counter] = tolower(HomeAddress[counter]);
		}
		counter++;
	}
	if (HomeAddress == "cancel") { goto addWorkerGate; }
	if (HomeAddress == "0") { AdminHandle(); }
	cin.ignore();
	cout << "\t\t\t\tEnter Worker Mailing Address : ";
	getline(cin, MailingAddress);
	counter = 0;
	while (counter < MailingAddress.length())
	{
		if (isupper(MailingAddress[counter]))
		{
			MailingAddress[counter] = tolower(MailingAddress[counter]);
		}
		counter++;
	}
	if (MailingAddress == "cancel") { goto addWorkerGate; }
	if (MailingAddress == "0") { AdminHandle(); }
	cin.ignore();
	EnterIDCard:
	cout << "\t\t\t\tEnter Worker's Identification Card Number : ";
	getline(cin, IDCard);
	counter = 0;
	while (counter < IDCard.length())
	{
		if (isupper(IDCard[counter]))
		{
			IDCard[counter] = tolower(IDCard[counter]);
		}
		counter++;
	}
	if (IDCard == "cancel") { goto addWorkerGate; }
	if (IDCard == "0") { AdminHandle(); }
	if (IDCard.length() < 12)
	{  
		cout << "\n\t\t\t\t\t\tIdentification Card Not Valid\n";
		goto EnterIDCard;
	}
	cin.ignore();
	bool flag3 = false;
	do
	{
		cout << "\t\t\t\tEnter Worker's Email : ";
		cin >> Email;
		counter = 0;
		while (counter < Email.length())
		{
			if (isupper(Email[counter]))
			{
				Email[counter] = tolower(Email[counter]);
			}
			counter++;
		}
		if (Email == "cancel") { goto addWorkerGate; }
		if (Email == "0") { AdminHandle(); }
		string CheckEmail_query = "select * from logindetail where email = '" + Email + "' limit 1";
		const char* CE = CheckEmail_query.c_str();
		valid = mysql_query(conn, CE);

		if (!valid)
		{
			result = mysql_store_result(conn);
			if (result->row_count == 1)
			{
				cout << "\n\t\t\t\t\tEmail Already Taken\n\n";
				flag3 = false;
			}
			if (result->row_count == 0)
			{
				flag3 = true;
			}

		}
		else {
			cout << "ERROR EXECUTION EMAIL : " << mysql_errno(conn);
			AdminHandle();
		}
	} while (flag3 == false);
	cin.ignore();
EnterPassword:
	cout << "\t\t\t\tEnter Worker's Email's Password : ";
	getline(cin, Password);
	counter = 0;
	while (counter < Password.length())
	{
		if (isupper(Password[counter]))
		{
			Password[counter] = tolower(Password[counter]);
		}
		counter++;
	}
	if (Password == "cancel") { goto addWorkerGate; }
	if (Password == "0") { AdminHandle(); }
	if (Password == "") { goto EnterPassword; }

	string insert_login = "INSERT INTO LOGINDETAIL (name,email, password) VALUES ('" + name + "','" + Email + "', '" + Password + "')";
	const char* InsL = insert_login.c_str();
	valid = mysql_query(conn, InsL);
	if (!valid)
	{
		string SearchLoginEmail = "SELECT * FROM LOGINDETAIL WHERE email = '" + Email + "'";
		const char* SEL = SearchLoginEmail.c_str();
		valid2 = mysql_query(conn, SEL);
		if (!valid2)
		{
			result = mysql_store_result(conn);
			while (row = mysql_fetch_row(result))
			{
				AccountID = row[0];
			}
		}
		numberLogin = AccountID;
		AccountID = AcID + AccountID;
		string updateLoginEmail = "UPDATE logindetail SET Number='" + numberLogin + "' , accountid='" + AccountID + "' WHERE email = '" + Email + "'";
		const char* ULE = updateLoginEmail.c_str();
		valid2 = mysql_query(conn, ULE);
		if (!valid2)
		{
			string insertWorker = "INSERT INTO worker (name, email, homeaddress, mailingaddress, idcardnumber, accountid) VALUES ('" + name + "', '" + Email + "', '" + HomeAddress + "', '" + MailingAddress + "', '" + IDCard + "', '" + AccountID + "')";
			const char* iW = insertWorker.c_str();
			qstate = mysql_query(conn, iW);
			if (!qstate)
			{
				string SelectWorkerEmail = "SELECT * FROM worker WHERE email = '" + Email + "'";
				const char* SWL = SelectWorkerEmail.c_str();
				valid2 = mysql_query(conn, SWL);
				if (!valid2)
				{
					result = mysql_store_result(conn);
					while (row = mysql_fetch_row(result))
					{
						WorkerID = row[0];
					}
				}
				numberWorker = WorkerID;
				WorkerID = WkID + WorkerID;
				string updateWorkerEmail = "UPDATE worker SET number = '" + numberWorker + "', workerid = '" + WorkerID + "' WHERE email = '" + Email + "'";
				const char* UWE = updateWorkerEmail.c_str();
				valid2 = mysql_query(conn, UWE);
				if (!valid2)
				{
					string getWorker = "SELECT * FROM worker WHERE email = '" + Email + "'";
					const char* GWE = getWorker.c_str();
					valid2 = mysql_query(conn, GWE);
					if (!valid2)
					{
						result = mysql_store_result(conn);
						while (row = mysql_fetch_row(result))
						{
							cout << "\n\n\t\t****************************************************************************************************\n";
							cout << "\t\t\t\t\tREGISTER SUCCESFULLY !";
							cout << "\n\t\t\t\t\tWorkerID: " << row[1];
							cout << "\n\t\t\t\t\tName: " << row[2];
							cout << "\n\t\t\t\t\tEmail: " << row[3];
							cout << "\n\t\t\t\t\tHome Address: " << row[4];
							cout << "\n\t\t\t\t\tMailing Address: " << row[5];
							cout << "\n\t\t\t\t\tID Card Number: " << row[6];
							cout << "\n\t\t\t\t\tAccount ID: " << row[7];
							cout << "\n\t\t****************************************************************************************************\n";
						}
						system("PAUSE");
						addWorker();
					}
				}
			}
			else
			{
				cout << "\t\t\t\tQuery Execution Problem " << mysql_errno(conn) << endl;
				cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
				cin.ignore();
				cin >> Choice;
				cin.ignore();
				if (Choice == "Y" || Choice == "y") { goto addWorkerGate; }
				else { HandleWorkerMenu(); }

			}
		}
	}
}

//DONE
void SearchWorker(int guide)
{
	system("cls");
	string WorkerID;
	int choice;
	if (guide == 2)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t         SEARCH WORKER MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	if (guide == 3)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t        MODIFY WORKER MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	if (guide == 4)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t        DELETE WORKER MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	cout << "\t\t" << date_time << endl;
	cout << "\n\t\tWorkerID : ";
	cin.ignore();
	cin >> WorkerID;
	int counter = 0;
	while (counter < WorkerID.length())
	{
		if (isupper(WorkerID[counter]))
		{
			WorkerID[counter] = tolower(WorkerID[counter]);
		}
		counter++;
	}
	if (WorkerID == "0")
	{
		HandleWorkerMenu();
	}

	string searchWorker_query = "select * from worker where workerid = '" + WorkerID + "' limit 1";
	const char* sW = searchWorker_query.c_str();
	qstate = mysql_query(conn, sW);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			cout << "\n\n\n\t\t______________________________________________________________________________________________________\n";
			cout << "\t\t\t\t\t\t\t Worker Exist!\n";
			while (row = mysql_fetch_row(result))
			{
				cout << "\t\t______________________________________________________________________________________________________\n\n";
				cout << "\t\tWorker ID :" << row[1] << "\n";
				cout << "\t\tName :" << row[2] << "\n";
				cout << "\t\tEmail :" << row[3] << "\n";
				cout << "\t\tHomeAddress :" << row[4] << "\n";
				cout << "\t\tMailing Address :" << row[5] << "\n";
				cout << "\t\tIDCard Number:" << row[6] << "\n";
				cout << "\t\tAccountID :" << row[7] << "\n";
				cout << "\t\t______________________________________________________________________________________________________\n";
				if (guide == 2)
				{
					system("pause");
					system("cls");
					SearchWorker(2);
				}
				if (guide == 3)
				{
					ModifyWorker(WorkerID);
					system("pause");
					system("cls");
				}
				if (guide == 4)
				{
					deleteWorker(WorkerID);
					system("pause");
					system("cls");
				}
			}
		}
		if (result->row_count == 0) //if result 1 or found
		{
			cout << "\n\n\n\n\t\t______________________________________________________________________________________________________\n\n";
			cout << "\t\t\t\t\t\t Worker DOES NOT EXIST !\n\n";
			cout << "\t\t______________________________________________________________________________________________________\n\n";
			system("pause");
			SearchWorker(2);
		}
	}
	else
	{
		HandleWorkerMenu();
	}
}

//done
void ModifyWorker(string workerid2)
{
gate1:
	string name, email, homeaddress, mailingaddress, idcardnumber, accountid;
	int counter;
	cout << "\n\t\t\t\t\tPlease Enter New Data For Worker : " << workerid2;
	cout << "\n\t\t______________________________________________________________________________________________________\n";
	cout << "\t\t" << date_time << "\n\n";
	cin.ignore();
	cout << "\t\tEnter \"0\" To Go Back\n";
	cout << "\t\tName : ";
	getline(cin, name);
	counter = 0;
	while (counter < name.length())
	{
		if (isupper(name[counter]))
		{
			name[counter] = tolower(name[counter]);
		}
		counter++;
	}
	if (name == "0") { HandleWorkerMenu(); }
	if (name == "cancel") { goto gate1; }
	cout << "\t\tEmail : ";
	cin >> email;
	counter = 0;
	while (counter < email.length())
	{
		if (isupper(email[counter]))
		{
			email[counter] = tolower(email[counter]);
		}
		counter++;
	}
	if (email == "0") { HandleWorkerMenu(); }
	if (email == "cancel") { goto gate1; }
	cin.ignore();
	cout << "\t\tHome Address : ";
	getline(cin, homeaddress);
	counter = 0;
	while (counter < homeaddress.length())
	{
		if (isupper(name[counter]))
		{
			homeaddress[counter] = tolower(homeaddress[counter]);
		}
		counter++;
	}
	if (homeaddress == "0") { HandleWorkerMenu(); }
	if (homeaddress == "cancel") { goto gate1; }
	cin.ignore();
	cout << "\t\tMailing Address : ";
	getline(cin, mailingaddress);
	counter = 0;
	while (counter < mailingaddress.length())
	{
		if (isupper(mailingaddress[counter]))
		{
			mailingaddress[counter] = tolower(mailingaddress[counter]);
		}
		counter++;
	}
	if (mailingaddress == "0") { HandleWorkerMenu(); }
	if (mailingaddress == "cancel") { goto gate1; }
	cin.ignore();
	EnterIDCard:
	cout << "\t\tIdentification Card Number : ";
	getline(cin, idcardnumber);
	counter = 0;
	while (counter < idcardnumber.length())
	{
		if (isupper(idcardnumber[counter]))
		{
			idcardnumber[counter] = tolower(idcardnumber[counter]);
		}
		counter++;
	}
	if (idcardnumber == "0") { HandleWorkerMenu(); }
	if (idcardnumber == "cancel") { goto gate1; }
	if (idcardnumber.length() < 12)
	{
		cout << "\n\t\t\t\t\t\t\t\t\tIdentification Card Not Valid\n\n";
		goto EnterIDCard;
	}

	string searchWorker_query = "select * from logindetail where accountid = (select accountid from worker where workerid = '" + workerid2 + "' limit 1)";
	const char* sW = searchWorker_query.c_str();
	qstate = mysql_query(conn, sW);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				accountid = row[0];
			}
		}
	}
	else {
		cout << "\n\t\tError Execution " << mysql_errno(conn);
		system("pause");
		system("cls");
		goto gate1;
	}

	string updateWorker_query = "update worker set Name = '" + name + "', Email = '" + email + "', HomeAddress = '" + homeaddress + "', MailingAddress = '" + mailingaddress + "', IDCardNumber = '" + idcardnumber + "' where workerid = '" + workerid2 + "' ";
	const char* uW = updateWorker_query.c_str();
	valid = mysql_query(conn, uW);

	string updateWorkerLogin_query = "update logindetail set Email = '" + email + "' where accountid = '" + accountid + "' ";
	const char* uWL = updateWorkerLogin_query.c_str();
	valid2 = mysql_query(conn, uWL);

	if (!valid && !valid2)
	{
		cout << "\n\t\t\tUpdate Successful!";
		system("pause");
		HandleWorkerMenu();
	}
	else
	{
		cout << "\n\t\tError Execution " << mysql_errno(conn);
		system("pause");
		system("cls");
		goto gate1;
	}
}

//DONE
void deleteWorker(string workerid3)
{
	string choice, donatedid, accountid, bloodtype, quantity, workerid;
	string searchWorker_query = "select * from logindetail where accountid = (select accountid from worker where workerid = '" + workerid3 + "' limit 1)";
	const char* sW = searchWorker_query.c_str();
	qstate = mysql_query(conn, sW);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				accountid = row[1];
			}
		}
	}

	cout << "\n\n\t\t\t\t ARE YOU SURE WANT TO DELETE DATA OF WORKER " << workerid3 << " ?\n\t\t\t\t Once It is Deleted It Cannot Be Retrieve Again ";
	cout << "\n\t\t\t\t [ Y / N ] : ";
	cin >> choice;
	if (choice == "Y" || choice == "y")
	{
		string searchAvailable_query = "UPDATE blooddonated NATURAL JOIN donor SET workerid = 'DELETED' where workerid = '" + workerid3 + "' and STATUS ='available'";
		const char* sA = searchAvailable_query.c_str();
		qstate = mysql_query(conn, sA);

		string editDonor_query = "UPDATE donor SET workerid = 'DELETED' where workerid = '" + workerid3 + "'";
		const char* eD = editDonor_query.c_str();
		qstate2 = mysql_query(conn, eD);
		if (!qstate && !qstate2)
		{

			string DeleteWorker_query = "DELETE FROM worker where workerid = '" + workerid3 + "'";
			const char* dW = DeleteWorker_query.c_str();
			valid2 = mysql_query(conn, dW);
			if (!valid2)
			{
				string DeleteLogin_query = "DELETE FROM LOGINDETAIL where accountid = '" + accountid + "'";
				const char* dL = DeleteLogin_query.c_str();
				qstate2 = mysql_query(conn, dL);
				if (!qstate2)
				{
					system("cls");
					cout << "\n\n\t\t______________________________________________________________________________________________________";
					cout << "\n\n\n\t\t\t\tUpdate Successfull !\n\n\n";
					cout << "\t\t______________________________________________________________________________________________________\n\n";
					system("pause");
					HandleWorkerMenu();
				}
				else
				{
					system("cls");
					cout << "\n\n\t\t\t\tERROR IN EXECUTION 1 " << mysql_errno(conn);
					system("pause");
					HandleWorkerMenu();
				}
			}
			else
			{
				system("cls");
				cout << "\n\n\t\t\t\tERROR IN EXECUTION 2 " << mysql_errno(conn);
				system("pause");
				HandleWorkerMenu();
			}
		}
	}
	else
	{
		AdminHandleDonorMenu();
	}
}


/////////////////// DONOR //////////////////
//done
void addDonor(int guide)
{
DonorGate1:
	int counter;
	string DonorID, name, IDCard, BloodType, WorkerID, PPDID, ContactNumber, choice1, donatedid, adminid, numberdonor, numberdonated;
	string status = "notTested";
	system("CLS");
	cout << "\n\n\t\t****************************************************************************************************\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t*\t\t\t\t        DONOR REGISTER MENU\t\t\t\t           *\n";
	cout << "\t\t*                                                                                                  *\n";
	cout << "\t\t****************************************************************************************************\n";
	cout << "\t\t" << date_time << "\n\n";
	cin.ignore();
	cout << "\t\tEnter \"0\" To Go Back\n";
	try
	{
		cout << "\t\tEnter Donor's Name : ";
		getline(cin, name);
		if (name == "cancel" || name == "0")
		{
			if (guide == 1) { throw 1; }
			else if (guide == 2) { throw 2; }
		}
	}
	catch (int e)
	{
		if (name == "cancel" || name == "0")
		{
			if (e == 1) { AdminHandleDonorMenu(); }
			else if (e == 2) { WorkerMenu(); }
		}
	}
	counter = 0;
	while (counter < name.length())
	{
		if (isupper(name[counter]))
		{
			name[counter] = tolower(name[counter]);
		}
		counter++;
	}
	cin.ignore();
EnterIDCard:
	cout << "\t\tEnter Donor's Identification Card Number : ";
	getline(cin, IDCard);
	counter = 0;
	while (counter < IDCard.length())
	{
		if (isupper(IDCard[counter]))
		{
			IDCard[counter] = tolower(IDCard[counter]);
		}
		counter++;
	}
	if (IDCard == "cancel" || IDCard == "0")
	{
		if (guide == 1) { AdminHandleDonorMenu(); }
		if (guide == 2) { WorkerMenu(); }
	}
	if (IDCard.length() < 12)
	{
		cout << "\n\t\t\t\t\t\t\t\t\tIdentification Card Not Valid\n\n";
		goto EnterIDCard;
	}
	string CheckPPD_query = "select * from donor where IDCardNumber = '" + IDCard + "' limit 1";
	const char* cD = CheckPPD_query.c_str();
	valid = mysql_query(conn, cD);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1)
		{
			cout << "Identification Card ALREADY EXIST !";
			goto EnterIDCard;
		}
		else
		{
			bool bloodtypebool = false;
			do
			{
				cin.ignore();
				cout << "\t\tEnter Donor's Blood Type : ";
				getline(cin, BloodType);
				counter = 0;
				while (counter < BloodType.length())
				{
					if (isupper(BloodType[counter]))
					{
						BloodType[counter] = tolower(BloodType[counter]);
					}
					counter++;
				}
				if (BloodType == "cancel")
				{
					if (guide == 1) { AdminHandleDonorMenu(); }
					if (guide == 2) { WorkerMenu(); }
				}
				if (BloodType == "a+" || BloodType == "b+" || BloodType == "ab+" || BloodType == "o+" || BloodType == "a-" || BloodType == "b-" || BloodType == "ab-" || BloodType == "o-")
				{
					bloodtypebool = true;
				}
				if (bloodtypebool == false)
				{
					cout << "\n\t\t\t\t\t\tBLOOD TYPE INVALID !\n";
				}
			} while (bloodtypebool == false);
			cin.ignore();
			cout << "\t\tEnter Donor's Contact Number : ";
			getline(cin, ContactNumber);
			if (ContactNumber == "cancel")
			{
				if (guide == 1)
				{
					AdminHandleDonorMenu();
				}
				if (guide == 2)
				{
					WorkerMenu();
				}
			}
			if (ContactNumber == "CANCEL" || ContactNumber == "0")
			{
				if (guide == 1)
				{
					AdminHandleDonorMenu();
				}
				if (guide == 2)
				{
					WorkerMenu();
				}
			}
		PPDGate:
			cin.ignore();
			cout << "\t\tEnter Pusat Derma Darah ID : ";
			getline(cin, PPDID);
			counter = 0;
			while (counter < PPDID.length())
			{
				if (islower(PPDID[counter]))
				{
					PPDID[counter] = toupper(PPDID[counter]);
				}
				counter++;
			}
			if (PPDID == "CANCEL" || PPDID == "0")
			{
				if (guide == 1)
				{
					AdminHandleDonorMenu();
				}
				if (guide == 2)
				{
					WorkerMenu();
				}
			}
			string CheckPPD_query = "select * from pusatdermadarah where PPDID = '" + PPDID + "' limit 1";
			const char* cD = CheckPPD_query.c_str();
			valid = mysql_query(conn, cD);
			if (!valid)
			{
				result = mysql_store_result(conn);
				if (result->row_count == 1)
				{
					if (guide == 1)
					{
						adminid = id;
						string insertA_query = "INSERT INTO Donor (Name, ContactNumber, BloodType, IDCardNumber, adminID, PPDID) VALUES ('" + name + "', '" + ContactNumber + "', '" + BloodType + "', '" + IDCard + "', '" + adminid + "', '" + PPDID + "')";
						const char* InsQA = insertA_query.c_str();
						qstate = mysql_query(conn, InsQA);
					}
					if (guide == 2)
					{
						WorkerID = id;
						string insertA_query = "INSERT INTO Donor (Name, ContactNumber, BloodType, IDCardNumber, workerid, PPDID) VALUES ('" + name + "', '" + ContactNumber + "', '" + BloodType + "', '" + IDCard + "', '" + WorkerID + "', '" + PPDID + "')";
						const char* InsQA = insertA_query.c_str();
						qstate = mysql_query(conn, InsQA);
					}
					if (!qstate)
					{
						string searchD = "SELECT * FROM Donor WHERE IDCardNumber = '" + IDCard + "'";
						const char* sD = searchD.c_str();
						qstate2 = mysql_query(conn, sD);
						if (!qstate2)
						{
							result = mysql_store_result(conn);
							while (row = mysql_fetch_row(result))
							{
								numberdonor = row[0];
							}
						}
						else
						{
							cout << "\t\t\t\tInsertion Problem SEARCH ID CARD :: " << mysql_errno(conn) << endl;
							cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
							cin.ignore();
							cin >> choice1;
							if (choice1 == "Y" || choice1 == "y")
							{
								system("cls");
								goto DonorGate1;
							}
							else
							{
								system("cls");
								if (guide == 1)
								{
									WorkerMenu();
								}
								if (guide == 2)
								{
									AdminHandle();
								}
							}
						}
						DonorID = "d";
						DonorID = DonorID + numberdonor;
						string updatedonor = "UPDATE donor SET number='" + numberdonor + "' , donorid='" + DonorID + "' WHERE IDCardNumber = '" + IDCard + "'";
						const char* Ud = updatedonor.c_str();
						valid2 = mysql_query(conn, Ud);
						if (!valid2)
						{
							if (guide == 1)
							{
								string insertBloodDonated_query = "INSERT INTO BLOODDONATED (status, bloodtype, donorid, AdminID) VALUES ('" + status + "','" + BloodType + "','" + DonorID + "', '" + adminid + "')";
								const char* cBD = insertBloodDonated_query.c_str();
								valid = mysql_query(conn, cBD);
							}
							if (guide == 2)
							{
								string insertBloodDonated_query = "INSERT INTO BLOODDONATED (status, bloodtype, donorid, WorkerID) VALUES ('" + status + "','" + BloodType + "','" + DonorID + "', '" + WorkerID + "')";
								const char* cBD = insertBloodDonated_query.c_str();
								valid = mysql_query(conn, cBD);
							}
							if (!valid)
							{
								string searchD = "SELECT * FROM BLOODDONATED WHERE Donorid = '" + DonorID + "'";
								const char* sD = searchD.c_str();
								qstate2 = mysql_query(conn, sD);
								if (!qstate2)
								{
									result = mysql_store_result(conn);
									while (row = mysql_fetch_row(result))
									{
										numberdonated = row[0];
									}
								}
								else
								{
									cout << "\t\t\t\tInsertion Problem 1B :: " << mysql_errno(conn) << endl;
									cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
									cin.ignore();
									cin >> choice1;
									if (choice1 == "Y" || choice1 == "y")
									{
										system("cls");
										goto DonorGate1;
									}
									else
									{
										system("cls");
										if (guide == 1)
										{
											WorkerMenu();
										}
										if (guide == 2)
										{
											AdminHandle();
										}
									}
								}
								donatedid = "bd";
								donatedid = donatedid + numberdonated;
								string updateBloodDonated = "UPDATE BLOODDONATED SET number='" + numberdonated + "' , donatedid='" + donatedid + "' WHERE Donorid = '" + DonorID + "'";
								const char* UBD = updateBloodDonated.c_str();
								valid2 = mysql_query(conn, UBD);
								if (!valid2)
								{
									string getdonor = "SELECT * FROM donor WHERE donorid = '" + DonorID + "'";
									const char* GD = getdonor.c_str();
									valid = mysql_query(conn, GD);
									if (!valid)
									{
										result = mysql_store_result(conn);
										while (row = mysql_fetch_row(result))
										{
											cout << "\n\n\n\t\t______________________________________________________________________________________________________\n";
											cout << "\n\n\t\t\t\t\tDonor Registration Success! \n\n";
											cout << "\t\t______________________________________________________________________________________________________\n";
											cout << "\n\t\t\t\t\tBlood Donated ID: " << donatedid;
											cout << "\n\t\t\t\t\tDonorID: " << row[1];
											cout << "\n\t\t\t\t\tName: " << row[2];
											cout << "\n\t\t\t\t\tContact Number: " << row[3];
											cout << "\n\t\t\t\t\tBlood Type: " << row[4];
											cout << "\n\t\t\t\t\tIDCardNumber: " << row[5];
											cout << "\n";
										}
										system("PAUSE");
										system("CLS");
										if (guide == 1)
										{
											addDonor(1);
										}
										if (guide == 2)
										{
											addDonor(2);
										}
									}
									else
									{
										cout << "\t\t\t\tInsertion Problem 2 :: " << mysql_errno(conn) << endl;
										cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
										cin.ignore();
										cin >> choice1;
										if (choice1 == "Y" || choice1 == "y")
										{
											system("cls");
											goto DonorGate1;
										}
										else
										{
											system("cls");
											if (guide == 1)
											{
												WorkerMenu();
											}
											if (guide == 2)
											{
												AdminHandle();
											}
										}
									}
								}
								else
								{
									cout << "\t\t\t\tInsertion Problem 3 :: " << mysql_errno(conn) << endl;
									cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
									cin.ignore();
									cin >> choice1;
									if (choice1 == "Y" || choice1 == "y")
									{
										system("cls");
										goto DonorGate1;
									}
									else
									{
										system("cls");
										if (guide == 1)
										{
											WorkerMenu();
										}
										if (guide == 2)
										{
											AdminHandle();
										}
									}
								}
							}
							else
							{
								cout << "\t\t\t\tInsertion Problem 4 :: " << mysql_errno(conn) << endl;
								cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
								cin.ignore();
								cin >> choice1;
								if (choice1 == "Y" || choice1 == "y")
								{
									system("cls");
									goto DonorGate1;
								}
								else
								{
									system("cls");
									if (guide == 1)
									{
										WorkerMenu();
									}
									if (guide == 2)
									{
										AdminHandle();
									}
								}
							}
						}
						else
						{
							cout << "\t\t\t\tInsertion Problem 5 :: " << mysql_errno(conn) << endl;
							cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
							cin.ignore();
							cin >> choice1;
							if (choice1 == "Y" || choice1 == "y")
							{
								system("cls");
								goto DonorGate1;
							}
							else
							{
								system("cls");
								if (guide == 1)
								{
									WorkerMenu();
								}
								if (guide == 2)
								{
									AdminHandle();
								}
							}
						}
					}
					else
					{
						cout << "\t\t\t\tInsertion Problem 6 :: " << mysql_errno(conn) << endl;
						cout << "\t\t\t\tDo You Wanna Try Again ? (Y or N)\n";
						cin.ignore();
						cin >> choice1;
						if (choice1 == "Y" || choice1 == "y")
						{
							system("cls");
							goto DonorGate1;
						}
						else
						{
							system("cls");
							if (guide == 1)
							{
								WorkerMenu();
							}
							if (guide == 2)
							{
								AdminHandle();
							}
						}
					}
				}
				else
				{
					cout << "\t\t\t\tPPDID DOES NOT EXIST";
					goto PPDGate;
				}

			}
			else
			{
				cout << "\t\t\t\tPPDID DOES NOT EXIST";
				goto PPDGate;
			}
		}
	}

}

//DONE
void SearchDonor(int guide, int guide2)
{
	system("CLS");
	string DonorID, choice2, blooddonatedid;
	int choice1;
	if (guide2 == 2)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t         SEARCH DONOR MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	else if (guide2 == 3)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t         MODIFY DONOR MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	else if (guide2 == 4)
	{
		cout << "\n\n\t\t****************************************************************************************************\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t           *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t*\t\t\t\t         DELETE DONOR MENU\t\t\t                   *\n";
		cout << "\t\t*                                                                                                  *\n";
		cout << "\t\t****************************************************************************************************\n";
	}
	cout << "\t\t" << date_time << "\n\n";
	cout << "\t\tEnter \"0\" To Go Back\n";
	cout << "\t\tDonorID : ";
	cin.ignore();
	cin >> DonorID;
	int counter = 0;
	while (counter < DonorID.length())
	{
		if (isupper(DonorID[counter]))
		{
			DonorID[counter] = tolower(DonorID[counter]);
		}
		counter++;
	}
	if (DonorID == "0")
	{
		if (guide == 1)
		{
			AdminHandleDonorMenu();
		}
		if (guide == 2)
		{
			WorkerMenu();
		}
	}
	string searchBlood_query = "select * from blooddonated where DONORID = '" + DonorID + "' limit 1";
	const char* sB = searchBlood_query.c_str();
	qstate = mysql_query(conn, sB);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				blooddonatedid = row[1];
			}
		}
		if (result->row_count == 0) //if result 0 or does not found
		{
			cout << "\n\n\t\t\t\t Donor Does Not Exist ! \n";
			system("PAUSE");
			if (guide == 1)
			{
				SearchDonor(1, 2);
			}
			if (guide == 2)
			{
				SearchDonor(2, 2);
			}
		}
	}
	string searchDonor_query = "select * from donor where DONORID = '" + DonorID + "' limit 1";
	const char* sD = searchDonor_query.c_str();
	qstate = mysql_query(conn, sD);
	bool exist = false;
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			cout << "\n\n\t\t\t\t\t\t    Donor Exist!\n";
			cout << "\t\t######################################################################################################\n";
			cout << "\t\t#                                                                                                    \n";
			while (row = mysql_fetch_row(result))
			{
				cout << "\t\t#\t\t\tDonor ID :" << row[1] << "\n";
				cout << "\t\t#\t\t\tBlood Donated ID : " << blooddonatedid << endl;
				cout << "\t\t#\t\t\tName :" << row[2] << "\n";
				cout << "\t\t#\t\t\tContact Number :" << row[3] << "\n";
				cout << "\t\t#\t\t\tBloodType :" << row[4] << "\n";
				cout << "\t\t#\t\t\tIdentification Card :" << row[5] << "\n";
				if (row[6] == NULL)
				{
					cout << "\t\t#\t\t\tAdmin ID : " << row[7] << "\n";
				}
				else
				{
					cout << "\t\t#\t\t\tWorker ID :" << row[6] << "\n";

				}
				cout << "\t\t#\t\t\tPPDID :" << row[8] << "\n";
				cout << "\t\t#                                                                                                    \n";
				cout << "\t\t######################################################################################################\n\n";
				if (guide2 == 2)
				{
					if (guide == 1)
					{
						system("pause");
						AdminHandleDonorMenu();
					}
					if (guide == 2)
					{
						system("pause");
						WorkerMenu();
					}
				}
				if (guide2 == 3)
				{
					if (guide == 1)
					{
						ModifyDonor(DonorID, 1);
					}
					if (guide == 2)
					{
						ModifyDonor(DonorID, 2);
					}
				}
				if (guide2 == 4)
				{
					deleteDonor(DonorID);
				}
			}
		}
		if (result->row_count == 0) //if result 0 or does not found
		{
			cout << "\n\n\t\t\t\t Donor Does Not Exist ! \n";
			system("PAUSE");
			if (guide == 1)
			{
				SearchDonor(1, 2);
			}
			if (guide == 2)
			{
				SearchDonor(2, 2);
			}
		}
	}
}

//DONE
void ModifyDonor(string donorid2, int guide)
{
	string name, contactnumber, bloodtype, idcardnumber, workerid;
	int counter;
	cout << "\n\t\t______________________________________________________________________________________________________";
	cout << "\n\t\t\t\t\t\tPlease Enter New Data For Donor : " << donorid2;
	cout << "\n\t\t______________________________________________________________________________________________________\n";
	cout << "\t\t" << date_time << "\n\n";
	cout << "\t\tEnter \"0\" To Go Back\n";
	cout << "\t\t Enter Name : ";
	cin.ignore();
	getline(cin, name);
	counter = 0;
	while (counter < name.length())
	{
		if (isupper(name[counter]))
		{
			name[counter] = tolower(name[counter]);
		}
		counter++;
	}
	if (name == "cancel" || name == "0")
	{
		if (guide == 1)
		{
			SearchDonor(1, 2);
		}
		if (guide == 2)
		{
			SearchDonor(2, 2);
		}
	}
	cin.ignore();
	cout << "\t\t Enter Contact Number : ";
	getline(cin, contactnumber);
	counter = 0;
	while (counter < contactnumber.length())
	{
		if (isupper(contactnumber[counter]))
		{
			contactnumber[counter] = tolower(contactnumber[counter]);
		}
		counter++;
	}
	if (contactnumber == "cancel" && guide == 1)
	{
		AdminHandleDonorMenu();
	}
	if (contactnumber == "0" && guide == 1)
	{
		AdminHandleDonorMenu();
	}
	if (contactnumber == "cancel" && guide == 2)
	{
		WorkerMenu();
	}
	if (contactnumber == "0" && guide == 2)
	{
		WorkerMenu();
	}
	cin.ignore();
	EnterIDCard:
	cout << "\t\t Enter Identification Card Number : ";
	getline(cin, idcardnumber);
	counter = 0;
	while (counter < idcardnumber.length())
	{
		if (isupper(idcardnumber[counter]))
		{
			idcardnumber[counter] = tolower(idcardnumber[counter]);
		}
		counter++;
	}
	if (idcardnumber == "cancel" && guide == 1)
	{
		AdminHandleDonorMenu();
	}
	if (idcardnumber == "0" && guide == 1)
	{
		AdminHandleDonorMenu();
	}
	if (idcardnumber == "cancel" && guide == 2)
	{
		WorkerMenu();
	}
	if (idcardnumber == "cancel" && guide == 2)
	{
		WorkerMenu();
	}
	if (idcardnumber.length() < 12)
	{
		cout << "\n\t\t\t\t\t\t\t\t\tIdentification Card Not Valid\n\n";
		goto EnterIDCard;
	}
	string updateDonor_query = "UPDATE donor SET Name ='" + name + "', ContactNumber ='" + contactnumber + "', IDCardNumber ='" + idcardnumber + "' WHERE DonorID = '" + donorid2 + "'";
	const char* uD = updateDonor_query.c_str();
	qstate = mysql_query(conn, uD);
	if (!qstate)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\tUpdate Successfull !";
		system("pause");
		if (guide == 1)
		{
			SearchDonor(1, 2);
		}
		if (guide == 2)
		{
			SearchDonor(2, 2);
		}
	}
	else
	{
		system("cls");
		cout << "\n\n\t\t\t\tERROR IN EXECUTION 1 " << mysql_errno(conn);
		system("pause");
		if (guide == 1)
		{
			SearchDonor(1, 2);
		}
		if (guide == 2)
		{
			SearchDonor(2, 2);
		}
	}
}

//DONE
void deleteDonor(string donorid)
{
	string choice;
	cout << "\n\n\t\t\t\t ARE YOU SURE WANT TO DELETE DATA OF USER " << donorid << " ?  \n\t\t\t\t Once It is Deleted It Cannot Be Retrieve Again ";
	cout << "\n\t\t\t\t [ Y / N ] : ";
	cin >> choice;
	if (choice == "Y" || choice == "y")
	{
		string DeleteBloodDonated_query = "DELETE FROM blooddonated where DONORID = '" + donorid + "'";
		const char* dBD = DeleteBloodDonated_query.c_str();
		valid = mysql_query(conn, dBD);

		string DeleteDonor_query = "DELETE FROM donor where DONORID = '" + donorid + "'";
		const char* dD = DeleteDonor_query.c_str();
		valid2 = mysql_query(conn, dD);

		if (!valid && !valid2)
		{
			system("cls");
			cout << "\n\n\t\t______________________________________________________________________________________________________";
			cout << "\n\n\n\t\t\t\tUpdate Successfull !\n\n\n";
			cout << "\t\t______________________________________________________________________________________________________\n\n";

			system("pause");
			AdminHandleDonorMenu();
		}
		else
		{
			system("cls");
			cout << "\n\n\t\t\t\tERROR IN EXECUTION 1 " << mysql_errno(conn);
			system("pause");
			AdminHandleDonorMenu();
		}
	}
	else
	{

		AdminHandleDonorMenu();
	}

}


///////////////////////////// BLOOD ////////////////////////////

//DONE 
void HandleBlood(int guide)
{
main:
	system("CLS");
	string option1;
	cout << "\n\t\t######################################################################################################\n";
	cout << "\t\t#                                                                                                    #\n";
	cout << "\t\t#\t\t\t\t    BLOOD BANK MANAGEMENT SYSTEM\t\t\t\t     #\n";
	cout << "\t\t#                                                                                                    #";
	cout << "\n\t\t######################################################################################################\n\n\n";

	cout << "\t\t______________________________________________________________________________________________________\n";
	cout << "\t\t|                                                                                                    |\n";
	cout << "\t\t|\t\t\t\t          BLOOD DATA MENU\t\t\t\t             |\n";
	cout << "\t\t|____________________________________________________________________________________________________|\n";
	cout << "\t\t|                                                                                                    |\n";
	cout << "\t\t|\t\t1) Blood Donated Analysis\t\t\t\t\t\t\t     |\n"; //guide 2nd parameter== 1
	cout << "\t\t|\t\t2) View Blood Donated Detail \t\t\t\t\t\t\t     |\n"; // guide 2nd parameter== 4
	cout << "\t\t|\t\t3) Update Blood Donated Status To Testing\t\t\t\t\t     |\n"; //guide 2nd parameter == 5
	cout << "\t\t|\t\t4) Update Blood Donated Status To Having Disorder\t\t\t\t     |\n"; //guide 2nd parameter  == 6
	cout << "\t\t|\t\t5) Update Blood Donated Status To Stock\t\t\t\t\t\t     |\n"; //guide 2nd parameter == 7
	cout << "\t\t|\t\t6) Analysis Blood Stock Available\t\t\t\t\t\t     |\n";
	if (guide == 1)
	{
		cout << "\t\t|____________________________________________________________________________________________________|\n";
		cout << "\t\t|                                                                                                    |\n";
		cout << "\t\t|\t\t7) Adjust Blood Stock\t\t\t\t\t\t\t\t     |\n";
		cout << "\t\t|\t\t8) Adjust Blood Status & Disorder Type\t\t\t\t\t\t     |\n";
		cout << "\t\t|\t\t9) Remove Blood Donated \t\t\t\t\t\t\t     |\n";
	}
	cout << "\t\t|____________________________________________________________________________________________________|\n\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\t\t\t\tEnter \"0\" To Go Back\n";
	cout << "\t\t\t\t\tChoose : ";
	cin >> option1;
	try
	{
		if (option1 == "1")
		{
			if (guide == 1)
			{
				viewBloodDonatedSTOCK(1);
			}
			if (guide == 2)
			{
				viewBloodDonatedSTOCK(2);
			}
		}
		else if (option1 == "2")
		{
			if (guide == 1)
			{
				viewBloodDetail(1);
			}
			if (guide == 2)
			{
				viewBloodDetail(2);
			}
		}
		else if (option1 == "3")
		{
			if (guide == 1)
			{
				UpdateBlood(1, 5);
			}
			if (guide == 2)
			{
				UpdateBlood(2, 5);
			}
		}
		else if (option1 == "4")
		{
			if (guide == 1)
			{
				UpdateBlood(1, 6);
			}
			if (guide == 2)
			{
				UpdateBlood(2, 6);
			}
		}
		else if (option1 == "5")
		{
			if (guide == 1)
			{
				UpdateBlood(1, 7);
			}
			if (guide == 2)
			{
				UpdateBlood(2, 7);
			}
		}
		else if (option1 == "6")
		{
			if (guide == 1)
			{
				viewBloodSTOCK(1);
			}
			if (guide == 2)
			{
				viewBloodSTOCK(2);
			}
		}
		else if (option1 == "7" && guide == 1)
		{
			AdjustBloodStock();
		}
		else if (option1 == "8" && guide == 1)
		{
			AdjustBloodStatus();
		}
		else if (option1 == "9" && guide == 1)
		{
			RemoveBloodDonated();
		}
		else if (option1 == "0")
		{
			if (guide == 1)
			{
				AdminHandle();
			}
			if (guide == 2)
			{
				WorkerMenu();
			}
		}
		else
		{
			throw 99;
		}
	}
	catch (int x) {
		goto main;
	}
}

//DONE
void viewBloodDonatedSTOCK(int guide6)
{
	string Choice, Choice1;
	double bloodannt , bloodbnnt , bloodabnnt , bloodonnt , bloodapnt , bloodbpnt , bloodabpnt , bloodopnt ;  //Blood Not Tested
	double bloodant , bloodbnt , bloodabnt , bloodont , bloodapt , bloodbpt , bloodabpt , bloodopt ; //Blood testing
	double bloodantd , bloodbntd , bloodabntd , bloodontd , bloodaptd , bloodbptd , bloodabptd , bloodoptd ; //Blood Tested
	double totalnt , totalt , totaltd ;

	system("cls");
	cout << "\n\n\t\t\t\t#########################################################################################################################################";
	cout << "\n\t\t\t\t                                                      BLOOD BANK MANAGEMENT SYSTEM                                                         ";
	cout << "\n\n\t\t\t\t#########################################################################################################################################";

	cout << "\n\n\t\t\t\t\t\t\t\t\t\t      BLOOD DONATED ANALYSIS MENU";
	cout << "\n\t\t\t\t                            _____________________________________________________________________________________________________________\n";
	cout << "\t\t\t\t                            |                                   QUANTITY OF EACH PHASE (PINT)                        |                  |\n";
	cout << "\t\t\t\t____________________________|________________________________________________________________________________________|       TOTAL      |\n";
	cout << "\t\t\t\t|          BloodType        |           NOT TESTED          |           TESTING          |           TESTED          |                  |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	//////////////////A-
	string searchANNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'a-'";
	const char* sANNTB = searchANNTBlood_query.c_str();
	valid = mysql_query(conn, sANNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodannt = stod(row[0]);
		}
	}
	string searchANTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'a-'";
	const char* sANTB = searchANTBlood_query.c_str();
	valid = mysql_query(conn, sANTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodant = stod(row[0]);
		}
	}
	string searchANTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'a-'";
	const char* sANTDB = searchANTDBlood_query.c_str();
	valid = mysql_query(conn, sANTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodantd = stod(row[0]);
		}
	}


	/////////////////////////////////////////////////////////////////B-
	string searchBNNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'b-'";
	const char* sBNNTB = searchBNNTBlood_query.c_str();
	valid = mysql_query(conn, sBNNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbnnt = stod(row[0]);
		}
	}
	string searchBNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'b-'";
	const char* sBNTB = searchBNTBlood_query.c_str();
	valid = mysql_query(conn, sBNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbnt = stod(row[0]);
		}
	}
	string searchBNTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'b-'";
	const char* sBNTDB = searchBNTDBlood_query.c_str();
	valid = mysql_query(conn, sBNTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbntd = stod(row[0]);
		}
	}
	

	//////////////////////////////////////////////////AB-
	string searchABNNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'ab-'";
	const char* sABNNTB = searchABNNTBlood_query.c_str();
	valid = mysql_query(conn, sABNNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabnnt = stod(row[0]);
		}
	}
	string searchABNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'ab-'";
	const char* sABNTB = searchABNTBlood_query.c_str();
	valid = mysql_query(conn, sABNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabnt = stod(row[0]);
		}
	}
	string searchABNTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'ab-'";
	const char* sABNTDB = searchABNTDBlood_query.c_str();
	valid = mysql_query(conn, sABNTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabntd = stod(row[0]);
		}
	}

	////////////////////////////////////O-
	string searchONNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'o-'";
	const char* sONNTB = searchONNTBlood_query.c_str();
	valid = mysql_query(conn, sONNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodonnt = stod(row[0]);
		}
	}
	string searchONTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'o-'";
	const char* sONTB = searchONTBlood_query.c_str();
	valid = mysql_query(conn, sONTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodont = stod(row[0]);
		}
	}
	string searchONTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'o-'";
	const char* sONTDB = searchONTDBlood_query.c_str();
	valid = mysql_query(conn, sONTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodontd = stod(row[0]);
		}
	}


	////////////////////////////////A+
	string searchAPNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'a+'";
	const char* sAPNTB = searchAPNTBlood_query.c_str();
	valid = mysql_query(conn, sAPNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodapnt = stod(row[0]);
		}
	}
	string searchAPTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'a+'";
	const char* sAPTB = searchAPTBlood_query.c_str();
	valid = mysql_query(conn, sAPTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodapt = stod(row[0]);
		}
	}
	string searchAPTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'a+'";
	const char* sAPTDB = searchAPTDBlood_query.c_str();
	valid = mysql_query(conn, sAPTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodaptd = stod(row[0]);
		}
	}

	//////////////////////////////B+
	string searchBPNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'b+'";
	const char* sBPNTB = searchBPNTBlood_query.c_str();
	valid = mysql_query(conn, sBPNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbpnt = stod(row[0]);
		}
	}
	string searchBPTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'b+'";
	const char* sBPTB = searchBPTBlood_query.c_str();
	valid = mysql_query(conn, sBPTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbpt = stod(row[0]);
		}
	}
	string searchBPTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'b+'";
	const char* sBPTDB = searchBPTDBlood_query.c_str();
	valid = mysql_query(conn, sBPTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbptd = stod(row[0]);
		}
	}

	///////////////////////////AB+

	string searchABPNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'ab+'";
	const char* sABPNTB = searchABPNTBlood_query.c_str();
	valid = mysql_query(conn, sABPNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabpnt = stod(row[0]);
		}
	}
	string searchABPTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'ab+'";
	const char* sABPTB = searchABPTBlood_query.c_str();
	valid = mysql_query(conn, sABPTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabpt = stod(row[0]);
		}
	}
	string searchABPTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'ab+'";
	const char* sABPTDB = searchABPTDBlood_query.c_str();
	valid = mysql_query(conn, sABPTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabptd = stod(row[0]);
		}
	}


	/////////////////////////////O+
	string searchOPNTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'notTested' AND BloodType = 'o+'";
	const char* sOPNTB = searchOPNTBlood_query.c_str();
	valid = mysql_query(conn, sOPNTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodopnt = stod(row[0]);
		}
	}

	string searchOPTBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Testing' AND BloodType = 'o+'";
	const char* sOPTB = searchOPTBlood_query.c_str();
	valid = mysql_query(conn, sOPTB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodopt = stod(row[0]);
		}
	}

	string searchOPTDBlood_query = "SELECT COUNT(*) FROM `blooddonated` WHERE Status = 'Tested' AND BloodType = 'o+'";
	const char* sOPTDB = searchOPTDBlood_query.c_str();
	valid = mysql_query(conn, sOPTDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodoptd = stod(row[0]);
		}
	}

	totalnt = bloodannt + bloodbnnt + bloodabnnt + bloodonnt + bloodapnt + bloodbpnt + bloodabpnt + bloodopnt;
	totalt = bloodant + bloodbnt + bloodabnt + bloodont + bloodapt + bloodbpt + bloodabpt + bloodopt;
	totaltd = bloodantd + bloodbntd + bloodabntd + bloodontd + bloodaptd + bloodbptd + bloodabptd + bloodoptd;

	//total
	int totalall = totalnt + totalt + totaltd;
	int totalan, totalbn, totalabn, totalon, totalap, totalbp, totalabp, totalop;

	//negative
	totalan = bloodannt + bloodant + bloodantd;
	totalbn = bloodbnnt + bloodbnt + bloodbntd;
	totalabn = bloodabnnt + bloodabnt + bloodabntd;
	totalon = bloodonnt + bloodont + bloodontd;

	//positive
	totalap = bloodapnt + bloodapt + bloodaptd;
	totalbp = bloodbpnt + bloodbpt + bloodbptd;
	totalabp = bloodabpnt + bloodabpt + bloodabptd;
	totalop = bloodopnt + bloodopt + bloodoptd;


	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           A-              |               " << bloodannt << "               |              " << bloodant << "             |             " << bloodantd << "             |         " << totalan << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           B-              |               " << bloodbnnt << "               |              " << bloodbnt << "             |             " << bloodbntd << "             |         " << totalbn << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           AB-             |               " << bloodabnnt << "               |              " << bloodabnt << "             |             " << bloodabntd << "             |         " << totalabn << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           O-              |               " << bloodonnt << "               |              " << bloodont << "             |             " << bloodontd << "             |         " << totalon << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           A+              |               " << bloodapnt << "               |              " << bloodapt << "             |             " << bloodaptd << "             |         " << totalap << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           B+              |               " << bloodbpnt << "               |              " << bloodbpt << "             |             " << bloodbptd << "             |         " << totalbp << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           AB+             |               " << bloodabpnt << "               |              " << bloodabpt << "             |             " << bloodabptd << "             |         " << totalabp << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|                           |                               |                            |                           |                  |\n";
	cout << "\t\t\t\t|           O+              |               " << bloodopnt << "               |              " << bloodont << "             |             " << bloodontd << "             |         " << totalop << "        |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t|          TOTAL            |              " << totalnt << "               |              " << totalt << "             |              " << totaltd << "            |         " << totalall << "       |\n";
	cout << "\t\t\t\t|___________________________|_______________________________|____________________________|___________________________|__________________|\n";
	cout << "\t\t\t\t" << date_time << "\n\n";
	if (guide6 == 1)
	{
		system("PAUSE");
		system("CLS");
		HandleBlood(1);
	}
	if (guide6 == 2)
	{
		system("PAUSE");
		system("CLS");
		HandleBlood(2);
	}
}

//DONE
void viewBloodDetail(int guide)
{
	system("cls");
	string disorder;
	string searchBloodDonated_query = "SELECT * FROM `blooddonated` ORDER BY number ASC";
	const char* sBD = searchBloodDonated_query.c_str();
	valid = mysql_query(conn, sBD);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count >= 1)
		{
			cout << "\t\t#####################################################################################################\n";
			cout << "\t\t#\t\t\t                 BLOOD BANK MANAGEMENT SYSTEM                               #\n";
			cout << "\t\t#\t\t\t                                                                            #\n";
			cout << "\t\t#\t\t\t                                                                            #\n";
			cout << "\t\t#\t\t\t                   BLOOD DONATED DETAIL MENU                                #\n";
			cout << "\t\t#####################################################################################################\n";


			cout << "\n\t\t________________________________________________________________________________________________________" << endl;
			cout << "\n\t\t|      BloodDonated ID      |        DateIN          |     Blood Type     |     Blood Disorder Type     |";
			cout << "\n\t\t|___________________________|________________________|____________________|_____________________________|\n";
			while (row = mysql_fetch_row(result))
			{
				if (row[8] == NULL)
				{
					disorder = "NULL";
				}
				else {
					disorder = row[8];
				}
				cout << "\t\t_________________________________________________________________________________________________________\n";
				cout << "\t\t                                                                                                         \n";
				cout << "\t\t            " << row[1] << "                    " << row[3] << "                  " << row[4] << "                   " << disorder << "              \n";
			}
			cout << "\t\t_________________________________________________________________________________________________________\n";
			cout << "\t\t" << date_time << "\n\n";
			if (guide == 1)
			{
				system("PAUSE");
				system("CLS");
				HandleBlood(1);
			}
			if (guide == 2)
			{
				system("PAUSE");
				system("CLS");
				HandleBlood(2);
			}
		}
		if (result->row_count == 0)
		{
			cout << "\n\t\t\t NO BLOOD DONATED AVAILABLE\n";
			system("pause");
			if (guide == 1)
			{
				system("PAUSE");
				system("CLS");
				AdminHandle();
			}
			if (guide == 2)
			{
				system("PAUSE");
				system("CLS");
				WorkerMenu();
			}
		}
	}
}

//DONE
void viewBloodSTOCK(int guide)
{
	system("cls");
	string choice;
	double bloodan, bloodbn, bloodabn, bloodon, bloodap, bloodbp, bloodabp, bloodop, total;
	double bloodanper, bloodbnper, bloodabnper, bloodonper, bloodapper, bloodbpper, bloodabpper, bloodopper;
	cout << "\n\n\t\t\t\t########################################################################################################\n";
	cout << "\n\n\t\t\t\t                                        BLOOD BANK MANAGEMENT SYSTEM";
	cout << "\n\n\t\t\t\t########################################################################################################\n";
	cout << "\n\n\t\t\t\t                                          BLOOD STOCK ANALYSIS MENU";
	cout << "\n\n\t\t\t\t_______________________________________________________________________________________________________________\n";
	cout << "\t\t\t\t|           BloodType             |                Quantity             |                PERCENTAGE           |\n";

	string searchANanBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'a-' ";
	const char* sANanB = searchANanBlood_query.c_str();
	valid = mysql_query(conn, sANanB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodan = stod(row[1]);
		}
	}

	string searchANbnBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'b-' ";
	const char* sANbnB = searchANbnBlood_query.c_str();
	valid = mysql_query(conn, sANbnB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbn = stod(row[1]);
		}
	}


	string searchANabnBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'ab-' ";
	const char* sANabnB = searchANabnBlood_query.c_str();
	valid = mysql_query(conn, sANabnB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabn = stod(row[1]);
		}
	}

	string searchANonBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'o-' ";
	const char* sANonB = searchANonBlood_query.c_str();
	valid = mysql_query(conn, sANonB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodon = stod(row[1]);
		}
	}

	string searchANapBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'a+' ";
	const char* sANapB = searchANapBlood_query.c_str();
	valid = mysql_query(conn, sANapB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodap = stod(row[1]);
		}
	}

	string searchANbpBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'b+' ";
	const char* sANbpB = searchANbpBlood_query.c_str();
	valid = mysql_query(conn, sANbpB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodbp = stod(row[1]);
		}
	}

	string searchANabpBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'ab+' ";
	const char* sANabpB = searchANabpBlood_query.c_str();
	valid = mysql_query(conn, sANabpB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodabp = stod(row[1]);
		}
	}

	string searchANopBlood_query = "SELECT * FROM `bloodstock` WHERE bloodtype = 'o+' ";
	const char* sANopB = searchANopBlood_query.c_str();
	valid = mysql_query(conn, sANopB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			bloodop = stod(row[1]);
		}
	}

	total = bloodan + bloodbn + bloodabn + bloodon + bloodap + bloodbp + bloodabp + bloodop;
	bloodanper = (bloodan / total) * 100;
	bloodbnper = (bloodbn / total) * 100;
	bloodabnper = (bloodabn / total) * 100;
	bloodonper = (bloodon / total) * 100;

	bloodapper = (bloodap / total) * 100;
	bloodbpper = (bloodbp / total) * 100;
	bloodabpper = (bloodabp / total) * 100;
	bloodopper = (bloodop / total) * 100;

	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               A-                |                   " << bloodan << "                |                 " << bloodanper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               B-                |                   " << bloodbn << "                |                 " << bloodbnper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               AB-               |                   " << bloodabn << "                |                 " << bloodabnper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               O-                |                   " << bloodon << "                |                 " << bloodonper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               A+                |                   " << bloodap << "                |                 " << bloodapper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               B+                |                   " << bloodbp << "                |                 " << bloodbpper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               AB+               |                   " << bloodabp << "                |                 " << bloodabpper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";
	cout << "\t\t\t\t|                                 |                                     |                                     |\n";
	cout << "\t\t\t\t|               O+                |                   " << bloodop << "                |                 " << bloodopper << "             |\n";
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|\n";

	cout << "\t\t\t\t|               TOTAL             |                  " << total << "    \t\t|\t\t    100 \t      |" << endl;
	cout << "\t\t\t\t|_________________________________|_____________________________________|_____________________________________|" << endl;
	cout << "\t\t\t\t" << date_time << "\n\n";
	system("pause");
	if (guide == 1)
	{
		AdminHandle();
	}
	if (guide == 2)
	{
		WorkerMenu();
	}
}


///////////////////////////// ORDER   /////////////////////////////
//DONE
void CreateOrder()
{
	system("cls");
OrderGate1:
	string soid = "r";
	string requestid, bloodtype, hospitalid, dateout, quantity, description, input, temp3;
	string bloodask[8] = { "a+","b+","ab+","o+","a-","b-","ab-","o-" };
	string bloodint[8];
	int subquantity, counter, temp1, total = 0;
	int temp[8];
	cout << "\n\n\t#########################################################################################################\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\tBLOOD BANK MANAGEMENT SYSTEM\t\t\t\t        #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t   CREATE BLOOD ORDER MENU\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#########################################################################################################\n";
	cout << "\t" << date_time << "\n";
	cout << "\n\t\t\t\tEnter Received Request Invoice ID : ";
	cin >> requestid;
	counter = 0;
	while (counter < requestid.length())
	{
		if (isupper(requestid[counter]))
		{
			requestid[counter] = tolower(requestid[counter]);
		}
		counter++;
	}
	if (requestid == "cancel") { goto OrderGate1; }
	if (requestid == "0")
	{
		AdminHandle();
	}
	string searchrequestid_query = "SELECT * FROM orderblood WHERE receivedrequestInvoiceID = '" + requestid + "'";
	const char* sOi = searchrequestid_query.c_str();
	qstate = mysql_query(conn, sOi);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1)
		{
			system("pause");
			cout << "\n\t\t\t\t\t\tRequest ID ALREADY EXIST\n";
			goto OrderGate1;
		}
		if (result->row_count == 0)
		{

			for (int counter = 0; counter < 8; counter++)
			{
			OrderGateBloodType:
				bloodtype = bloodask[counter];
				cout << "\n\t\t\t\tENTER BLOOD QUANTITY REQUESTED FOR BLOOD TYPE " << bloodask[counter] << " (Pint) : ";
				cin >> input;

				if (input == "cancel") { AdminHandle(); }
				int counter2 = 0;
				while (counter2 < input.length())
				{
					if (isupper(input[counter]))
					{
						input[counter] = tolower(input[counter]);
					}
					if (isalpha(input[counter]))
					{
						goto OrderGateBloodType;
					}
					counter2++;
				}
				bloodint[counter] = input;
				int blood = stoi(bloodint[counter]);

				string selectBlood_query = "SELECT * FROM bloodstock WHERE bloodtype = '" + bloodtype + "'";
				const char* sB = selectBlood_query.c_str();
				qstate = mysql_query(conn, sB);
				if (!qstate)
				{
					result = mysql_store_result(conn);
					while (row = mysql_fetch_row(result))
					{
						subquantity = stoi(row[1]);
						if (subquantity < blood)
						{
							cout << "\n\t\t\t\t\t\tNO QUANTITY BLOOD STOCK AVAILABLE";
							goto OrderGateBloodType;
						}
						else
						{
							total = total + blood;
						}
					}
				}
			}
			description = "A+ = " + bloodint[0] + "\n \t\t\t\t\t\tB+ = " + bloodint[1] + "\n \t\t\t\t\t\tAB+ = " + bloodint[2] + "\n \t\t\t\t\t\tO+ = " + bloodint[3] + "\n\t\t\t\t\t\tA- = " + bloodint[4] + "\n\t\t\t\t\t\tB- = " + bloodint[5] + "\n\t\t\t\t\t\tAB- = " + bloodint[6] + "\n\t\t\t\t\t\tO- = " + bloodint[7];
		OrderGate4:
			cout << "\n\t\t\t\tEnter hospital id :";
			cin >> hospitalid;
			counter = 0;
			while (counter < hospitalid.length())
			{
				if (isupper(hospitalid[counter]))
				{
					hospitalid[counter] = tolower(hospitalid[counter]);
				}
				counter++;
			}
			if (hospitalid == "cancel") { goto OrderGate1; }
			if (hospitalid == "0")
			{
				AdminHandle();
			}
			string searchHospitalid_query = "SELECT * FROM hospital WHERE hospitalid = '" + hospitalid + "' limit 1";
			const char* sHi = searchHospitalid_query.c_str();
			qstate = mysql_query(conn, sHi);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				if (result->row_count == 1)
				{

					for (int counter = 0; counter < 8; counter++)
					{
						temp[counter] = stoi(bloodint[counter]);
						bloodtype = bloodask[counter];
						string selectBlood_query = "SELECT * FROM bloodstock WHERE bloodtype = '" + bloodtype + "'";
						const char* sB = selectBlood_query.c_str();
						qstate = mysql_query(conn, sB);
						if (!qstate)
						{
							result = mysql_store_result(conn);
							while (row = mysql_fetch_row(result))
							{
								subquantity = stoi(row[1]);
							}
						}
						temp1 = subquantity - temp[counter];

						string temporary;
						ostringstream ss;
						ss << temp1;
						temporary = ss.str();

						string updateStock_query = "UPDATE bloodstock SET Quantity='" + temporary + "' WHERE bloodtype = '" + bloodtype + "'";
						const char* uS = updateStock_query.c_str();
						valid2 = mysql_query(conn, uS);
						if (!valid2)
						{
							cout << "";
						}
					}
					string totaltemporary;
					ostringstream ss;
					ss << total;
					totaltemporary = ss.str();
					string searchOrderid_query = "INSERT INTO `orderblood`(`receivedrequestInvoiceID`, `description`, `quantity`, `HospitalID`) VALUES ('" + requestid + "','" + description + "', '" + totaltemporary + "','" + hospitalid + "')";
					const char* sOi = searchOrderid_query.c_str();
					qstate = mysql_query(conn, sOi);
					if (!qstate)
					{
						string Selectorder = "SELECT * FROM orderblood WHERE receivedrequestInvoiceID = '" + requestid + "'";
						const char* Sor = Selectorder.c_str();
						valid2 = mysql_query(conn, Sor);
						if (!valid2)
						{
							result = mysql_store_result(conn);
							while (row = mysql_fetch_row(result))
							{
								temp3 = row[0];
							}
						}
						soid = soid + temp3;
						string updateorderpartial = "UPDATE orderblood SET sentoutInvoiceid  = '" + soid + "' WHERE  receivedrequestInvoiceID = '" + requestid + "'";
						const char* UOP = updateorderpartial.c_str();
						valid2 = mysql_query(conn, UOP);
						if (!valid2)
						{
							string Selectorder = "SELECT * FROM orderblood WHERE receivedrequestInvoiceID = '" + requestid + "'";
							const char* Sor = Selectorder.c_str();
							valid = mysql_query(conn, Sor);
							if (!valid)
							{
								result = mysql_store_result(conn);
								while (row = mysql_fetch_row(result))
								{
									cout << "\n\t\t\t\t\tREQUEST SENT OUT MADE SUCCESSFULLY ! \n\n";
									cout << "\n\t\t\t\t_________________________________________________\n";
									cout << "\t\t\t\t|  SENT OUT INVOICE ID : " << row[1] << "\n\t\t\t\t|  RECEIVED REQUEST INVOICE ID : " << row[2] << " \n\t\t\t\t|  QUANTITY : " << row[4] << " \n\t\t\t\t|  DATE OUT :" << row[5] << " \n\t\t\t\t|  HOSPITAL ID: " << row[6] << " \n\t\t\t\t|  DESCRIPTION: " << row[3] << " \n";
									cout << "\t\t\t\t_________________________________________________\n\n\n";
									system("pause");
									system("cls");
									CreateOrder();
								}
							}
						}
						else
						{
							cout << "ERROR EXECUTION 1 : " << mysql_errno(conn);
							system("pause");
						}
					}
					else
					{
						cout << "ERROR EXECUTION 3 : " << mysql_errno(conn);
						system("pause");
					}
				}
				if (result->row_count == 0)
				{
					cout << "\n\t\t\t\t\t\tHospital ID Does Not Exist\n";
					goto OrderGate4;
				}
			}
			else
			{
				cout << "ERROR EXECUTION 4 : " << mysql_errno(conn);
				system("pause");
			}
		}
	}
	else
	{
		cout << "ERROR EXECUTION 5 : " << mysql_errno(conn);
		system("pause");
	}
}

//DONE
void viewOrder()
{
	system("cls");
	cout << "\n\n\t#########################################################################################################\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t      BLOOD BANK MANAGEMENT SYSTEM\t\t\t                #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t   ORDER DETAIL MENU\t\t\t\t\t        #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#########################################################################################################\n";
	cout << "\t" << date_time << "\n";
	string searchOrder_query = "SELECT * FROM `orderblood`";
	const char* sO = searchOrder_query.c_str();
	valid = mysql_query(conn, sO);
	if (!valid)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			cout << "\n\n\t\t\t\t_________________________________________________\n";
			cout << "\t\t\t\t|  SENT OUT INVOICE ID : " << row[1] << "\n\t\t\t\t|  RECEIVED REQUEST INVOICE ID : " << row[2] << " \n\t\t\t\t|  QUANTITY : " << row[4] << " \n\t\t\t\t|  DATE OUT :" << row[5] << " \n\t\t\t\t|  HOSPITAL ID: " << row[6] << " \n\t\t\t\t|  DESCRIPTION: " << row[3] << " \n";
			cout << "\t\t\t\t_________________________________________________\n\n\n";
		}
	}
	system("pause");
	AdminHandle();
}

//DONE
void SearchOrder(int guide) {
	system("cls");
	string invoiceid, choice;
	if (guide == 1)
	{
		cout << "\n\n\t#########################################################################################################\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t      BLOOD BANK MANAGEMENT SYSTEM\t\t\t                #\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t   SEARCH ORDER MENU       \t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#########################################################################################################\n";
	}
	if (guide == 2)
	{
		cout << "\n\n\t#########################################################################################################\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t      BLOOD BANK MANAGEMENT SYSTEM\t\t\t                #\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t   EDIT ORDER MAIN MENU    \t\t\t\t\t#\n";
		cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
		cout << "\t#########################################################################################################\n";
	}
	cout << "\t" << date_time << "\n";
	cout << "\t\tENTER INVOICE ID\n";
	cout << "\t\tSent Out Invoice ID :";
	cin >> invoiceid;
	int counter = 0;
	while (counter < invoiceid.length())
	{
		if (isupper(invoiceid[counter]))
		{
			invoiceid[counter] = tolower(invoiceid[counter]);
		}
		counter++;
	}
	if (invoiceid == "0")
	{
		AdminHandle();
	}
	string searchOrder_query = "SELECT * FROM `orderblood` where sentoutinvoiceid = '" + invoiceid + "'";
	const char* sO = searchOrder_query.c_str();
	valid = mysql_query(conn, sO);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\n\n\t\t\t\t_________________________________________________\n";
				cout << "\t\t\t\t|  SENT OUT INVOICE ID : " << row[1] << "\n\t\t\t\t|  RECEIVED REQUEST INVOICE ID : " << row[2] << " \n\t\t\t\t|  QUANTITY : " << row[4] << " \n\t\t\t\t|  DATE OUT :" << row[5] << " \n\t\t\t\t|  HOSPITAL ID: " << row[6] << " \n\t\t\t\t|  DESCRIPTION: " << row[3] << " \n";
				cout << "\t\t\t\t_________________________________________________\n\n\n";
			}
		}
		else
		{
			cout << "\t\t\t\t\t\t INVOICE ID DOES NOT EXIST !\n";
			system("pause");
			system("cls");
			if (guide == 1) { SearchOrder(1); }
			if (guide == 2) { SearchOrder(2); }
		}
	}
	if (guide == 1)
	{
		system("pause");
		SearchOrder(1);
	}
	else if (guide == 2)
	{
		cout << "\t\t\t\t\tDo You Want To Edit ? [Y/N] : ";
		cin >> choice;
		cout << "\n\t\t\t\t_________________________________________________\n\n";
		if (choice == "Y" || choice == "y")
		{
			editOrder(invoiceid);
		}
		else
		{
			if (guide == 1) { SearchOrder(1); }
			if (guide == 2) { SearchOrder(2); }
		}
	}
}

//DONE
void editOrder(string invoiceid) {
	string quantity, receivedinvoiceid, dateout, hospitalid, description, input;
	string bloodask[8] = { "a+","b+","ab+","o+","a-","b-","ab-","o-" };
	string bloodquantity[8];
	int total = 0;
	int counter;

	cout << "\n\n\t\t\t\t  RECEIVED REQUEST INVOICE ID : ";
	cin >> receivedinvoiceid;
	counter = 0;
	while (counter < receivedinvoiceid.length())
	{
		if (isupper(receivedinvoiceid[counter]))
		{
			receivedinvoiceid[counter] = tolower(receivedinvoiceid[counter]);
		}
		counter++;
	}
	if (receivedinvoiceid == "0" || receivedinvoiceid == "cancel")
	{
		AdminHandle();
	}
	cout << "\n\t\t\t\t  DATE OUT : ";
	cin >> dateout;
	if (dateout == "0" || dateout == "cancel")
	{
		AdminHandle();
	}
EHGate1:
	cout << "\n\t\t\t\t  HOSPITAL ID : ";
	cin >> hospitalid;
	counter = 0;
	while (counter < hospitalid.length())
	{
		if (isupper(hospitalid[counter]))
		{
			hospitalid[counter] = tolower(hospitalid[counter]);
		}
		if (ispunct(hospitalid[counter]))
		{
			cout << "\n\t\t\tINVALID CHARACTER\n";
			goto EHGate1;
		}
		counter++;
	}
	if (hospitalid == "cancel")
	{
		goto EHGate1;
	}
	if (hospitalid == "0")
	{
		AdminHandle();
	}

	string searchHPID_query = "SELECT * FROM hospital where hospitalid = '" + hospitalid + "' limit 1";
	const char* sHPID = searchHPID_query.c_str();
	qstate = mysql_query(conn, sHPID);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 0)
		{
			cout << "\n\t\t\t\t\tHopsital ID DOES NOT EXIST\n";
			goto EHGate1;
		}
		if (result->row_count == 1)
		{
			cout << "\n\t\t\t\t  DESCRIPTION : ";
			for (int counter = 0; counter < 8; counter++)
			{
			OrderGateBloodType:
				cout << "\n\t\t\t\t  ENTER BLOOD QUANTITY REQUESTED FOR BLOOD TYPE " << bloodask[counter] << " : ";
				cin >> input;
				if (input == "cancel") { AdminHandle(); }
				int counter2 = 0;
				while (counter2 < input.length())
				{
					if (isupper(input[counter]))
					{
						input[counter] = tolower(input[counter]);
					}
					if (isalpha(input[counter]))
					{
						goto OrderGateBloodType;
					}
					counter2++;
				}
				bloodquantity[counter] = input;
				total += stoi(input);


			}
			ostringstream ss1;
			ss1 << total;
			string Quantity2 = ss1.str();
			description = "A+ = " + bloodquantity[0] + "\n \t\t\t\t\t\tB+ = " + bloodquantity[1] + "\n \t\t\t\t\t\tAB+ = " + bloodquantity[2] + "\n \t\t\t\t\t\tO+ = " + bloodquantity[3] + "\n\t\t\t\t\t\tA- = " + bloodquantity[4] + "\n\t\t\t\t\t\tB- = " + bloodquantity[5] + "\n\t\t\t\t\t\tAB- = " + bloodquantity[6] + "\n\t\t\t\t\t\tO- = " + bloodquantity[7];
			string updateorderpartial = "UPDATE orderblood SET  receivedrequestInvoiceID = '" + receivedinvoiceid + "', `description`='" + description + "',`quantity`='" + Quantity2 + "',`DateOut`='" + dateout + "',`HospitalID`='" + hospitalid + "'  WHERE sentoutInvoiceid  = '" + invoiceid + "'";
			const char* UOP = updateorderpartial.c_str();
			valid2 = mysql_query(conn, UOP);
			if (!valid2)
			{
				string Selectorder = "SELECT * FROM orderblood WHERE sentoutInvoiceid = '" + invoiceid + "'";
				const char* Sor = Selectorder.c_str();
				valid = mysql_query(conn, Sor);
				if (!valid)
				{
					result = mysql_store_result(conn);
					while (row = mysql_fetch_row(result))
					{

						cout << "\n\t\t\t\t\tREQUEST SENT OUT MADE SUCCESSFULLY ! \n\n";
						cout << "\n\t\t\t\t_________________________________________________\n";
						cout << "\t\t\t\t|  SENT OUT INVOICE ID : " << row[1] << "\n\t\t\t\t|  RECEIVED REQUEST INVOICE ID : " << row[2] << " \n\t\t\t\t|  QUANTITY : " << row[4] << " \n\t\t\t\t|  DATE OUT :" << row[5] << " \n\t\t\t\t|  HOSPITAL ID: " << row[6] << " \n\t\t\t\t|  DESCRIPTION: " << row[3] << " \n";
						cout << "\t\t\t\t_________________________________________________\n\n\n";
						system("pause");
						system("cls");
						cout << "\n\t\t\t\t\tORDER UPDATED SUCCESSFULLY ! \n\n";
						system("pause");
						system("cls");
						AdminHandle();
					}
				}
			}
		}
	}
}

//DONE
void deleteOrder() {
	system("cls");
	string invoiceid, choice;
	cout << "\n\n\t#########################################################################################################\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t      BLOOD BANK MANAGEMENT SYSTEM\t\t\t                #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t   DELETE ORDER MENU       \t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#########################################################################################################\n";
	cout << "\t" << date_time << "\n";
	cout << "\t\tENTER INVOICE ID\n";
	cout << "\t\tSent Out Invoice ID :";
	cin >> invoiceid;
	int counter = 0;
	while (counter < invoiceid.length())
	{
		if (isupper(invoiceid[counter]))
		{
			invoiceid[counter] = tolower(invoiceid[counter]);
		}
		counter++;
	}
	if (invoiceid == "0")
	{
		AdminHandle();
	}
	string searchOrder_query = "SELECT * FROM `orderblood` where sentoutinvoiceid = '" + invoiceid + "'";
	const char* sO = searchOrder_query.c_str();
	valid = mysql_query(conn, sO);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\n\n\t\t\t\t_________________________________________________\n";
				cout << "\t\t\t\t|  SENT OUT INVOICE ID : " << row[1] << "\n\t\t\t\t|  RECEIVED REQUEST INVOICE ID : " << row[2] << " \n\t\t\t\t|  QUANTITY : " << row[4] << " \n\t\t\t\t|  DATE OUT :" << row[5] << " \n\t\t\t\t|  HOSPITAL ID: " << row[6] << " \n\t\t\t\t|  DESCRIPTION: " << row[3] << " \n";
				cout << "\t\t\t\t_________________________________________________\n\n\n";
			}
			cout << "\t\t\t\t\t  ARE YOU SURE WANT TO DELETE ? [Y/N] : \n";
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{
				string deleteorder_query = "DELETE FROM `orderblood` WHERE sentoutinvoiceid = '" + invoiceid + "'";
				const char* dO = deleteorder_query.c_str();
				valid = mysql_query(conn, dO);
				if (!valid)
				{
					cout << "\t\t\t\t\t\t  ORDER DELETED SUCCESSFULLY !\n";
					system("pause");
					AdminHandle();
				}
			}
			else {
				AdminHandle();
			}
		}
		else
		{
			cout << "\t\t\t\t\t\t INVOICE ID DOES NOT EXIST !\n";
			deleteOrder();
		}
	}
}



//////////////////////// ADMIN BLOOD ACCESS MENU ///////////////////
//DONE
void UpdateBlood(int guide7, int guide)
{
	string lastchoice;
	system("cls");
	if (guide == 7)
	{
		system("cls");
		cout << "\n\n\t******************************************************************************************************\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                  BLOOD BANK MANAGEMENT SYSTEM                                      *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                UPDATE BLOOD STATUS TO STOCK MENU                                   *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t******************************************************************************************************\n";
		cout << "\t\t" << date_time << "\n";
		cout << "\t                 Please Enter The Blood ID Your Wanted To TRANSFER TO BLOOD STOCK \t     \n";
	}
	if (guide == 6)
	{
		system("cls");
		cout << "\n\n\t******************************************************************************************************\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                  BLOOD BANK MANAGEMENT SYSTEM                                      *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                UPDATE BLOOD STATUS TO TESTED MENU                                  *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t******************************************************************************************************\n";
		cout << "\t\t" << date_time << "\n";
		cout << "\t                 Please Enter The Blood ID That Have Tested and Have Disorder Only\t     \n";
	}
	if (guide == 5)
	{
		system("cls");
		cout << "\n\n\t******************************************************************************************************\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                  BLOOD BANK MANAGEMENT SYSTEM                                      *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t*                               UPDATE BLOOD STATUS TO TESTING MENU                                  *\n";
		cout << "\t*                                                                                                    *\n";
		cout << "\t******************************************************************************************************\n";
		cout << "\t\t" << date_time << "\n";
	}
RBGate1:
	int counter = 0;
	int quantity;
	string status, disordertype, donordisordertype;
	string donatedid, dateOut, BloodType, HospitalID, DonatedID, WorkerID, donorIDstring, donorid, donorname, donorcontactnumber, donorbloodtype, donoridcardnumber, donordatein;
	cout << "\n\t\t\t\t\tEnter \"0\" To Go Back";
	cout << "\n\t\t\t\t\tBlood Donated ID :";
	cin >> donatedid;
	while (counter < donatedid.length())
	{
		if (isupper(donatedid[counter]))
		{
			donatedid[counter] = tolower(donatedid[counter]);
		}
		if (ispunct(donatedid[counter]))
		{
			cout << "\n\t\t\t\t\t\tINVALID CHARACTER\n";
			if (guide7 == 1 && guide == 5)
			{
				UpdateBlood(1, 5);
			}
			else if (guide7 == 2 && guide == 5)
			{
				UpdateBlood(2, 5);
			}
			else if (guide7 == 1 && guide == 6)
			{
				UpdateBlood(1, 6);
			}
			else if (guide7 == 2 && guide == 6)
			{
				UpdateBlood(2, 6);
			}
			if (guide7 == 1 && guide == 7)
			{
				UpdateBlood(1, 7);
			}
			else if (guide7 == 2 && guide == 7)
			{
				UpdateBlood(2, 7);
			}
		}
		counter++;
	}
	if (donatedid == "cancel" || donatedid == "0")
	{
		if (guide7 == 1)
		{
			HandleBlood(1);
		}
		if (guide7 == 2)
		{
			HandleBlood(2);
		}
	}
	string getStatus1_query = "select * from blooddonated where donatedid = '" + donatedid + "'";
	const char* gS = getStatus1_query.c_str();
	qstate = mysql_query(conn, gS);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1)
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\n\n\t\t_________________________________________________________________________________________________\n";
				cout << "\n\t\t\t\t\tDonated ID : " << row[1] << "\n";
				cout << "\t\t\t\t\tDonor ID : " << row[2] << "\n";
				cout << "\t\t\t\t\tDate In : " << row[3] << "\n";
				cout << "\t\t\t\t\tBlood Type : " << row[4] << "\n";

				if (row[5] = NULL)
				{
					cout << "\t\t\t\t\tAdmin ID : " << row[6] << "\n";
				}
				else if (row[6] = NULL)
				{
					cout << "\t\t\t\t\tWorker ID : " << row[5] << "\n";
				}
				cout << "\t\t\t\t\tStatus : " << row[7] << "\n";
				status = row[7];
				if (row[8] != NULL)
				{
					cout << "\t\t\t\t\tDisorder Type : " << row[8] << "\n";
				}
				cout << "\n\t\t_________________________________________________________________________________________________";
			}

			if (guide == 5)
			{
				if (status == "Testing")
				{
					cout << "\n\t\t\t\t\tThe Blood Is Already is Testing Phase\n";
					cout << "\t\t_________________________________________________________________________________________________\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 5);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 5);
					}
				}
				if (status == "Tested")
				{
					cout << "\n\t\t\t\t\tThe Blood Is Already Tested !\n";
					cout << "\t\t_________________________________________________________________________________________________\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 5);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 5);
					}
				}
				if (status == "Stock")
				{
					cout << "\n\t\t\t\t\tThe Blood Is Already in Stock\n";
					cout << "\t\t_________________________________________________________________________________________________\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 5);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 5);
					}
				}
				if (status == "notTested")
				{
					cout << "\n\t\t\t\t\t Do You Want To Continue ? [Y/N] : ";
					cin >> lastchoice;
					if (lastchoice == "y" || lastchoice == "Y")
					{
						string updatenotTested_query = "UPDATE `blooddonated` SET `status`='Testing' WHERE donatedid = '" + donatedid + "'";
						const char* unT = updatenotTested_query.c_str();
						valid = mysql_query(conn, unT);
						if (!valid)
						{
							system("cls");
							cout << "\n\n\n\t\t_________________________________________________________________________________________________\n";
							cout << "\n\t\t\t\t\t\tBLOOD UPDATED TO TESTING PHASE !";
							cout << "\n\t\t_________________________________________________________________________________________________\n";

							string getStatus1_query = "select * from blooddonated where donatedid = '" + donatedid + "'";
							const char* gS = getStatus1_query.c_str();
							qstate = mysql_query(conn, gS);
							if (!qstate)
							{
								result = mysql_store_result(conn);
								while (row = mysql_fetch_row(result))
								{
									cout << "\t\t\t\t\tDonated ID : " << row[1] << "\n";
									cout << "\t\t\t\t\tDonor ID : " << row[2] << "\n";
									cout << "\t\t\t\t\tDate In : " << row[3] << "\n";
									cout << "\t\t\t\t\tBlood Type : " << row[4] << "\n";
									if (row[5] = NULL)
									{
										cout << "\t\t\t\t\tAdmin ID : " << row[6] << "\n";
									}
									else if (row[6] = NULL)
									{
										cout << "\t\t\t\t\tWorker ID : " << row[5] << "\n";
									}
									cout << "\t\t\t\t\tStatus : " << row[7] << "\n";
								}
							}
							system("PAUSE");
							if (guide7 == 1)
							{
								UpdateBlood(1, 5);
							}
							else if (guide7 == 2)
							{
								UpdateBlood(2, 5);
							}
						}
						else
						{
							cout << "ERROR EXECUTION 1 " << mysql_errno(conn) << "\n";
							system("pause");
						}
					}
					else
					{
						system("cls");
						if (guide7 == 1) 
						{
							UpdateBlood(1, 5);
						}
						else if (guide7 == 2)
						{
							UpdateBlood(2, 5);
						}
					}
				}
			}

			if (guide == 6)
			{
				if (status == "notTested")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is still NOT TESTED ! \n";
					cout << "\n\t\t_________________________________________________________________________________________________\n";

					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 6);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 6);
					}
				}
				if (status == "Stock")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is Already in Stock\n";
					cout << "\n\t\t_________________________________________________________________________________________________\n";

					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 6);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 6);
					}
				}
				if (status == "Tested")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is Already Tested !\n";
					cout << "\n\t\t_________________________________________________________________________________________________\n";

					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 6);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 6);
					}
				}
				if (status == "Testing")
				{
					cout << "\n\t\t\t\t\t Do You Want To Continue ? [Y/N] : ";
					cin >> lastchoice;
					if (lastchoice == "y" || lastchoice == "Y")
					{
						string updateTestingToDisorder_query = "UPDATE `blooddonated` SET `status`='Disorder' WHERE donatedid = '" + donatedid + "'";
						const char* uTTD = updateTestingToDisorder_query.c_str();
						valid = mysql_query(conn, uTTD);
						if (!valid)
						{
							cout << "\n\t\t\t\t\tDisorder Type : ";
							cin >> disordertype;
							string updateDisorder_query = "UPDATE `blooddonated` SET `status`='Tested', `Disorder_Type` = '" + disordertype + "' WHERE donatedid = '" + donatedid + "'";
							const char* uDs = updateDisorder_query.c_str();
							valid2 = mysql_query(conn, uDs);
							if (!valid2)
							{
								string searchBloodI_query = "select * FROM donor join blooddonated on donor.donorid = blooddonated.donorid where donatedid = '" + donatedid + "'";
								const char* sBDI = searchBloodI_query.c_str();
								qstate = mysql_query(conn, sBDI);
								if (!qstate)
								{
									result = mysql_store_result(conn);
									while (row = mysql_fetch_row(result))
									{
										donorid = row[1];
										donorname = row[2];
										donorcontactnumber = row[3];
										donorbloodtype = row[4];
										donoridcardnumber = row[5];
										donordatein = row[12];
										donordisordertype = row[17];
									}
								}
								system("CLS");
								cout << "\n\n\t\t\t\t______________________________________________________________________";
								cout << "\t\t\t\t\t\t\t\t\tBLOOD UPDATED TO TESTED PHASE !\n";
								cout << "\t\t\t\t______________________________________________________________________";
								cout << "\n\t\t\t\t\t\tDonor ID : " << donorid << endl;
								cout << "\n\t\t\t\t\t\tDonor Name : " << donorname << endl;
								cout << "\n\t\t\t\t\t\tDonor BloodType : " << donorbloodtype << endl;
								cout << "\n\t\t\t\t\t\tDonor Contact Number : " << donorcontactnumber << endl;
								cout << "\n\t\t\t\t\t\tDonor ID Card Number : " << donoridcardnumber << endl;
								cout << "\n\t\t\t\t\t\tDonor Blood Disorder Type : " << donordisordertype << endl;
								cout << "\n\t\t\t\t\t\tDate Blood Donated : " << donordatein << endl;
								cout << "\t\t\t\t______________________________________________________________________\n";
								system("PAUSE");
								if (guide7 == 1)
								{
									UpdateBlood(1, 6);
								}
								else if (guide7 == 2)
								{
									UpdateBlood(2, 6);
								}
							}
						}
					}
					else
					{
						system("cls");
						if (guide7 == 1)
						{
							UpdateBlood(1, 6);
						}
						else if (guide7 == 2)
						{
							UpdateBlood(2, 6);
						}
					}
				}
			}

			if (guide == 7)
			{
				if (status == "Tested")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is Already Tested !\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 7);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 7);
					}
				}
				if (status == "Stock")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is Already in Stock !\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 7);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 7);
					}
				}
				if (status == "notTested")
				{
					cout << "\n\t\t\t\t\t\tThe Blood Is Not Yet Tested !\n";
					system("PAUSE");
					if (guide7 == 1)
					{
						UpdateBlood(1, 7);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 7);
					}
				}
				cout << "\n\t\t\t\t\t Do You Want To Continue ? [Y/N] : ";
				cin >> lastchoice;
				if (lastchoice == "y" || lastchoice == "Y")
				{
					if (status == "Testing")
					{
						string updateStock_query = "UPDATE `blooddonated` SET `status`='Stock' WHERE donatedid = '" + donatedid + "'";
						const char* uS = updateStock_query.c_str();
						valid = mysql_query(conn, uS);
						if (!valid)
						{
							string selectBloodtype_query = "SELECT * FROM blooddonated WHERE donatedid = '" + donatedid + "'";
							const char* sB = selectBloodtype_query.c_str();
							valid = mysql_query(conn, sB);
							if (!valid)
							{
								result = mysql_store_result(conn);
								while (row = mysql_fetch_row(result))
								{
									BloodType = row[4];
								}
								string selectBloodQuantity_query = "SELECT * FROM bloodstock WHERE bloodtype = '" + BloodType + "'";
								const char* sBQ = selectBloodQuantity_query.c_str();
								valid = mysql_query(conn, sBQ);
								if (!valid)
								{
									result = mysql_store_result(conn);
									while (row = mysql_fetch_row(result))
									{
										quantity = stoi(row[1]);
										quantity += 1;
									}
									ostringstream ss;
									ss << quantity;
									string Quantity1 = ss.str();

									string updateBloodQuantity_query = "UPDATE `bloodstock` SET `quantity`='" + Quantity1 + "' WHERE Bloodtype = '" + BloodType + "'";
									const char* uBQ = updateBloodQuantity_query.c_str();
									valid = mysql_query(conn, uBQ);
									if (!valid)
									{
										cout << "\n\t\t\t\t\t\tBLOOD UPDATED TO STOCK SUCCESSFULLY !\n";
										system("PAUSE");
										if (guide7 == 1)
										{
											UpdateBlood(1, 7);
										}
										else if (guide7 == 2)
										{
											UpdateBlood(2, 7);
										}
									}
								}
							}
						}
					}
				}
				else
				{
					system("cls");
					if (guide7 == 1)
					{
						UpdateBlood(1, 7);
					}
					else if (guide7 == 2)
					{
						UpdateBlood(2, 7);
					}
				}
			}
		}
		else
		{
			cout << "\n\t\t\t\t\t\tBLOOD ID DOES NOT EXIST !\n";
			system("PAUSE");
			if (guide7 == 1 && guide == 5)
			{
				UpdateBlood(1, 5);
			}
			else if (guide7 == 2 && guide == 5)
			{
				UpdateBlood(2, 5);
			}
			else if (guide7 == 1 && guide == 6)
			{
				UpdateBlood(1, 6);
			}
			else if (guide7 == 2 && guide == 6)
			{
				UpdateBlood(2, 6);
			}
			if (guide7 == 1 && guide == 7)
			{
				UpdateBlood(1, 7);
			}
			else if (guide7 == 2 && guide == 7)
			{
				UpdateBlood(2, 7);
			}
		}
	}
	else
	{
		cout << "ERROR EXECUTION LAST " << mysql_errno(conn) << "\n";
		system("pause");
	}
}

//DONE
void AdjustBloodStock() {
	system("CLS");
	string bloodask[8] = { "a-","b-","ab-","o-","a+","b+","ab+","o+" };
	string bloodint[8];
	string bloodtype, input;
	cout << "\n\n\t######################################################################################################\n\n";
	cout << "\t                                        BLOOD BANK MANAGEMENT SYSTEM                                  \n";
	cout << "\n\n\t                                        ADJUST BLOOD STOCK ADMIN MENU      \n";
	cout << "\t######################################################################################################\n";
	cout << "\t" << date_time << "\n";
	cout << "\n\t\t\t\t\t\tCurrent Blood Quantity\n";
	cout << "\n\t\t\t\t\t_________________________________________\n";
	for (int counter4 = 0; counter4 < 8; counter4++)
	{
		bloodtype = bloodask[counter4];
		string showStock_query = "SELECT * from bloodstock where bloodtype = '"+bloodtype+"' ";
		const char* sS = showStock_query.c_str();
		valid2 = mysql_query(conn, sS);
		if (!valid2)
		{
			result = mysql_store_result(conn);
			while (row = mysql_fetch_row(result))
			{
				cout << "\t\t\t\t\t\t  " << bloodtype << "      :     " << row[1] << endl;
				cout << "\t\t\t\t\t_________________________________________\n";

			}
		}
	}

	for (int counter2 = 0; counter2 < 8; counter2++)
	{
	TypeAgain:
		bloodtype = bloodask[counter2];
		cout << "\n\tENTER BLOOD QUANTITY FOR BLOOD TYPE " << bloodask[counter2] << " : ";
		try
		{
			cin >> input;
			if (input == "cancel" || input == "CANCEL")
			{
				throw 99;
			}
		}
		catch (int x) {
			AdminHandle();
		}
		int counter = 0;
		while (counter < input.length())
		{
			if (isalpha(input[counter]))
			{
				cout << "\t\t\t\t\t\t\tPlease Enter A Valid Value !";
				goto TypeAgain;
			}
			if (ispunct(input[counter]))
			{
				cout << "\t\t\t\t\t\t\tPlease Enter A Valid Value !";
				goto TypeAgain;
			}
			counter++;
		}
		bloodint[counter2] = input;
	}
	for (int counter3 = 0; counter3 < 8; counter3++)
	{
		bloodtype = bloodask[counter3];
		string updateStock_query = "UPDATE bloodstock SET Quantity='" + bloodint[counter3] + "' WHERE bloodtype = '" + bloodtype + "'";
		const char* uS = updateStock_query.c_str();
		valid2 = mysql_query(conn, uS);
		if (!valid2)
		{
			cout << "";
		}
	}
	viewBloodSTOCK(1);
}

//DONE
void AdjustBloodStatus() {

	system("CLS");
	string donatedid, choice, disorder, bloodtype, status;
	int bloodquantity = 0;
	cout << "\n\n\t######################################################################################################\n\n";
	cout << "\t                                        BLOOD BANK MANAGEMENT SYSTEM                                  \n";
	cout << "\n\n\t                                   ADJUST BLOOD DONATED STATUS ADMIN MENU                         \n";
	cout << "\t######################################################################################################\n";
ADGate1:
	cout << "\t" << date_time << "\n";
	cout << "\tEnter Blood Donated ID : ";
	cin >> donatedid;
	int counter = 0;
	while (counter < donatedid.length())
	{
		if (isupper(donatedid[counter]))
		{
			donatedid[counter] = tolower(donatedid[counter]);
		}
		counter++;
	}
	if (donatedid == "0")
	{
		HandleBlood(1);
	}
	string SearchDonatedBlood_query = "SELECT * FROM BLOODDONATED WHERE donatedid = '" + donatedid + "' ";
	const char* sDB = SearchDonatedBlood_query.c_str();
	valid = mysql_query(conn, sDB);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\t|\t\t\t\t\tDonated ID :" << row[1] << "\n";
				cout << "\t|\t\t\t\t\tDonor ID :" << row[2] << "\n";
				cout << "\t|\t\t\t\t\tDate In :" << row[3] << "\n";
				bloodtype = row[4];
				cout << "\t|\t\t\t\t\tBloodType :" << row[4] << "\n";
				status = row[7];
				cout << "\t|\t\t\t\t\tStatus :" << row[7] << "\n";
				if (row[8] == NULL)
				{
					cout << "\t|\t\t\t\t\tDisorder : NULL\n";
				}
				else
				{
					cout << "\t|\t\t\t\t\tDisorder :" << row[8] << "\n";
				}
				if (row[5] == NULL)
				{
					cout << "\t|\t\t\t\t\tAdmin ID : " << row[6] << "\n";
				}
				else
				{
					cout << "\t|\t\t\t\t\tWorker ID :" << row[5] << "\n";
				}

			}
			cout << "\t|______________________________________________________________________________________________________\n\n";
			cout << "\t\t\tSelect Status : ";
			cout << "\n\t\t\t1) notTested\n";
			cout << "\t\t\t2) Testing\n";
			cout << "\t\t\t3) Stock\n";
			cout << "\t\t\t4) Tested\n";
			cout << "\t\t\tChoice : ";
			cin >> choice;
			counter = 0;
			while (counter < choice.length())
			{
				if (isupper(choice[counter]))
				{
					choice[counter] = tolower(choice[counter]);
				}
				counter++;
			}
			if (status == "Stock" && choice == "3")
			{
				cout << "\n\t\t\t\t BLOOD ALREADY IN STOCK ! \n";
				system("pause");
				system("cls");
				AdjustBloodStatus();
			}
			if (status == "Stock" && (choice == "1" || choice == "2" || choice == "4"))
			{
				string SearchBlood2T_query = "SELECT * from bloodstock WHERE bloodtype = '" + bloodtype + "' ";
				const char* sBT2 = SearchBlood2T_query.c_str();
				valid = mysql_query(conn, sBT2);
				if (!valid)
				{
					result = mysql_store_result(conn);
					while (row = mysql_fetch_row(result))
					{
						bloodquantity = stoi(row[1]);
					}
					bloodquantity = bloodquantity - 1;
				}
				ostringstream ss1;
				ss1 << bloodquantity;
				string Quantity = ss1.str();
				string addBloodStock2 = "UPDATE `bloodstock` SET `Quantity`='" + Quantity + "' WHERE bloodtype = '" + bloodtype + "' ";
				const char* sBT3 = addBloodStock2.c_str();
				valid = mysql_query(conn, sBT3);
				if (!valid)
				{
					cout << " ";
				}
			}
			if (choice == "0")
			{
				HandleBlood(1);
			}
			else if (choice == "1")
			{
				string SearchDonatedBlood_query = "UPDATE `blooddonated` SET `status`='notTested',`Disorder_Type`='NULL' WHERE donatedid = '" + donatedid + "' ";
				const char* sDB = SearchDonatedBlood_query.c_str();
				valid = mysql_query(conn, sDB);
				if (!valid)
				{
					cout << "\t\t\t\tUPDATE BLOOD TO NOT TESTED SUCCESSFULLY !\n";
					system("pause");
					AdjustBloodStatus();
				}
			}
			else if (choice == "2")
			{
				string SearchDonatedBlood_query = "UPDATE `blooddonated` SET `status`='Testing',`Disorder_Type`='NULL' WHERE donatedid = '" + donatedid + "' ";
				const char* sDB = SearchDonatedBlood_query.c_str();
				valid = mysql_query(conn, sDB);
				if (!valid)
				{
					cout << "\t\t\t\tUPDATE BLOOD TO TESTING SUCCESSFULLY !\n";
					system("pause");
					AdjustBloodStatus();
				}
			}
			else if (choice == "3")
			{
				string SearchDonatedBlood_query = "UPDATE `blooddonated` SET `status`='Stock',`Disorder_Type`='NULL' WHERE donatedid = '" + donatedid + "' ";
				const char* sDB = SearchDonatedBlood_query.c_str();
				valid = mysql_query(conn, sDB);
				if (!valid)
				{
					string SearchBloodT_query = "SELECT * from bloodstock WHERE bloodtype = '" + bloodtype + "' ";
					const char* sBT = SearchBloodT_query.c_str();
					valid = mysql_query(conn, sBT);
					if (!valid)
					{
						result = mysql_store_result(conn);
						while (row = mysql_fetch_row(result))
						{
							bloodquantity = stoi(row[1]);
						}
						bloodquantity = bloodquantity + 1;

						ostringstream ss1;
						ss1 << bloodquantity;
						string Quantity = ss1.str();

						string addBloodStock = "UPDATE `bloodstock` SET `Quantity`='" + Quantity + "' WHERE bloodtype = '" + bloodtype + "' ";
						const char* sBT = addBloodStock.c_str();
						valid = mysql_query(conn, sBT);
						if (!valid)
						{
							cout << "\t\t\t\tUPDATE BLOOD TO STOCK SUCCESSFULLY !\n";
							system("pause");
							AdjustBloodStatus();
						}
					}
				}
			}
			else if (choice == "4")
			{
				cout << "\n\t\t\tType of Disorder : ";
				cin >> disorder;
				counter = 0;
				while (counter < disorder.length())
				{
					if (isupper(disorder[counter]))
					{
						disorder[counter] = tolower(disorder[counter]);
					}
					counter++;
				}
				if (disorder == "0")
				{
					HandleBlood(1);
				}
				string SearchDonatedBlood_query = "UPDATE `blooddonated` SET `status`='Tested',`Disorder_Type`='" + disorder + "' WHERE donatedid = '" + donatedid + "' ";
				const char* sDB = SearchDonatedBlood_query.c_str();
				valid = mysql_query(conn, sDB);
				if (!valid)
				{
					cout << "\t\t\t\tUPDATE BLOOD TO TESTED SUCCESSFULLY !\n";
					system("pause");
					AdjustBloodStatus();
				}
			}
			else
			{
				AdjustBloodStatus();
			}
		}
		else
		{
			cout << "\n\t\t\t\t\t\tBLOOD DOES NOT EXIST !\n";
			goto ADGate1;
		}
	}

}

//DONE
void RemoveBloodDonated() {
	system("cls");
	string donatedid, choice;
	cout << "\n\n\t\t\t\t########################################################################################################\n";
	cout << "\t\t\t\t                                  BLOOD BANK MANAGEMENT SYSTEM                                          \n";
	cout << "\n\t\t\t\t########################################################################################################\n";
	cout << "\n\n\t\t\t\t________________________________________________________________________________________________________\n";
	cout << "\t\t\t\t|                                                                                                      |\n";
	cout << "\t\t\t\t|                                   Delete Blood Donated Menu                                          |\n";
	cout << "\t\t\t\t|______________________________________________________________________________________________________|\n";
	cout << "\t\t\t\t|" << date_time;
	cout << "\t\t\t\t|ENTER \"0\" TO EXIT\n";
	cout << "\t\t\t\t|Enter Blood Donated ID : ";
	try
	{

		cin >> donatedid;
		int counter = 0;
		while (counter < donatedid.length())
		{
			if (isupper(donatedid[counter]))
			{
				donatedid[counter] = tolower(donatedid[counter]);
			}
			counter++;
		}
		if (donatedid == "0")
		{
			HandleBlood(1);
		}
		string SearchDonatedBlood_query = "SELECT * FROM BLOODDONATED WHERE donatedid = '" + donatedid + "' ";
		const char* sDB = SearchDonatedBlood_query.c_str();
		valid = mysql_query(conn, sDB);
		if (!valid)
		{
			result = mysql_store_result(conn);
			if (result->row_count == 1) //if result 1 or found
			{
				while (row = mysql_fetch_row(result))
				{
					cout << "\t\t\t\t|\t\t\t\t\tDonated ID :" << row[1] << "\n";
					cout << "\t\t\t\t|\t\t\t\t\tDonor ID :" << row[2] << "\n";
					cout << "\t\t\t\t|\t\t\t\t\tDate In :" << row[3] << "\n";
					cout << "\t\t\t\t|\t\t\t\t\tBloodType :" << row[4] << "\n";
					cout << "\t\t\t\t|\t\t\t\t\tStatus :" << row[7] << "\n";
					if (row[8] == NULL)
					{
						cout << "\t\t\t\t|\t\t\t\t\tDisorder : NULL \n";
					}
					else
					{
						cout << "\t\t\t\t|\t\t\t\t\tDisorder :" << row[8] << "\n";
					}
					if (row[5] == NULL)
					{
						cout << "\t\t\t\t|\t\t\t\t\tAdmin ID : " << row[6] << "\n";
					}
					else if (row[6] == NULL)
					{
						cout << "\t\t\t\t|\t\t\t\t\tWorker ID :" << row[5] << "\n";
					}
				}
				cout << "\t\t\t\t|______________________________________________________________________________________________________\n\n";
				cout << "\t\t\t\t ARE YOU SURE YOU WANT TO DELETE ? [Y/N] : ";
				cin >> choice;
				if (choice == "0")
				{
					HandleBlood(1);
				}
				if (choice == "y" || choice == "Y")
				{
					string SearchDonated2Blood_query = "DELETE FROM BLOODDONATED WHERE donatedid = '" + donatedid + "' ";
					const char* sDB2 = SearchDonated2Blood_query.c_str();
					valid = mysql_query(conn, sDB2);
					if (!valid)
					{
						cout << "\t\t\t\t\t\tBLOOD DELETED SUCCESSFULLY !\n";
						system("pause");
						RemoveBloodDonated();
					}
				}
				else
				{
					throw 99;
				}
			}
			if (result->row_count == 0) //if result 1 or found
			{
				cout << "\t\t\t\t\t\t\t BLOOD DOES NOT EXIST !\n";
				system("pause");
				throw 99;
			}
		}
		else
		{
			cout << "\t\t\t\t\t\t\t BLOOD DOES NOT EXIST !\n";
			system("pause");
			throw 99;
		}
	}
	catch (int x)
	{
		RemoveBloodDonated();
	}
}


///////////////////////////       HOSPITAL    ////////////////////////
//DONE
void ShowHospital(int guide)
{
	system("cls");
	string choice;
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n";
	cout << "\n\t\t######################################################################################################################################################\n\n";
	cout << "\t\t                                                              HOSPITAL DETAIL MENU\n";
	cout << "\n\n\t\t" << date_time;
	cout << "\t\t________________________________________________________________________________________________________________________________________________________________________\n";
	cout << "\t\t|\t\tHospitalID\t\t\t| \tNAME AND ADDRESS  \n";
	cout << "\t\t|_______________________________________________|_______________________________________________________________________________________________________________________\n";
	string showPPD_query = "SELECT * FROM hospital";
	const char* sP = showPPD_query.c_str();
	qstate = mysql_query(conn, sP);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			cout << "\t\t|\t\t\t\t\t\t|\n";
			cout << "\t\t|\t\t" << row[0] << "\t\t\t\t| " << row[1] << "  :  " << row[2] << "  \n";
			cout << "\t\t|_______________________________________________|_______________________________________________________________________________________________________________________\n";
		}
	}
	if (guide == 1)
	{
		system("pause");
		AdminHandle();
	}
	if (guide == 2)
	{
		system("pause");
		WorkerMenu();
	}
}

//DONE
void EnterHospital()
{
	system("cls");
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n\n\n";
	cout << "\t\t                                                             REGISTER HOSPITAL MENU\n";
	cout << "\n\t\t######################################################################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
HospitalIDGate:
	int counter = 0;
	string hospitalID, hospitalName, hospitalAddress, choice;
	cout << "\t\t\tEnter \"0\" To Go Back";
	cout << "\n\t\t\tEnter Hospital ID : ";
	cin.ignore();
	getline(cin, hospitalID);
	while (counter < hospitalID.length())
	{
		if (islower(hospitalID[counter]))
		{
			hospitalID[counter] = toupper(hospitalID[counter]);
		}
		counter++;
	}
	if (hospitalID == "0")
	{
		AdminHandle();
	}
	if (hospitalID == "CANCEL")
	{
		goto HospitalIDGate;
	}
	string searchHospitalID_query = "SELECT * from hospital where hospitalid = '" + hospitalID + "'";
	const char* sHID = searchHospitalID_query.c_str();
	qstate = mysql_query(conn, sHID);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			cout << "\n\t\t\t\t\t\t HOSPITAL ID ALREADY EXIST ! \n";
			goto HospitalIDGate;
		}
		if (result->row_count == 0)
		{
		HospitalNameGate:
			cout << "\n\t\t\tEnter Hospital Name : ";
			getline(cin, hospitalName);
			counter = 0;
			while (counter < hospitalName.length())
			{
				if (isupper(hospitalName[counter]))
				{
					hospitalName[counter] = tolower(hospitalName[counter]);
				}
				counter++;
			}
			if (hospitalName == "0") { AdminHandle(); }
			if (hospitalName == "cancel") { AdminHandle(); }
			string searchHospitalName_query = "select * from hospital where name = '" + hospitalName + "' limit 1";
			const char* sHN = searchHospitalName_query.c_str();
			qstate = mysql_query(conn, sHN);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				if (result->row_count == 1) //if result 1 or found
				{
					cout << "\t\t\t\t HOSPITAL NAME ALREADY EXIST ! ";
					goto HospitalNameGate;
				}
				if (result->row_count == 0)
				{
					cout << "\n\t\t\tEnter Hospital Address : ";
					getline(cin, hospitalAddress);
					counter = 0;
					while (counter < hospitalAddress.length())
					{
						if (isupper(hospitalAddress[counter]))
						{
							hospitalAddress[counter] = tolower(hospitalAddress[counter]);
						}
						counter++;
					}
					if (hospitalAddress == "0") { AdminHandle(); }
					if (hospitalAddress == "cancel") { AdminHandle(); }
					cout << "\n\n\t\t\t Is All Data Correct ? [Y/N] :";
					cin >> choice;
					if (choice == "Y" || choice == "y")
					{
						string InsertHospital_query = "INSERT INTO hospital (HospitalID, Name, Address) VALUES ('" + hospitalID + "','" + hospitalName + "', '" + hospitalAddress + "')";
						const char* sHN = InsertHospital_query.c_str();
						valid = mysql_query(conn, sHN);
						if (!valid)
						{
							cout << "\n\n\n\t\t\t\t\tHospital Registration Successfully";
							system("pause");
							system("cls");
							ShowHospital(1);
						}
						else
						{
							system("cls");
							cout << "\n\n\t\t\t Error Execution 1 " << mysql_errno(conn);
							system("pause");
							goto HospitalIDGate;
						}
					}
					else
					{
						goto HospitalIDGate;
					}
				}
			}
			else
			{
				system("cls");
				cout << "\n\n\t\t\t Error Execution 2 " << mysql_errno(conn);
				system("pause");
				goto HospitalIDGate;
			}
		}
	}
	else
	{
		system("cls");
		cout << "\n\n\t\t\t Error Execution 3 " << mysql_errno(conn);
		system("pause");
		goto HospitalIDGate;
	}
}

//DONE
void EditHospital()
{
EHGate1:
	system("cls");
	string hospitalid, hospitalname, hospitaladdress;
	int counter;
	cin.ignore();
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n\n\n";
	cout << "\t\t                                                           MODIFY HOSPITAL DETAIL MENU\n";
	cout << "\n\t\t######################################################################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tEnter \"0\" To Go Back";
	cout << "\n\t\tEnter Hospital ID : ";
	getline(cin, hospitalid);
	counter = 0;
	while (counter < hospitalid.length())
	{
		if (isupper(hospitalid[counter]))
		{
			hospitalid[counter] = tolower(hospitalid[counter]);
		}
		if (ispunct(hospitalid[counter]))
		{
			cout << "\n\t\t\tINVALID CHARACTER\n";
			goto EHGate1;
		}
		counter++;
	}
	if (hospitalid == "cancel")
	{
		goto EHGate1;
	}
	if (hospitalid == "0")
	{
		AdminHandle();
	}
	string searchHPID_query = "SELECT * FROM hospital where hospitalid = '" + hospitalid + "' limit 1";
	const char* sHPID = searchHPID_query.c_str();
	qstate = mysql_query(conn, sHPID);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 0)
		{
			cout << "\n\t\t\tHopsital ID DOES NOT EXIST\n";
			goto EHGate1;
		}
		if (result->row_count == 1)
		{
			string showHospital_query = "SELECT * FROM hospital where hospitalid = '" + hospitalid + "'";
			const char* sH = showHospital_query.c_str();
			qstate = mysql_query(conn, sH);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				while (row = mysql_fetch_row(result))
				{
					cout << "\n\t\t\t#######################################################################";
					cout << "\n\n\t\t\tHospital ID : " << row[0] << "\n";
					cout << "\n\t\t\tHospital Name: " << row[1] << "\n";
					cout << "\n\t\t\tHospital Address : " << row[2] << "\n\n";
					cout << "\t\t\t#######################################################################\n\n";
				}
			}
			cin.ignore();
			cout << "\n\t\tEnter Hospital Name : ";
			getline(cin, hospitalname);
			counter = 0;
			while (counter < hospitalname.length())
			{
				if (isupper(hospitalname[counter]))
				{
					hospitalname[counter] = tolower(hospitalname[counter]);
				}
				counter++;
			}
			if (hospitalname == "cancel")
			{
				goto EHGate1;
			}
			if (hospitalname == "0")
			{
				AdminHandle();
			}
			cin.ignore();
			cout << "\n\t\tEnter Hospital Addreess : ";
			getline(cin, hospitaladdress);
			counter = 0;
			while (counter < hospitalname.length())
			{
				if (isupper(hospitaladdress[counter]))
				{
					hospitalname[counter] = tolower(hospitalname[counter]);
				}
				counter++;
			}
			if (hospitaladdress == "cancel")
			{
				goto EHGate1;
			}
			if (hospitaladdress == "0")
			{
				AdminHandle();
			}
			string updateHospital_query = "UPDATE hospital SET Name='" + hospitalname + "', Address='" + hospitaladdress + "' WHERE hospitalid = '" + hospitalid + "'";
			const char* uH = updateHospital_query.c_str();
			qstate = mysql_query(conn, uH);
			if (!qstate)
			{
				cout << "\n\t\t\tUPDATE SUCCESSFULLY !\n";
				system("pause");
				system("cls");
				ShowHospital(1);
			}
			else
			{
				cout << "ERROR IN EXECUTION 1 : " << mysql_errno(conn) << endl;
				system("pause");
				goto EHGate1;
			}
		}
	}
	else
	{
		cout << "ERROR IN EXECUTION 2 : " << mysql_errno(conn) << endl;
		system("pause");
		goto EHGate1;
	}
}

//DONE
void deleteHospital() {
	system("cls");
	string hospitalid, choice;
	cout << "\n\n\t#########################################################################################################\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t BLOOD BANK MANAGEMENT SYSTEM\t\t\t\t        #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t     DELETE HOSPITAL MENU      \t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#########################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tEnter \"0\" To Go Back";
dHospital:
	cout << "\t\tENTER HOSPITAL ID TO BE DELETE\n";
	cout << "\t\tHOSPITAL ID: ";
	cin.ignore();
	getline(cin, hospitalid);
	int counter = 0;
	while (counter < hospitalid.length())
	{
		if (isupper(hospitalid[counter]))
		{
			hospitalid[counter] = tolower(hospitalid[counter]);
		}
		counter++;
	}
	if (hospitalid == "0")
	{
		AdminHandle();
	}
	string searchOrder_query = "SELECT * FROM `hospital` where hospitalid = '" + hospitalid + "'";
	const char* sO = searchOrder_query.c_str();
	valid = mysql_query(conn, sO);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\n\t\t#############################################################################################";
				cout << "\n\t\t\t\tHOSPITAL ID : " << row[0];
				cout << "\n\t\t\t\tHOSPITAL NAME :" << row[1];
				cout << "\n\t\t\t\tHOSPITAL ADDRESS : " << row[2];
				cout << "\n\t\t#############################################################################################";
			}
			cout << "\n\n\t\t\t\t\t\t  ARE YOU SURE WANT TO DELETE ? [Y/N] : ";
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{
				string deleteorder_query = "DELETE FROM `hospital` WHERE hospitalid = '" + hospitalid + "'";
				const char* dO = deleteorder_query.c_str();
				valid = mysql_query(conn, dO);
				if (!valid)
				{
					cout << "\n\t\t\t\t\t\t  HOSPITAL DELETED SUCCESSFULLY !\n";
					system("pause");
					system("cls");
					ShowHospital(1);
				}
			}
			else {
				AdminHandle();
			}
		}
		else
		{
			cout << "\t\t\t\t\t\t HOSPITAL ID DOES NOT EXIST !\n";
			goto dHospital;
		}
	}
}


///////////////////////////       PUSAT DERMA DARAH    ////////////////////////
//DONE
void ShowPPD(int guide)
{
	system("cls");
	string choice;
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n";
	cout << "\n\t\t######################################################################################################################################################\n\n";
	cout << "\t\t                                                          PUSAT DERMA DARAH DETAIL MENU\n";
	cout << "\n\n\t\t" << date_time;
	cout << "\t\t______________________________________________________________________________________________________________________________________________________\n";
	cout << "\t\t|\t\tPPDID\t\t\t| \tNAME AND ADDRESS  \n";
	cout << "\t\t|_______________________________________|_____________________________________________________________________________________________________________\n";
	string showPPD_query = "SELECT * FROM pusatdermadarah";
	const char* sP = showPPD_query.c_str();
	qstate = mysql_query(conn, sP);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		while (row = mysql_fetch_row(result))
		{
			cout << "\t\t|\t\t" << row[0] << "\t\t\t| " << row[1] << "  :  " << row[2] << "  \n";
			cout << "\t\t|_______________________________________|_____________________________________________________________________________________________________________\n";
		}
	}
	if (guide == 1)
	{
		system("pause");
		AdminHandle();
	}
	if (guide == 2)
	{
		system("pause");
		WorkerMenu();
	}
}

//DONE
void EnterPPD()
{
PPDIDGate:
	system("cls");
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n\n\n";
	cout << "\t\t                                                         REGISTER PUSAT DERMA DARAH MENU\n";
	cout << "\n\t\t######################################################################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	int counter = 0;
	string PPDID, PPDName, PPDAddress, choice;
	cout << "\t\t\tEnter \"0\" To Go Back";
	cin.ignore();
	cout << "\n\t\t\tEnter PPD ID : ";
	getline(cin, PPDID);
	while (counter < PPDID.length())
	{
		if (islower(PPDID[counter]))
		{
			PPDID[counter] = toupper(PPDID[counter]);
		}
		counter++;
	}
	if (PPDID == "0")
	{
		AdminHandle();
	}
	if (PPDID == "CANCEL")
	{
		goto PPDIDGate;
	}
	string searchPPDID_query = "select * from pusatdermadarah where PPDID = '" + PPDID + "'";
	const char* sPID = searchPPDID_query.c_str();
	qstate = mysql_query(conn, sPID);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			cout << "\n\t\t\t\t\t PPDID ALREADY EXIST ! \n";
			goto PPDIDGate;
		}
		if (result->row_count == 0)
		{
		PPDNameGate:
			cin.ignore();
			cout << "\n\t\t\tEnter Pusat Derma Darah Name : ";
			getline(cin, PPDName);
			counter = 0;
			while (counter < PPDName.length())
			{
				if (isupper(PPDName[counter]))
				{
					PPDName[counter] = tolower(PPDName[counter]);
				}
				counter++;
			}
			if (PPDName == "0") { AdminHandle(); }
			if (PPDName == "cancel") { AdminHandle(); }
			string searchPPDName_query = "select * from pusatdermadarah where name = '" + PPDName + "' limit 1";
			const char* sPN = searchPPDName_query.c_str();
			qstate = mysql_query(conn, sPN);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				if (result->row_count == 1) //if result 1 or found
				{
					cout << "\t\t\t\t PUSAT DERMA DARAH NAME ALREADY EXIST ! ";
					goto PPDNameGate;
				}
				if (result->row_count == 0)
				{
					cout << "\n\t\t\tEnter Pusat Derma Darah Address : ";
					getline(cin, PPDAddress);
					counter = 0;
					while (counter < PPDAddress.length())
					{
						if (isupper(PPDAddress[counter]))
						{
							PPDAddress[counter] = tolower(PPDAddress[counter]);
						}
						counter++;
					}
					if (PPDAddress == "0") { AdminHandle(); }
					if (PPDAddress == "cancel") { AdminHandle(); }
					cout << "\n\n\t\t\t Is All Data Correct ? [Y/N] :";
					cin >> choice;
					if (choice == "Y" || choice == "y")
					{
						string InsertPusatDermaDarah_query = "INSERT INTO pusatdermadarah (PPDID, Name, Address) VALUES ('" + PPDID + "','" + PPDName + "', '" + PPDAddress + "')";
						const char* iPPD = InsertPusatDermaDarah_query.c_str();
						valid = mysql_query(conn, iPPD);
						if (!valid)
						{
							cout << "\n\n\n\t\t\t\t\t Pusat Derma Darah Registration Successfully";
							system("pause");
							system("cls");
							ShowPPD(1);
						}
						else
						{
							system("cls");
							cout << "\n\n\t\t\t Error Execution 1 " << mysql_errno(conn);
							system("pause");
							goto PPDIDGate;
						}
					}
					else
					{
						goto PPDIDGate;
					}
				}
			}
			else
			{
				system("cls");
				cout << "\n\n\t\t\t Error Execution 2 " << mysql_errno(conn);
				system("pause");
				goto PPDIDGate;
			}
		}
	}
	else
	{
		system("cls");
		cout << "\n\n\t\t\t Error Execution 3 " << mysql_errno(conn);
		system("pause");
		goto PPDIDGate;
	}
}

//DONE
void EditPPD()
{
	system("cls");
EPGate1:
	string ppdid, ppdname, ppdaddress;
	int counter;
	cin.ignore();
	cout << "\n\n\t\t######################################################################################################################################################\n";
	cout << "\t\t                                                          BLOOD BANK MANAGEMENT SYSTEM\n\n\n";
	cout << "\t\t                                                      MODIFY PUSAT DERMA DARAH DETAIL MENU\n";
	cout << "\n\t\t######################################################################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tEnter \"0\" To Go Back";
	cout << "\n\t\tEnter PPDID : ";
	getline(cin, ppdid);
	counter = 0;
	while (counter < ppdid.length())
	{
		if (isupper(ppdid[counter]))
		{
			ppdid[counter] = tolower(ppdid[counter]);
		}
		if (ispunct(ppdid[counter]))
		{
			cout << "\n\t\t\tINVALID CHARACTER\n";
			goto EPGate1;
		}
		counter++;
	}
	if (ppdid == "cancel")
	{
		goto EPGate1;
	}
	if (ppdid == "0")
	{
		AdminHandle();
	}
	string searchPPDID_query = "SELECT * FROM pusatdermadarah where ppdid = '" + ppdid + "' limit 1";
	const char* sPPDID = searchPPDID_query.c_str();
	qstate = mysql_query(conn, sPPDID);
	if (!qstate)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 0)
		{
			cout << "\n\t\t\t PUSAT DERMA DARAH ID DOES NOT EXIST\n";
			system("pause");
			system("cls");
			goto EPGate1;
		}
		if (result->row_count == 1)
		{
			string showppd_query = "SELECT * FROM pusatdermadarah where ppdid = '" + ppdid + "'";
			const char* sppd = showppd_query.c_str();
			qstate = mysql_query(conn, sppd);
			if (!qstate)
			{
				result = mysql_store_result(conn);
				while (row = mysql_fetch_row(result))
				{
					cout << "\n\t\t\t#######################################################################";
					cout << "\n\n\t\t\tPusat Derma Darah ID : " << row[0] << "\n";
					cout << "\n\t\t\tPusat Derma Darah Name: " << row[1] << "\n";
					cout << "\n\t\t\tPusat Derma Darah Address : " << row[2] << "\n\n";
					cout << "\t\t\t#######################################################################\n\n";
				}
			}
			cin.ignore();
			cout << "\n\t\tEnter Pusat Derma Darah Name : ";
			getline(cin, ppdname);
			counter = 0;
			while (counter < ppdname.length())
			{
				if (isupper(ppdname[counter]))
				{
					ppdname[counter] = tolower(ppdname[counter]);
				}
				counter++;
			}
			if (ppdname == "cancel")
			{
				goto EPGate1;
			}
			if (ppdname == "0")
			{
				AdminHandle();
			}
			cin.ignore();
			cout << "\t\tEnter Pusat Derma Darah Addreess : ";
			getline(cin, ppdaddress);
			counter = 0;
			while (counter < ppdaddress.length())
			{
				if (isupper(ppdaddress[counter]))
				{
					ppdaddress[counter] = tolower(ppdaddress[counter]);
				}
				counter++;
			}
			if (ppdaddress == "cancel")
			{
				goto EPGate1;
			}
			if (ppdaddress == "0")
			{
				AdminHandle();
			}
			string updatePPD_query = "UPDATE pusatdermadarah SET Name='" + ppdname + "', Address='" + ppdaddress + "' WHERE ppdid = '" + ppdid + "'";
			const char* uP = updatePPD_query.c_str();
			qstate = mysql_query(conn, uP);
			if (!qstate)
			{
				cout << "\n\t\t\tUPDATE SUCCESSFULLY !\n";
				system("pause");
				system("cls");
				ShowPPD(1);
			}
			else
			{
				cout << "ERROR IN EXECUTION 1 : " << mysql_errno(conn) << endl;
				system("pause");
				goto EPGate1;
			}
		}
	}
	else
	{
		cout << "ERROR IN EXECUTION 2 : " << mysql_errno(conn) << endl;
		system("pause");
		goto EPGate1;
	}
}

//DONE
void deletePPD() {
dPPD:
	system("cls");
	string ppdid, choice;
	cout << "\n\n\t#########################################################################################################\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t BLOOD BANK MANAGEMENT SYSTEM\t\t\t\t        #\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#\t\t\t\t\tDELETE PUSAT DERMA DARAH MENU      \t\t\t\t#\n";
	cout << "\t#\t\t\t\t\t\t\t\t\t\t\t\t\t#\n";
	cout << "\t#########################################################################################################\n";
	cout << "\t\t" << date_time << "\n";
	cout << "\t\tEnter \"0\" To Go Back";
	cout << "\t\tENTER PUSAT DERMA DARAH ID\n";
	cin.ignore();
	cout << "\t\tPPD ID: ";
	getline(cin, ppdid);
	int counter = 0;
	while (counter < ppdid.length())
	{
		if (isupper(ppdid[counter]))
		{
			ppdid[counter] = tolower(ppdid[counter]);
		}
		counter++;
	}
	if (ppdid == "0")
	{
		AdminHandle();
	}
	string searchOrder_query = "SELECT * FROM `pusatdermadarah` where PPDID = '" + ppdid + "'";
	const char* sO = searchOrder_query.c_str();
	valid = mysql_query(conn, sO);
	if (!valid)
	{
		result = mysql_store_result(conn);
		if (result->row_count == 1) //if result 1 or found
		{
			while (row = mysql_fetch_row(result))
			{
				cout << "\n\t\t#############################################################################################";
				cout << "\n\t\t\tPPD ID : " << row[0];
				cout << "\n\t\t\tPPD NAME :" << row[1];
				cout << "\n\t\t\tPPD ADDRESS : " << row[2];
				cout << "\n\t\t#############################################################################################";
			}
			cout << "\n\n\t\t\t\t\t\t  ARE YOU SURE WANT TO DELETE ? [Y/N] : ";
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{

				string deleteorder_query = "DELETE FROM `pusatdermadarah` WHERE PPDID = '" + ppdid + "'";
				const char* dO = deleteorder_query.c_str();
				valid = mysql_query(conn, dO);
				if (!valid)
				{
					cout << "\t\t\t\t\t\t  PUSAT DERMA DARAH DELETED SUCCESSFULLY !\n";
					system("pause");
					system("cls");
					ShowPPD(1);
				}

			}
			else {
				AdminHandle();
			}
		}
		else
		{
			cout << "\t\t\t\t\t\t PUSAT DERMA DARAH ID DOES NOT EXIST !\n";
			system("pause");
			system("cls");
			goto dPPD;
		}
	}
}