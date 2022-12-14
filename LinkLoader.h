/******************************************************************** 
***  NAME        : Cole Masterson                                 *** 
***  CLASS       : CSC 354                                        *** 
***  ASSIGNMENT  : 4                                              *** 
***  DUE DATE    : 11/30/2022                                      *** 
***  INSTRUCTOR  : GAMRADT                                        *** 
*********************************************************************
***  DESCRIPTION : main.cpp is where the main program is executed.
The main function takes in 2 arguments, which are files that are used
in popuating the symbol table and evaluating expressions based on the
symbol table values.
********************************************************************/
#ifndef LINKLOADER_H
#define LINKLOADER_H

#include "Record.h"

using namespace std;


class LinkLoader
{
    public:
        LinkLoader();
        LinkLoader(string);
        LinkLoader(vector<string>);

        void setRecordType();
        void load();
        void modify();

        string getCurrRow(string, string);
        void storeMemory(string);

        void displayRow(AddressRow);
        void displayMemory();
        void writeMemory();

        AddressRow initializeAddRow(AddressRow);

        void readFiles(string);
        void parseRecord(string);

        void trimMemory();
        void calcExecute();

        int toDec(string);
        string toHex(int);

        vector<AddressRow> mem;     // holds the address rows for each consecutive memory address after starting address
        vector<string> bytes;
        Record recs;
        string execAddr;
        string execPath;
        string outPath = "memory.txt";

    private:
};

#endif