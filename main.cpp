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
#include "LinkLoader.h"

using namespace std;


void parseRecord(string);

int main()
{
/*     vector<string> records;
    records.push_back("HPROGRA00000000003b");
    records.push_back("HPROGR 000003000012");
    records.push_back("HPROG  00001A000034");
    records.push_back("HFUNC  0000000000FF");
    records.push_back("HFOOBAR00000000001C");
    records.push_back("DONE   00000ARETADR00001E");
    records.push_back("DBARS  000009LETS  000023");
    records.push_back("DALMOST000069FINISH000FF7");
    records.push_back("DICANT 000024BELIVE000291");


    cout << "name" << setw(15) << "start" << setw(15) << "length" << endl;

    for(string r : records)
        parseRecord(r); */

    LinkLoader l;

    l.recs.readFile("sic1.obj");
    //l.recs.printEstab();
    //l.recs.printMR();
    //l.recs.printTR();
    l.load();
    l.trimMemory();
    l.displayMemory();

    return 0;
}

void parseRecord(string line)
{
    string name, start, length;
    if(line[0] == 'H')
    {
        ExtSymbol tSym;

        tSym.csect = line.substr(1,6);
        tSym.csaddr = line.substr(7,6);
        tSym.length = line.substr(13,6);

        cout  <<  tSym.csect << setw(15) << tSym.csaddr  << setw(15) << tSym.length << endl;
    }
    if(line[0] == 'D')
    {
        int idx = 1;
        while(idx < line.size())
        {
            ExtSymbol tSym;
            tSym.symbol = line.substr(idx, 6);
            tSym.addr= line.substr(idx + 6, 6);
            idx += 12;

            cout << tSym.symbol << setw(15) << tSym.addr << endl;
        }
        
    }
    if(line[0] == 'E')
    {
        
    }

    return;
}



/* int main(int argc, char* argv[])
{

    if(argc == 1)
    {
        //no argument given
        LinkLoader ll;

        return 0;
    }
    else if(argc > 1)
    {
        vector<string> paths;
        for(int i = 0; i < argc; i++)
            paths.push_back(argv[i]);
        
        LinkLoader(paths);

        return 0;
    }
    else
        cout << "Correct Usage: ./output OR ./output programFile" << endl;

    return 1;
} */