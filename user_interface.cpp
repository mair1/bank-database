/*****************************************************************
//
//  NAME:        ***Mairi Yoshioka***
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 23, 2023
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//    ***set up user interface to display menu and prompt user
//       to choose between add, delete, find, and printall. Once
//       user chooses quit program ends***
//
*****************************************************************/

#include <iostream>
#include <string>
#include <cstring>

#include "record.h"
#include "llist.h"

using namespace std;

/************************************************************
//
//  Function name:    main
//
//  DESCRIPTION:
//    ***user interface to display menu options and calls
//       llist functions when needed***
//
//  Parameters:       argc (int) : number of arguments
//                    argv (char*[]) : array of arguments
//
//  Return values:    0 : success
//
************************************************************/

int main(int argc, char* argv[])
{
    int quitLoop;
    string choice;
    llist list;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE ON**********\n" << endl;
    #endif

    quitLoop = 1;

    if (quitLoop != 0)
    {
        cout << "This is the bank database." << endl;
        cout << "This program allows access to manage bank records.\n" << endl;
    }

    while (quitLoop != 0)
    {
        cout << "Please choose an option from the menu: \n" << endl;
        cout << "  add: will add a new record to database" << endl;
        cout << "  printall: will print all records in database" << endl;
        cout << "  find: will find records with specific account number" << endl;
        cout << "  delete: will delete existing records with specific account number" << endl;
        cout << "  quit: will quit the program" << endl;

        cout << "Enter a valid choice: \n";
        getline(cin, choice);

        /****ADD****/
        if (strncmp(choice.c_str(), "add", choice.length()) == 0)
        {
            int accountNumber;
            char accountName[40];
            string strname;
            char mailAddress[60];
            string straddress;
            string trash;

            cout << "You have chosen to add a record to database." << endl;

            /**account number**/
            cout << "Please enter account number: ";

            while (!(cin >> accountNumber) || accountNumber <= 0)
            {
                cout << "ERROR! Input was not valid.\n";
                cout << "Please enter a valid account number: " <<endl;
                cin.clear();
                getline(cin, trash);
            }
            getline(cin, trash);

            /**account name**/
            cout << "Please enter account name: ";
            getline(cin, strname);
            strcpy(accountName, strname.c_str());

            /**address**/
            cout << "Please enter addres and type # at end: " << endl;
            getline(cin, straddress, '#');
            strcpy(mailAddress, straddress.c_str());

            /*call to addRecord*/
            list.addRecord(accountNumber, accountName, mailAddress);

            cout << "Record has been added.\n" << endl;
            getline(cin, trash);
        }

        /****PRINTALL****/
        else if (strncmp(choice.c_str(), "printall", choice.length()) == 0)
        {
            cout << "You have chosen to print all records in database." << endl;

            /*call to printAllRecords*/
            list.printAllRecords();

            cout << "All records have been printed.\n" << endl;
        }

        /****FIND****/
        else if (strncmp(choice.c_str(), "find", choice.length()) == 0)
        {
            int accountNumber;
            string trash;

            cout << "You have chosen to find a record." << endl;

            /**account number**/
            cout << "Please enter account number: " << endl;

            while (!(cin >> accountNumber) || accountNumber <= 0)
            {
                cout << "ERROR! Input was not valid.\n";
                cout << "Please enter a valid account number: " << endl;
                cin.clear();
                getline(cin, trash);
            }
            getline(cin, trash);

            /*call to findRecord*/
            if (list.findRecord(accountNumber) == 0)
            {
                cout << "Record was found." << endl;
            }
            else
            {
                cout << "ERROR! Record was not found/No records exist." << endl;
            }
        }

        /****DELETE****/
        else if (strncmp(choice.c_str(), "delete", choice.length()) == 0)
        {
            int accountNumber;
            string trash;

            cout << "You have chosen to delete records." << endl;

            /**account number**/
            cout << "Please enter account number: " << endl;

            while (!(cin >> accountNumber) || accountNumber <= 0)
            {
                cout << "ERROR! Input was not valid.\n";
                cout << "Please enter a valid account number: " << endl;
                cin.clear();
                getline(cin, trash);
            }
            getline(cin, trash);

            /*call to deleteRecord*/
            if (list.deleteRecord(accountNumber) == 0)
            {
                cout << "Records have been deleted." << endl;
            }
            else
            {
                cout << "ERROR! Records do not exist/No records exist." << endl;
            }
        }

        /****QUIT****/
        else if (strncmp(choice.c_str(), "quit", choice.length()) == 0)
        {
            quitLoop = 0;
        }

        /****invalid input****/
        else
        {
            cout << "Your choice was an invalid option.\n" << endl;
        }
    }
    return 0;
}
