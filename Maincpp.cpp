
/*--------------------------------------------------------------------------------------------------------------------------------
 | This program is designed by Lean Wei Liang, Tan Teck Song, Seow Kai Sheng and Tan Yuan Jie using Microsoft Visual Studio 2019 |
 --------------------------------------------------------------------------------------------------------------------------------*/


/*--------------------
 |     Libraries     |		
 --------------------*/

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#ifndef _INC_WINDOWS //This library is only available for Window OS
#include<windows.h>  // For Sleep() and Change the colour of output words
#endif

#define GUEST_SIZE 1000
using namespace std;

//Set console text colour command
HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

/*---------------------------
 |     Global Variables     |
 ---------------------------*/

//For date information structure
typedef struct
{
	int day;
	int month;
	int year;
}RESERVE_DATE;

//For guest information structure
typedef struct
{
	char no[50];
	char name[100];
	RESERVE_DATE date_reserve;
	char time[100];
	int num_guest;
	char contact_info[100];
}DATA;


/*------------------------------
 |     Function Prototypes     |
 ------------------------------*/

//Display Menu
void main_menu();

//Function 1 > List
void display_list(DATA guest[], int index, char choice[], bool title_sleep);

//Function 2 > Search for Availability
void check_availability(DATA guest[], int index, char choice[], bool title_sleep);

//Function 3 > Update Reservation Record
void update_reservation_record(DATA guest[], int index, char choice[], bool title_sleep);
void add_reservation_record(DATA guest[], int index, char choice[], bool title_sleep);
void delete_reservation_record(DATA guest[], int index, char choice[], bool title_sleep);

//Function 4 > Advance Search
void advance_search(DATA guest[], int index, char choice[], bool title_sleep);

//Function 5 > Exit
void exit();

//Display Title header
void header(char title[], int num_setw1, int num_setw2, int num_i, bool title_sleep);
void small_header();

//Prompt and get option to ask user to choose for returning to main menu or exiting the program.
char option();


/*------------------------
 |     Main Function     |
 -------------------------*/

int main(void)
{
	char  choice[5] = { 0 }; // choice[5] is for repeating the main function
	do
	{
		system("mode 150"); //Maximize the output screen for better view

		//Declaration of Variable
		char opt[5]; // opt[5] is to choose the menu option 
		int index = 1;
		bool delay = true;
		DATA guest[GUEST_SIZE];

		//Display Main Menu
		main_menu();

		//Read text file
		ifstream in_file("list.txt");

		if (in_file)
		{
			while (in_file)
			{
				if (in_file.peek() == '\n')
					in_file.ignore(256, '\n');
				in_file.getline(guest[index].no, 50);
				in_file.getline(guest[index].name, 100);
				in_file >> guest[index].date_reserve.day >> guest[index].date_reserve.month
					>> guest[index].date_reserve.year >> guest[index].time >> guest[index].num_guest >> guest[index].contact_info;
				if (in_file.eof()) break;
				index++;
			}

			in_file.close(); //Close text file

			//Prompt and get menu option
			do
			{
				cout << "\t\t\t\t\t\tOption [1 - 5]: ";
				cin >> opt;

				if (strlen(opt) > 1 || opt[0] < '1' || opt[0] > '5')
					cout << "\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\tPlease enter valid option from '1' to '5'.\n\n";
			} while (strlen(opt) > 1 || opt[0] < '1' || opt[0] > '5');


			switch (opt[0])
			{
			case '1':	// option 1 is to display list of reservation records
				display_list(guest, index, choice, delay);
				break;
			case '2':	//option 2 is to search for availability
				check_availability(guest, index, choice, delay);
				break;
			case '3':	//option 3 is to update reservation record which includes add and delete reservation record
				update_reservation_record(guest, index, choice, delay);
				break;
			case '4':	//option 4 is to search for keywords
				advance_search(guest, index, choice, delay);
				break;
			}

		}

		else
		{
			//Set console text colour to Green
			SetConsoleTextAttribute(colour, 2);
			cout << "\t\t\t\t\t\tError!!! The text file is missing!\n\t\t\t\t\t\tThe program cannot run if the text file is not found.\n\n";
			//Set console text colour back to White
			SetConsoleTextAttribute(colour, 7);
			exit(100); //Exit if no text file is found
		}
	} while (choice[0] == '1');

	exit();  //Exit the program
	return 0;
}

/*-----------------------
 |     Display Menu     |
 -----------------------*/

void main_menu()
{
	system("cls"); //Clear screen

	//Design of Title
	char title1[] = "TEPPANYAKI JAPANESE RESTAURANT";
	char title2[] = "-RESERVATION RECORDS SYSTEM-";

	SetConsoleTextAttribute(colour, 13); //Set console text colour to Purple
	cout << endl << endl << setw(60);
	for (int i = 0; i < strlen(title1); i++)
	{
		cout << title1[i];
		Sleep(50);
	}
	cout << endl << setw(61);
	for (int i = 0; i < strlen(title2); i++)
	{
		cout << title2[i];
		Sleep(50);
	}

	//Design of Menu
	SetConsoleTextAttribute(colour, 3); //Set console text colour to Blue
	cout << endl << setw(48);
	for (int i = 0; i < 51; ++i)
		cout << (char)220;
	cout << endl << setw(48) << (char)219 << "                     Main Menu                   " << (char)219;
	cout << "\n\t\t\t\t\t       |                    -----------                  |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |  >> 1.  List                                    |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |  >> 2.  Search for availability                 |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |  >> 3.  Update reservation record               |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |  >> 4.  Advanced search                         |";
	cout << "\n\t\t\t\t\t       |                                                 |";
	cout << "\n\t\t\t\t\t       |  >> 5.  Exit                                    |";
	cout << "\n\t\t\t\t\t       " << (char)219 << "                                                 " << (char)219;
	cout << endl << setw(48);
	for (int i = 0; i < 51; ++i)
		cout << (char)223;
	cout << endl << endl << endl;

	SetConsoleTextAttribute(colour, 7); //Set console text colour back to White
	return;
}

/*---------------
 |     List     |
 ---------------*/

void display_list(DATA guest[], int index, char choice[], bool title_sleep)
{
	system("cls"); //Clear screen

	//Design of Title
	char title[] = "List of Reservation Records";
	int num_setw1 = 57, num_i = 31, num_setw2 = 60;
	header(title, num_setw1, num_setw2, num_i, title_sleep);
	SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green

	//Declaration of Variables
	int a = 1;

	//Display list title
	cout << "\t" << left << setw(10) << "NO" << setw(24) << "NAME" <<right<< setw(12) << "DATE" << setw(28)
		<< "SESSION" << setw(32) << "NUMBER OF GUEST"<<setw(18)<< "CONTACT INFO" << endl;
	cout << "\t---------------------------------------------------------------------------------------------------------------------------------" << endl;

	//Display reservation information
	while (a <= index)
	{
		cout << "\t" << left << setw(4) << guest[a].no << "\t" << setw(25) << guest[a].name << "\t";
		if (guest[a].date_reserve.day > 9)
			cout << guest[a].date_reserve.day;
		else
			cout << "0" << guest[a].date_reserve.day;
		cout << "/";
		if (guest[a].date_reserve.month > 9)
			cout << guest[a].date_reserve.month;
		else
			cout << "0" << guest[a].date_reserve.month;
		cout << "/" << setw(4) << guest[a].date_reserve.year << "\t\t" << setw(15)
			<< guest[a].time << "\t\t\t" << setw(4) << guest[a].num_guest << "\t\t" << setw(12) << guest[a].contact_info << endl;
		a++;
	}
	SetConsoleTextAttribute(colour, 7); //Set console text colour back to White

	choice[0] = option(); //Ask user if the user want to return to main menu or exit the program.
	return;
}

/*----------------------------------
 |     Search For Availability     |
 ----------------------------------*/

void check_availability(DATA guest[], int index, char choice[], bool title_sleep)
{
	char ans[5]; //ans[5] is for repeating the function 

	do
	{
		system("cls");	//Clear screen

		//Design of Title
		char title[] = "Search For Availability";
		int num_setw1 = 59, num_setw2 = 62, num_i = 27;
		header(title, num_setw1, num_setw2, num_i, title_sleep);

		//Declaration of Variables
		char opt[5];	//To get option from user to or not to perform function add_reservation_record 
		int  total_date = 0;	//Total number of guest for four session in one day
		int total_session1 = 0, total_session2 = 0, total_session3 = 0, total_session4 = 0;
		int seat_left1, seat_left2, seat_left3, seat_left4;
		int day1, month1, year1; 
		int b = 1, i = 1;	//Counter
		const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	//Days per every month

		char session1[100] = "11.00AM-12.30PM";
		char session2[100] = "12.30PM-02.00PM";
		char session3[100] = "05.00PM-06.30PM";
		char session4[100] = "06.30PM-08.00PM";

		SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
		cout << setw(92) << "Please enter the reservation date " << endl;
		SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White

		//Prompt and get date
		do
		{
			
			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tDay [1 - 31]: ";
				cin >> day1;
				if (!cin || day1 < 1 || day1 > 31)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe day is only valid from 1 to 31.\n\n";
			} while (!cin || day1 < 1 || day1 > 31);

			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tMonth [1 - 12]: ";
				cin >> month1;
				if (!cin || month1 < 1 || month1 > 12)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe month is only valid from 1 to 12.\n\n";
			} while (!cin || month1 < 1 || month1 > 12);

			if (day1 > monthDays[month1 - 1])
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThis month only contains " << monthDays[month1 - 1] << " days.\n\n";
		} while (day1 > monthDays[month1]);

		do
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\n\t\t\t\t\t\t\tYear [2019 - 2023]: ";
			cin >> year1;
			if (!cin || year1 < 2019 || year1 > 2023)
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe year is only valid from 2019 to 2023.\n\n";
		} while (!cin || year1 < 2019 || year1 > 2023);

		//Compute total number of guest for four session in one day
		while (b <= index)
		{
			if (guest[b].date_reserve.day == day1 && guest[b].date_reserve.month == month1 && guest[b].date_reserve.year == year1)
				total_date += guest[i].num_guest;
			b++;
		}

		if (total_date < 32)
		{
			SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
			cout << "\n\t\t\t\t\t\tThe date you want to reserve is available.\n";
			cout << "\t\t\t\t\t\tThe session and seats left is as follow:\n\n";
			cout << "\t\t\t\t\t\t\tSession\t\t" << "\tSeat\n";

			for (int k = 1; k <= index; k++)
			{
				if (guest[k].date_reserve.day == day1 && guest[k].date_reserve.month == month1 && guest[k].date_reserve.year == year1)
				{
					if ((strcmp(guest[k].time, session1)) == 0)
						total_session1 += guest[k].num_guest;
					else if ((strcmp(guest[k].time, session2)) == 0)
						total_session2 += guest[k].num_guest;
					else if ((strcmp(guest[k].time, session3)) == 0)
						total_session3 += guest[k].num_guest;
					else if ((strcmp(guest[k].time, session4)) == 0)
						total_session4 += guest[k].num_guest;
				}

			}

			//Compute seat left for each session
			seat_left1 = 8 - total_session1;
			seat_left2 = 8 - total_session2;
			seat_left3 = 8 - total_session3;
			seat_left4 = 8 - total_session4;

			//Display seat left for each session
			cout << "\t\t\t\t\t\t\t" << session1 << "\t\t" << setw(3) << seat_left1 << endl;
			cout << "\t\t\t\t\t\t\t" << session2 << "\t\t" << setw(3) << seat_left2 << endl;
			cout << "\t\t\t\t\t\t\t" << session3 << "\t\t" << setw(3) << seat_left3 << endl;
			cout << "\t\t\t\t\t\t\t" << session4 << "\t\t" << setw(3) << seat_left4 << endl;

			SetConsoleTextAttribute(colour, 7);		//Set console text colour to White
		}
		else
			cout << "\n\t\t\t\t\t\tThe date you want to reserve is not available.\n";

		// Ask user if the user want to proceed to add reservation record or not
		do
		{
			cout << "\n\n\t\t\t\t\tDo you want to proceed your reservation? [ 1 - yes / 0 - no ]: ";
			cin >> opt;

			if (strlen(opt) > 1 || opt[0] < '0' || opt[0] > '1')
				cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '1'.\n\n";
		} while (strlen(opt) > 1 || opt[0] < '0' || opt[0] > '1');

		if (opt[0] == '1')
			add_reservation_record(guest, index, choice, title_sleep);
		else
		{
			// Ask user if the user want to repeat the funciton or not
			do
			{
				cout << "\n\n\t\t\t\t\tDo you want repeat Search For Availability again? [ 1 - yes / 0 - no ]: ";
				cin >> ans;

				if (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1')
					cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '1'.\n\n";
			} while (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1');
		}
	} while (ans[0] == '1');

	choice[0] = option(); // Ask user if the user want to return to main menu or exit the program.

	return;
}

/*------------------------------------
 |     Update Reservation Record     |
 ------------------------------------*/

//Menu of Update Reservation Record
void update_reservation_record(DATA guest[], int index, char choice[], bool title_sleep)
{
	//Declaration of Variables
	char decision[5];

	system("cls");	//Clear screen

	//Design of Title
	char title[] = "Update Reservation Record";
	int num_setw1 = 58, num_setw2 = 61, num_i = 29;
	header(title, num_setw1, num_setw2, num_i, title_sleep);
	small_header();

	//Ask user if the user want to return to main menu, add or delete reservation records
	do
	{
		cout << "\n\n\t\t\t\t\tPlease key in your choice[0 - 2]: ";
		cin >> decision;
		if (strlen(decision) > 1 || decision[0]<'0' || decision[0]>'2')
			cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '2'.\n\n";
	} while (strlen(decision) > 1 || decision[0]<'0' || decision[0]>'2');

	if (decision[0] == '0')		//Option 0 is to return to main menu
		choice[0] = '1';
	else if (decision[0] == '1')	//Option 1 is to proceed to function add_reservation_record
		add_reservation_record(guest, index, choice, title_sleep);	
	else if (decision[0] == '2')	//Option 2 is to proceed to function delete_reservation_record
		delete_reservation_record(guest, index, choice, title_sleep);

	if (decision[0] != '0')
		choice[0] = option();	// Ask user if the user want to return to main menu or exit the program.

	return;
}

//Add Reservation Record
void add_reservation_record(DATA guest[], int index, char choice[], bool title_sleep)
{
	char ans[5];	//ans[5] is for repeating the function 

	do
	{
		system("cls");	//Clear screen

		//Design of Title
		char title[] = "Add Reservation Record";
		int num_setw1 = 59, num_setw2 = 62, num_i = 26;
		header(title, num_setw1, num_setw2, num_i, title_sleep);
		SetConsoleTextAttribute(colour, 7);	//Set console text colour to White

		//Declaration of Variables
		int num_guest1;
		char time1[20];
		int total = 0; //Total number of guest per day
		int c = 1;	//Counter
		int day1, month1, year1, tdy_day, tdy_mth, tdy_year, total_day, day_per_year;
		const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };	//Days per every month
		ofstream out_file("list.txt", ios::app);
		SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
		cout << setw(100) << "The session available for Tepanyaki Restaurant \n\n\n";
		cout << setw(109) << "11.00AM-12.30PM, 12.30PM-2:00PM, 5.00PM-6.30PM and 6.30PM-8.00PM\n\n\n";
		cout << setw(100) << "*The reservation only available 3 days in advance*\n\n\n";
		cout << setw(86) << "Please enter the today's date " << endl;
		SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White
		
		//Prompt and get today's date

		do
		{
			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tDay [1 - 31]: ";
				cin >> tdy_day;
				if (!cin || tdy_day < 1 || tdy_day > 31)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe day is only valid from 1 to 31.\n\n";
			} while (!cin || tdy_day < 1 || tdy_day > 31);

			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tMonth [1 - 12]: ";
				cin >> tdy_mth;
				if (!cin || tdy_mth < 1 || tdy_mth > 12)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe month is only valid from 1 to 12.\n\n";
			} while (!cin || tdy_mth < 1 || tdy_mth > 12);
			if (tdy_day > monthDays[tdy_mth - 1])
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThis month only contains " << monthDays[tdy_mth - 1] << " days.\n\n";
		} while (tdy_day > monthDays[tdy_mth - 1]);

		do
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\n\t\t\t\t\t\t\tYear [2019 - 2023]: ";
			cin >> tdy_year;
			if (!cin || tdy_year < 2019 || tdy_year > 2023)
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe year is only valid from 2019 to 2023.\n\n";
		} while (!cin || tdy_year < 2019 || tdy_year > 2023);

		SetConsoleTextAttribute(colour, 2); //Set console text colour to Green
		cout << endl << endl << setw(92) << "Please enter the date you want to reserve " << endl;
		SetConsoleTextAttribute(colour, 7);	//Set console text colour to White

		//Prompt and get date for reservation

		do
		{
			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tDay [1 - 31]: ";
				cin >> day1;
				if (!cin || day1 < 1 || day1 > 31)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe day is only valid from 1 to 31.\n\n";
			} while (!cin || day1 < 1 || day1 > 31);

			do
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "\n\t\t\t\t\t\t\tMonth [1 - 12]: ";
				cin >> month1;
				if (!cin || month1 < 1 || month1 > 12)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe month is only valid from 1 to 12.\n\n";
			} while (!cin || month1 < 1 || month1 > 12);

			if (day1 > monthDays[month1 - 1])
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThis month only contains " << monthDays[month1 - 1] << " days.\n\n";
		} while (day1 > monthDays[month1 - 1]);

		do
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "\n\t\t\t\t\t\t\tYear [2019 - 2023]: ";
			cin >> year1;
			if (!cin || year1 < 2019 || year1 > 2023)
				cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe year is only valid from 2019 to 2023.\n\n";
		} while (!cin || year1 < 2019 || year1 > 2023);

		
		if (((day1 + month1 * monthDays[month1] + year1 * 365) - (tdy_day + tdy_mth * monthDays[month1] + year1 * 365)) < 3)
			cout << "\n\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe reservation only available 3 days in advance.\n\n";
		else
		{
			//Prompt and get reservation session
			do
			{
				cout << "\n\t\t\tTime [1 >> 11.00AM-12.30PM , 2 >> 12.30PM-2:00PM , 3 >> 5.00PM-6.30PM , 4 >> 6.30PM-8.00PM]: ";
				cin >> time1;
				if (strlen(time1) > 1 || time1[0] < '1' || time1[0] > '4')
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tPlease enter valid option from '1' to '4'.\n\n";
			} while (strlen(time1) > 1 || time1[0] < '1' || time1[0] > '4');

			if (time1[0] == '1')
				strcpy_s(time1, "11.00AM-12.30PM");
			else if (time1[0] == '2')
				strcpy_s(time1, "12.30PM-02:00PM");
			else if (time1[0] == '3')
				strcpy_s(time1, "05.00PM-06.30PM");
			else if (time1[0] == '4')
				strcpy_s(time1, "06.30PM-08.00PM");

			//Prompt and get number of guest for reservation

			do
			{
				cout << "\n\t\t\t\t\t\t\tNumber of guest [ Max = 8 ]: ";
				cin >> num_guest1;
				if (!cin || num_guest1 < 1 || num_guest1 > 8)
					cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tPlease enter valid number of guest from 1 to 8.\n\n";
			} while (!cin || num_guest1 < 1 || num_guest1 > 8);

			//Compute total number of guest in the session that is selected by the user
			while (c <= index)
			{
				if (guest[c].date_reserve.day == day1 && guest[c].date_reserve.month == month1 && guest[c].date_reserve.year == year1 && strcmp(guest[c].time, time1) == 0)
					total += guest[c].num_guest;
				c++;
			}

			total += num_guest1;

			if (total <= 8)
			{
				SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
				cout << "\n\n" << setw(87) << "The time reserved is available.<3" << endl << endl;
				cin.ignore(10000, '\n');
				SetConsoleTextAttribute(colour, 7);		//Set console text colour to White

				index++;
				
				//Prompt and get name of guest for reservation

				bool error_name;
				do
				{
					error_name = false;
					cout << "\t\t\t\t\t\t\tName: ";
					cin.getline(guest[index].name, 100);
					
					for (int i = 0; i < strlen(guest[index].name); i++)
					{
						if (guest[index].name[i] != ' ')
							if (isdigit(guest[index].name[i]) || ispunct(guest[index].name[i]))
								error_name = true;
					}
					if (error_name == true)
						cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe name must contain only alphabet.\n\n";

				} while (error_name == true);

				//Prompt and get telephone number of guest for reservation

				bool error_telephone;
				do
				{
					error_telephone = false;
					cout << "\n\t\t\t\t\t\t\tTelephone number [xxx-xxxxxxx]: ";
					cin >> guest[index].contact_info;
					if (strlen(guest[index].contact_info) != 11)
						error_telephone = true;
					for (int j = 0; j < strlen(guest[index].contact_info); j++)
					{
						if (guest[index].contact_info[j] != ' ')
							if (isalpha(guest[index].contact_info[j]) || guest[index].contact_info[3] != '-')
								error_telephone = true;
					}
					if (error_telephone == true)
						cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tThe telephone number must contain only 11 numbers and '-' after three digits.\n";

				} while (error_telephone == true);

				//Copy the user input information into the guest information variables
				guest[index].date_reserve.day = day1;
				guest[index].date_reserve.month = month1;
				guest[index].date_reserve.year = year1;
				strcpy_s(guest[index].time, time1);
				guest[index].num_guest = num_guest1;

				//Output the text file

				out_file << "\n" << index << ". \n" << guest[index].name << "\n" << guest[index].date_reserve.day << " " << guest[index].date_reserve.month << " " << guest[index].date_reserve.year << "\t\t" << guest[index].time
					<< " \t" << guest[index].num_guest << "\t\t\t" << guest[index].contact_info;


				out_file.close();	//Close text file
				SetConsoleTextAttribute(colour, 2);	//Set the console text colour to Green
				cout << "\n\n" << setw(92) << "The reservation is successfully added.\n";

			}

			else
			{
				SetConsoleTextAttribute(colour, 2);	//Set the console text colour to Green
				cout << "\n\n" << setw(91) << "The time reserved is not available :( " << endl;
			}

			SetConsoleTextAttribute(colour, 7);	//Set the console text colour back to White
		}

		//Ask user if the user want to repeat the function or not

		do
		{
			cout << "\n\n\t\t\t\t\tDo you want repeat Add Reservation Record again? [ 1 - yes / 0 - no ]: ";
			cin >> ans;

			if (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1')
				cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '1'.\n\n";
		} while (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1');
	} while (ans[0] == '1');

	return;
}

//Delete reservation record
void delete_reservation_record(DATA guest[], int index, char choice[], bool title_sleep)
{
	char ans[5];	//ans[5] is for repeating the function 
	do
	{
		system("cls");

		//Design of title
		char title[] = "Delete Reservation Record";
		int num_setw1 = 58, num_setw2 = 61, num_i = 29;
		header(title, num_setw1, num_setw2, num_i, title_sleep);
		SetConsoleTextAttribute(colour, 7);

		//Declaration of variables
		int e = 1, count = 1;	//Counter
		char name1[100];
		DATA temp_guest[GUEST_SIZE];
		ofstream out_file("updatedlist.txt");
		SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green

		//Display list of reservation records
		cout << "\t" << left << setw(10) << "NO" << setw(24) << "NAME" << right << setw(12) << "DATE" << setw(28)
			<< "SESSION" << setw(32) << "NUMBER OF GUEST" << setw(18) << "CONTACT INFO" << endl;
		cout << "\t---------------------------------------------------------------------------------------------------------------------------------" << endl;

		for (int a = 1; a <= index; a++)
		{
			cout << "\t" << left << setw(4) << guest[a].no << "\t" << setw(25) << guest[a].name << "\t";
			if (guest[a].date_reserve.day > 9)
				cout << guest[a].date_reserve.day;
			else
				cout << "0" << guest[a].date_reserve.day;
			cout << "/";
			if (guest[a].date_reserve.month > 9)
				cout << guest[a].date_reserve.month;
			else
				cout << "0" << guest[a].date_reserve.month;
			cout << "/" << setw(4) << guest[a].date_reserve.year << "\t\t" << setw(15)
				<< guest[a].time << "\t\t\t" << setw(4) << guest[a].num_guest << "\t\t" << setw(12) << guest[a].contact_info << endl;
		}

		SetConsoleTextAttribute(colour, 7);	//Set console text colour back to White

		//Prompt and get name of guest to delete reservation record of that particular guest
		cin.ignore(256, '\n');
		cout << "\n\n\t\t\t\t\t\t\tEnter the name of the guest: ";
		cin.getline(name1, 100);

		//Overwrite the reservation informations except for the reservation information of the guest whose name is same as the name entered by the user
		while (e <= index)
		{
			if (strcmp(guest[e].name, name1) != 0)
			{
				if (e <= index)
					out_file << "\n" << count << ". \n" << guest[e].name << "\n" << guest[e].date_reserve.day << " " << guest[e].date_reserve.month << " " << guest[e].date_reserve.year << "\t\t"
					<< guest[e].time << " \t" << guest[e].num_guest << "\t\t\t" << guest[e].contact_info;
				count++;
			}
			e++;
		}

		out_file.close();	//Close text file
		SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
		remove("list.txt");		//Remove old text file
		rename("updatedlist.txt", "list.txt");	//Rename new text file

		if (index < count)
		{
			cout << "\n\n\t\t\t\t\t\t\t The reservation is not found.";
			cout << "\n\t\t\t\tPlease make sure the name entered is correct (Capital letter must be same as the list).";
			SetConsoleTextAttribute(colour, 7);	//Set console text colour back to White

			//Ask user if the user want to repeat the function or not
			do
			{
				cout << "\n\n\t\t\t\t\tDo you want repeat Delete Reservation Record again? [ 1 - yes / 0 - no ]: ";
				cin >> ans;

				if (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1')
					cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '1'.\n\n";
			} while (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1');
			SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green
		}
		else
		{
			cout << "\n\n\t\t\t\t\t\t\t  The reservation is deleted.";
			ans[0] = '0';	
		}

		cout << "\n\n\n";
	} while (ans[0] == '1');
	SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White

	return;
}

/*--------------------------
 |     Advanced Search     |
 --------------------------*/

void advance_search(DATA guest[], int index, char choice[], bool title_sleep)
{
	char ans[5];	//ans[5] is for repeating the function
	do
	{
		system("cls");	//Clear Screen

		//Design of Title
		char title[] = "Advanced Search";
		title_sleep = true;
		int num_setw1 = 62, num_setw2 = 65, num_i = 19;
		header(title, num_setw1, num_setw2, num_i, title_sleep);
		SetConsoleTextAttribute(colour, 7);		//Set console text colour to White

		//Declaration of Variables
		DATA temp[GUEST_SIZE] = { 0 };
		char keyword[50];
		char temp_keyword[50];
		bool header_flag = true;

		//Prompt and Get keyword 

		cout << "\t\t\tPlease enter the keyword [NAME / CONTACT NUMBER] : ";
		cin.ignore(1000, '\n');
		cin.getline(keyword, 50);

		//Convert the keyword entered by the user to lower case letter
		strcpy_s(temp_keyword, keyword);
		for (int i = 0; i < strlen(temp_keyword); i++)
			temp_keyword[i] = tolower(temp_keyword[i]);


		
		for (int i = 1, num = 1; i <= index; i++)
		{
			//Convert every guest name to lower case letter
			for (int j = 0; j < strlen(guest[i].name); j++)
			{
				temp[i].name[j] = guest[i].name[j];
				temp[i].name[j] = tolower(temp[i].name[j]);
			}

			//Search for match between guest name with keyword or guest contact with keyword
			char* match_name = strstr(temp[i].name, temp_keyword);
			char* match_contact = strstr(guest[i].contact_info, keyword);

			if (match_name || match_contact)
			{	
				//Display header if header_flag is true
				if (header_flag)
				{
					system("cls");	//Clear screen

					//Design of Title
					int num_setw1 = 62, num_setw2 = 65, num_i = 19;
					title_sleep = false;
					header(title, num_setw1, num_setw2, num_i, title_sleep);


					SetConsoleTextAttribute(colour, 12);	//Set console text colour to Red

					//Design of 'keyword entered' interface
					cout << setw(49) << " " << (char)218;

					for (int i = 0; i < 42; i++)
						cout << (char)196;

					cout << (char)191 << endl;

					cout << setw(49) << " " << (char)179 << "Keyword(s) Entered >> " << left << setw(20) << keyword << (char)179 << endl;

					cout << right << setw(49) << " " << (char)192;
					for (int i = 0; i < 42; i++)
						cout << (char)196;

					cout << (char)217 << endl << endl << endl;
					SetConsoleTextAttribute(colour, 2);	//Set console text colour to Green

					cout << "\t" << left << setw(10) << "NO" << setw(24) << "NAME" << right << setw(12) << "DATE" << setw(28)
						<< "SESSION" << setw(32) << "NUMBER OF GUEST" << setw(18) << "CONTACT INFO" << endl;
					cout << "\t---------------------------------------------------------------------------------------------------------------------------------" << endl;


					header_flag = false; // Make the header_flag to false in order to not display the header
				}

				//Display the matched guest information

				cout << "\t" << left << setw(4) << num << "\t" << setw(25) << guest[i].name << "\t";
				if (guest[i].date_reserve.day > 9)
					cout << guest[i].date_reserve.day;
				else
					cout << "0" << guest[i].date_reserve.day;
				cout << "/";
				if (guest[i].date_reserve.month > 9)
					cout << guest[i].date_reserve.month;
				else
					cout << "0" << guest[i].date_reserve.month;
				cout << "/" << setw(4) << guest[i].date_reserve.year << "\t\t" << setw(15)
					<< guest[i].time << "\t\t\t" << setw(4) << guest[i].num_guest << "\t\t" << setw(12) << guest[i].contact_info << endl;

				num++;	
			}

		}

		if (header_flag)
		{
			system("cls");	//Clear screen

			//Design of Title
			int num_setw1 = 63, num_setw2 = 66, num_i = 19;
			title_sleep = false;
			header(title, num_setw1, num_setw2, num_i, title_sleep);


			SetConsoleTextAttribute(colour, 12);	//Set console text colour to Red

			//Design of 'Error' interface
			cout << endl << endl;
			cout << setw(44) << " " << (char)218;

			for (int i = 0; i < 56; i++)
				cout << (char)196;

			cout << (char)191 << endl;
			cout << setw(44) << " " << (char)179 << setw(31) << " !! Error !! " << setw(26) << (char)179 << endl;
			cout << setw(44) << " " << (char)179 << setw(56) << " " << (char)179 << " " << endl;
			cout << setw(44) << " " << (char)179 << " NO RECORD WAS FOUND WITH KEYWORD >> " << left << setw(19) << keyword << (char)179 << endl;

			cout << right << setw(44) << " " << (char)192;
			for (int i = 0; i < 56; i++)
				cout << (char)196;

			cout << (char)217 << endl << endl << endl;

		}
		SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White

		//Ask user if they want to repeat function or not

		do
		{
			cout << "\n\n\t\t\t\t\tDo you want repeat Advanced Search again? [ 1 - yes / 0 - no ]: ";
			cin >> ans;

			if (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1')
				cout << "\t\t\t\t\tInvalid Input!!\n\t\t\t\t\tPlease enter valid option from '0' to '1'.\n\n";
		} while (strlen(ans) > 1 || ans[0] < '0' || ans[0] > '1');
	}while (ans[0] == '1');

	choice[0] = option();	// Ask user if the user want to return to main menu or exit the program.
	return;
}


/*---------------
 |     Exit     |
 ---------------*/

void exit()
{
	system("cls");	//Clear screen

	//Design of 'Exit' interface
	for (int i = 1; i <= 50; i++)
	{
		system("cls");	//Clear screen
		SetConsoleTextAttribute(colour, 6);	//Set console text colour to Yellow
		cout << "\n\n\n\n\n" << setw(79) << "Loading... " << endl << setw(48);
		for (int j = 1; j <= i; j++)
			cout << (char)219;
		cout << endl << setw(50) << 2 * i << "%";
		if (i > 1 && i < 10)
			cout << "\t\t\t\t Accessing Main Memory...";
		else if (i > 10 && i < 25)
			cout << "\t\t\t\t Accessing Cache...";
		else if (i > 25 && i < 50)
			cout << "\t\t\t\t Saving Changes...";
		else cout << "\t\t\t\t Complete!!\n\n";
		Sleep(150 - i * 3);
	}
	cout << setw(66) << "Thank You!!\n\n\n\n\n\n\n";
	SetConsoleTextAttribute(colour, 7);	//Set console text colour back to White
	exit(0);	//Exit the program.
}

/*-----------------
 |     Header     |
 -----------------*/

//Display Header
void header(char title[], int num_setw1, int num_setw2, int num_i, bool title_sleep)
{
	SetConsoleTextAttribute(colour, 3);	//Set console text colour to Blue

	//Design of Header
	cout << endl << endl << setw(num_setw1) << " " << (char)201;

	for (int i = 0; i < num_i; i++)
		cout << (char)205;

	cout << (char)187 << endl << endl << setw(num_setw2) << " ";

	for (int i = 0; i < strlen(title); i++)
	{
		cout << title[i];
		if (title_sleep == true)
			Sleep(30);
	}

	cout << endl << endl << setw(num_setw1) << " " << (char)200;

	for (int i = 0; i < num_i; i++)
		cout << (char)205;

	cout << (char)188 << endl << endl << endl;

	return;
}

//Display Small Header for Update Reservation Record Function
void small_header()
{
	SetConsoleTextAttribute(colour, 12);	//Set console text colour to Red

	//Design of Small Header

	cout << setw(23) << (char)218;

	for (int i = 0; i < 83; i++)
	{
		if (i == 24)
			cout << (char)191 << setw(11) << (char)218;
		else if (i == 52)
			cout << (char)191 << setw(9) << (char)218;
		else
			cout << (char)196;
	}

	cout << (char)191 << endl;

	cout << setw(23) << (char)179 << setw(25) << (char)179 << setw(11) << (char)179 << setw(28) << (char)179
		<< setw(9) << char(179) << setw(31) << (char)179 << endl;

	cout << setw(23) << (char)179 << " Return to Main Menu(0) " << (char)179 << setw(11) << (char)179
		<< " Add Reservation Record(1) " << (char)179 << setw(9) << char(179) << " Delete Reservation Record(2) " << (char)179 << endl;

	cout << setw(23) << (char)179 << setw(25) << (char)179 << setw(11) << (char)179 << setw(28) << (char)179
		<< setw(9) << char(179) << setw(31) << (char)179 << endl;

	cout << setw(23) << (char)192;

	for (int i = 0; i < 83; i++)
	{
		if (i == 24)
			cout << (char)217 << setw(11) << (char)192;
		else if (i == 52)
			cout << (char)217 << setw(9) << (char)192;
		else
			cout << (char)196;
	}
	cout << (char)217;

	SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White

	return;
}


/*-----------------
 |     Option     |
 -----------------*/

 //Prompt and get option to ask user to choose for returning to main menu or exiting the program.
char option()
{
	//Declaration of Variable
	char choice[5];

	SetConsoleTextAttribute(colour, 12);	//Set console text colour to Red

	//Design of Option interface

	cout << "\n\n\n";
	cout << right << setw(50) << (char)218;

	for (int i = 0; i < 42; i++)
		cout << (char)196;

	cout << (char)191 << endl;

	cout << setw(50) << (char)179 << "Option:" << setw(36) << (char)179 << endl;
	cout << setw(50) << (char)179 << "<1>Return to Main Menu\t<2>Exit" << setw(6) << (char)179 << endl;

	cout << right << setw(50) << (char)192;
	for (int i = 0; i < 42; i++)
		cout << (char)196;

	cout << (char)217 << endl << endl;

	SetConsoleTextAttribute(colour, 7);		//Set console text colour back to White

	//Prompt and get choice

	do
	{
		cout << "\t\t\t\t\t\t\tSelect your choice: ";
		cin >> choice;

		if (strlen(choice) > 1 || choice[0] < '1' || choice[0] > '2')
			cout << "\t\t\t\t\t\t\tInvalid Input!!\n\t\t\t\t\t\t\tPlease enter valid option from '1' to '2'.\n\n";
	} while (strlen(choice) > 1 || choice[0] < '1' || choice[0] > '2');

	return choice[0];
}

