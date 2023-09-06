/****************************************************************
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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//    ***holds llist class methods called from user_interface***
//
****************************************************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

#include "record.h"
#include "llist.h"

using namespace std;

/**********************************************
//
//  Function name:    llist
//
//  DESCRIPTION:
//    ***llist constructor***
//
//  Parameters:       none
//
//  Return values:    none
//
**********************************************/

llist::llist()
{
    strcpy(this->filename, "myfile.txt");
    start = NULL;
    readfile();
}

/*********************************************
//
//  Function name:    llist
//
//  DESCRIPTION:
//    ***llist constructor, user chose filename***
//
//  Parameters:       none
//
//  Return values:    none
//
*********************************************/

llist::llist(char userfile[])
{
    strcpy(this->filename, userfile);
    start = NULL;
    readfile();
}

/*******************************************
//
//  Function name:    ~llist
//
//  DESCRIPTION:
//    ***llist destructor***
//
//  Parameters:       none
//
//  Return values:    none
//
*******************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/**********************************************************************
//
//  Function name:    addRecord
//
//  DESCRIPTION:
//    ***adds record to database record list***
//
//  Parameters:       accountNum (int) : account number of record to add
//                    name (char[]) : name on record adding
//                    address(char[]) : address on record adding
//
//  Return values:    none
//
************************************************************************/

void llist::addRecord(int accountNum, char name[], char address[])
{
    int done;
    struct record * current;
    struct record * next;
    struct record * temp;
    struct record * toAdd;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****addRecord is running*****" << endl;
    cout << "account number is: " << accountNum << endl;
    cout << "account name: " << name << endl;
    cout << "address: " << address << endl;
    cout << "********************************\n" << endl;
    #endif

    done = 0;
    current = start;

    toAdd = new struct record;

    toAdd->accountno = accountNum;
    strcpy(toAdd->name, name);
    strcpy(toAdd->address, address);

    /*empty list*/
    if (start == NULL)
    {
        start = toAdd;
        toAdd->next = NULL;
    }

    /*insert before start*/
    else if ((toAdd->accountno) <= ((start)->accountno))
    {
        temp = start;
        start = toAdd;
        toAdd->next = temp;
    }

    /*insert after current*/
    else if ((toAdd->accountno) > (current->accountno))
    {
        next = current->next;

        while (done == 0)
        {
            /*insert at end*/
            if (next == NULL)
            {
                current->next = toAdd;
                toAdd->next = NULL;

                done = 1;
            }

            /*insert after current*/
            else if ((next->accountno) > (toAdd->accountno))
            {
                temp = next;
                current->next = toAdd;
                toAdd->next = temp;

                done = 1;
            }

            /*iterate to next*/
            else
            {
                current = current->next;
                next = next->next;
            }
        }
    }
}

/****************************************************************
//
//  Function name:    findRecord
//
//  DESCRIPTION:
//    ***find record with matching account number to user input***
//
//  Parameters:       targetAcctNum (int) : account number to search
//
//  Return values:    0 : success, found account and print info
//                    -1 : unsuccessful, account no found
//
****************************************************************/

int llist::findRecord(int targetAcctNum)
{
    struct record * current;
    int result;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****findRecord is running*****" << endl;
    cout << "target account number is: " << targetAcctNum << endl;
    cout << "*******************************\n" << endl;
    #endif

    current = start;
    result = -1;

    /*non-empty list*/
    if (current != NULL)
    {
        while (current != NULL)
        {
            if (current->accountno == targetAcctNum)
            {
                cout << "Account number: " << current->accountno << endl;
                cout << "Name: " << current->name << endl;
                cout << "Address: " << current->address << endl << endl;

                result = 0;
            }
            current = current->next;
        }
    }

    /*empty list*/
    else
    {
        cout << "ERROR! No records exist.\n" << endl;
    }

    return result;
}

/**************************************************************
//
//  Function name:    printAllRecords
//
//  DESCRIPTION:
//    ***print all records from database***
//
//  Parameters:       none
//
//  Return Values:    none
//
***************************************************************/

void llist::printAllRecords()
{
    struct record * current;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****printAllRecords is running*****" << endl;
    cout << "*******************************\n" << endl;
    #endif

    current = start;

    /*non-empty list*/
    if (current != NULL)
    {
        while (current != NULL)
        {
            cout << "Account numer: " << current->accountno << endl;
            cout << "Name: " << current->name << endl;
            cout << "Address: " << current->address << endl << endl;

            current = current->next;
        }
    }

    /*empty list*/
    else
    {
        cout << "No records exist.\n" << endl;
    }
}

/*************************************************************
//
//  Function name:    deleteRecord
//
//  DESCRIPTION:
//    ***delete record with account number of user input***
//
//  Parameters:       targetAcctNum (int) : acccount number of record to delete
//
//  Return values:    0 : success, deleted records at target account num
//                    -1 : unsuccessful, records not deleted
//
*************************************************************/

int llist::deleteRecord(int targetAcctNum)
{
    struct record * current;
    struct record * next;
    struct record * prev;
    struct record * temp;
    int result;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****deleteRecord is running*****" << endl;
    cout << "Account number is: " << targetAcctNum << endl;
    cout << "********************************\n" << endl;
    #endif

    result = -1;
    current = start;
    prev = NULL;

    while (current != NULL)
    {
        /*act num found, delete*/
        if (targetAcctNum == current->accountno)
        {
            next = current->next;

            /*delete first*/
            if (current == start)
            {
                temp = current;
                start = next;
                current = current->next;

                delete(temp);
                prev = NULL;
                result = 0;
            }

            /*delete anything else*/
            else
            {
                temp = current;
                prev->next = next;
                current = current->next;

                delete(temp);
                result = 0;
            }
        }

        /*iterate to next*/
        else
        {
            prev = current;
            current = current->next;
        }
    }
    return result;
}

/*************************************************************
//
//  Function name:    readfile
//
//  DESCRIPTION:
//    ***adds records from file into database***
//
//  Parameters:       none
//
//  Return values:    0 : success
//                    -1 : unsuccessful
//
*************************************************************/

int llist::readfile()
{
    int result;
    int accountNum;
    char name[30];
    char address[50];
    string strname;
    string straddress;
    string trash;

    ifstream myfile;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****readfile is running*****" << endl;
    cout << "******************************\n" << endl;
    #endif

    myfile.open(filename);
    result = 0;

    if (myfile.is_open())
    {
        /*read in acct num in while condition*/
        while (myfile >> accountNum)
        {
            /*scan in name and address, change back to addRecord parameters*/
            /*clear newline*/
            getline(myfile, trash);

            getline(myfile, strname);
            strcpy(name, strname.c_str());

            getline(myfile, straddress, '#');
            strcpy(address, straddress.c_str());

            llist::addRecord(accountNum, name, address);
        }
        myfile.close();
    }
    else
    {
        result = -1;
    }
    return result;
}

/*************************************************************
//
//  Function name:    writefile
//
//  DESCRIPTION:
//    ***write records into file***
//
//  Parameters:       none
//
//  Return values:    0 : success
//                    -1 : unsuccessful
//
*************************************************************/

int llist::writefile()
{
    int result;
    struct record * current;

    ofstream myfile;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****writefile is running*****" << endl;
    cout << "*******************************\n" << endl;
    #endif

    current = start;
    result = 0;
    myfile.open(filename);

    if (myfile.is_open())
    {
        while (current != NULL)
        {
            myfile << current->accountno << endl;
            myfile << current->name << endl;
            myfile << current->address;
            myfile << "#" << endl;

            current = current->next;
        }
        myfile.close();
    }
    else
    {
        result = -1;
    }
    return result;
}

/***************************************************************
//
//  Function name:    cleanup
//
//  DESCRIPTION:
//    ***free all space on heap and set start to NULL***
//
//  Paremeters:       none
//
//  Return values:    none
//
****************************************************************/

void llist::cleanup()
{
    struct record * current;
    struct record * temp;

    #ifdef DEBUG
    cout << "\n**********DEBUG MODE**********" << endl;
    cout << "*****cleanup is running*****" << endl;
    cout << "******************************\n" << endl;
    #endif

    current = start;

    while (current != NULL)
    {
        temp = current;
        current = current->next;

        delete(temp);
    }
    start = NULL;
}

/****************************************************************
//
//  Function name:    operator<<
//
//  DESCRIPTION:
//    ***overload << operator to print contents of entire database***
//
//  Parameters:       mylist (ostream&) : out stream writing to
//                    const llist& (list) : reference to database
//
//  Return values:    mylist : out stream
//
****************************************************************/

ostream& operator<<(ostream& mylist, const llist& list)
{
    struct record * current;   
    current = list.start;

    if (current != NULL)
    {
        while (current != NULL)
        {
            mylist << "Account numer: " << current->accountno << endl;
            mylist << "Name: " << current->name << endl;
            mylist << "Address: " << current->address << endl << endl;

            current = current->next;
        }
    }

    /*empty list*/
    else
    {
        cout << "No records exist.\n" << endl;
    }
    return mylist;      
}
