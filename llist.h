/******************************************************************
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
//  FILE:        llist.h
//
//  DESCRIPTION: 
//    ***llist class holding private and public variables and methods
//    and contructors and destructors***
//
******************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include "record.h"

class llist
{
    private:
    record * start;
    char filename[20];
    int readfile();
    int writefile();
    void cleanup();

    public:
    llist();
    llist(char[]);
    ~llist();
    void addRecord(int, char[], char[]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
    friend std::ostream& operator<<(std::ostream&, const llist&);
};

#endif
