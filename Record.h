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
#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct AddressRow
{
    string adr;
    vector<string> cells;
    
};

struct TextRecord
{
    string start, length;
    string objcode;

};

struct ModRecord
{
    string addr;
    string modbyes;
    string name;
};

struct ExtSymbol
{
    string csect,
           symbol,
            addr,
            csaddr,
            ldaddr,
            length;
};

struct ObjProgram
{
    vector<TextRecord> tr;
    vector<ModRecord> mr;
    ExtSymbol csect;
    string execAddr;
};

class Record
{
    public:
        Record();
        Record(string);

        string getPath();

        void readFile(string);
        ObjProgram parseRecord(string, ObjProgram);

        void insert(ExtSymbol);

        string addHex(string, string);
        string subHex(string, string);
    
        void setRecordType(string);
        int getCodeFormat();

        void printEstab();
        void printTR();
        void printMR();

        vector<ExtSymbol> estab;
        vector<ObjProgram> progs;

        string progAddr, execAddr;


        string startAdr;
        string loadAdr = "02170";
    private:
};

#endif