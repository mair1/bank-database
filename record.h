/**************************************************
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
//  FILE:        record.h
//
//  DESCRIPTION:
//    ***struct definition of record***
//
*************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record * next;
};

#endif
