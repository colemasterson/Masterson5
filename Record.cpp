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
#include "Record.h"

using namespace std;



Record::Record()
{
    //string path = getPath();
    //pathName = setPathName(path);
    //readFile(path);
}
/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
Record::Record(string path)
{

}
/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
string Record::getPath()
{
    string s;
    cout << "Please enter file name:";
    cin >> s;
    cin.ignore();
    return s;
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
void Record::readFile(string path)
{
    ifstream inFile;
    string tLine;
    ObjProgram prog;
    int textCount = 0;
    int csectCount = 0;
    inFile.open(path);

    if(!inFile)
    {
        cout << "ERROR: " + path + " was not found. Please verify object file location and try again." << endl;
        exit(102);
    }

    while(getline(inFile, tLine))
    {   
        prog = parseRecord(tLine, prog);
    }
    inFile.close();

    progs.push_back(prog);

    return;
}


/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
string Record::addHex(string currL, string incr)
{
    stringstream ss1, ss2, ss3;
    int cDec, iDec, sDec;
    string result;

    ss1 << hex << currL;
    ss1 >> cDec;

    //cout << cDec << endl;
    ss1.clear();

    ss2 << hex << incr;
    ss2 >> iDec;

    //cout << iDec << endl;
    ss2.clear();

    sDec = cDec + iDec;

    ss3 << hex << sDec;
    result = ss3.str();

    ss3.clear();
    //cout << "Result: " << sDec << endl;
    return result;
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
ObjProgram Record::parseRecord(string line, ObjProgram p)
{
    if(line[0] == 'H')
    {
        ExtSymbol tSym;

        tSym.csect = line.substr(1,6);
        tSym.csaddr = line.substr(7,6);
        tSym.length = line.substr(13,6);

        if(estab.size() > 0)
        {
            tSym.csaddr = addHex(progAddr, tSym.csaddr);
        }

        insert(tSym);
        p.csect = estab.back();
        //cout  <<  tSym.csect << setw(15) << tSym.csaddr  << setw(15) << tSym.length << endl;
    }
    else if(line[0] == 'D')
    {
        int idx = 1;
        while(idx < line.size())
        {
            ExtSymbol tSym;
            tSym.symbol = line.substr(idx, 6);
            tSym.addr= line.substr(idx + 6, 6);
            idx += 12;

            insert(tSym);
            //cout << tSym.symbol << setw(15) << tSym.addr << endl;
        }
        
    }
    else if(line[0] == 'R')
    {
/*          int idx = 1;
        while (idx < line.size())
        {
            ExtSymbol tSym;
            tSym.symbol = line.substr(idx, 6);
            insert(tSym);
        }
        idx += 6; */    
    }
    else if(line[0] == 'T')
    {
        TextRecord t;
        t.start = line.substr(1,6);
        t.length = line.substr(7, 2);

        t.objcode = line.substr(9, line.size() - 9);
        p.tr.push_back(t);
    }
    else if(line[0] == 'M')
    {
        ModRecord m;

        m.addr = line.substr(1, 6);
        m.modbyes = line.substr(7,2);
        m.name = line.substr(10, (line.size() - 10));
        p.mr.push_back(m);
    }
    else if(line[0] == 'E')
    {
        startAdr = line.substr(1,6);
    }    

    return p;
}


/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
string Record::subHex(string currL, string decr)
{
    stringstream ss1, ss2, ss3;
    int cDec, iDec, sDec;
    string result;

    ss1 << hex << currL;
    ss1 >> cDec;

    //cout << cDec << endl;
    ss1.clear();

    ss2 << hex << decr;
    ss2 >> iDec;

    //cout << iDec << endl;
    ss2.clear();

    sDec = cDec - iDec;

    ss3 << hex << sDec;
    result = ss3.str();

    ss3.clear();
    //cout << "Result: " << sDec << endl;
    return result;
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
void Record::insert(ExtSymbol t)
{
    // if a csect, look for the last csect in the vector.
        // if not found, use the start address for this.csect
        // if found, use this.csect = addHex(that.csect, that.cslth)

    if(!t.csect.empty())
    {
        int lastIdx = -1;
        for(int i = 0; i < estab.size(); i++)
        {
            if(!estab[i].csect.empty())
                lastIdx = i;
        }

        if(lastIdx == -1)
            t.csaddr = loadAdr;
        else
            t.csaddr = addHex(estab[lastIdx].csaddr, estab[lastIdx].length);
        

    }
    
    // if a symbol, look for the last csect in the vector. 
        //if found, use this.ldaddr = addHex(that.csaddr, this.addr)
        //if not found, user this.ldaddr = addHex(loadAdr, this.addr)
    if(!t.symbol.empty())
    {
        for(int i = 0; i < estab.size(); i++)
        {
            int lastIdx = -1;
            for(int i = 0; i < estab.size(); i++)
            {
                if(!estab[i].csect.empty())
                    lastIdx = i;
            } 

            if(lastIdx == -1)
                t.ldaddr = addHex(loadAdr, t.addr);
            else
                t.ldaddr = addHex(estab[lastIdx].csaddr, t.addr);  
        }
    }

    estab.push_back(t);
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
void Record::printEstab()
{
    cout << "CSECT" << setw(15) << "SYMBOL" << setw(15) << "ADDRESS" << setw(15) << "CSADDR" << setw(15) << "LDADDR" << setw(15) << "LENGTH" << endl;
    for(ExtSymbol ext : estab)
    {
         cout << ext.csect << setw(15) << ext.symbol << setw(15) << ext.addr << setw(15) << ext.csaddr << setw(15) << ext.ldaddr << setw(15) << ext.length << endl;
    }

    return;
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
void Record::printTR()
{
    cout << "Text Records" << endl;
    for(int i = 0; i < progs.size(); i++)
    {   
        for(TextRecord t : progs[i].tr)
            cout << t.objcode << endl;
    }
    return;
}

/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
void Record::printMR()
{
    cout << "Mod Records" << endl;
    cout << "Address" << setw(15) << "Mod HBytes" << setw(15) << "Name" << endl;

    for(int i = 0; i < progs.size(); i++)
    {   
        for(ModRecord m : progs[i].mr)
            cout << m.addr << setw(15) << m.modbyes << setw(15) << m.name << endl;
    }

    return;
}