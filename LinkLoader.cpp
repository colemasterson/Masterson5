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
/********************************************************************
*** FUNCTION : addHex(string currL, string incr)                  ***
*********************************************************************
*** DESCRIPTION : returns the sum of two hexadecimal strings      ***

*** INPUT ARGS : string, string                                   ***

*** OUTPUT ARGS : string                                          ***

*** IN/OUT ARGS : n/a                                             ***

*** RETURN : n/a                                                  ***
********************************************************************/
LinkLoader::LinkLoader()
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
LinkLoader::LinkLoader(string path)
{
    //recs.parseRecord(path);
    //recs.initialize();
    //recs.load();
    //modify();
    //display();
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
LinkLoader::LinkLoader(vector<string> paths)
{
    for(string p : paths)
        recs.readFile(p);
    
    recs.printEstab();
    load();
    modify();
    trimMemory();
    displayMemory();
    writeMemory();
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
void LinkLoader::load()
{
    for(int i = 0; i < recs.progs.size(); i++)
    {
        //for each text record
        for(TextRecord t : recs.progs[i].tr)
        {
            string text = t.objcode;
            vector<string> bytes;
            int byteCount = 0;
            //start breaking up tr into bytes
            for(int k = 0; k < text.size(); k = k + 2)
                bytes.push_back(text.substr(k, 2));

            string startAddr = recs.addHex(recs.progs[i].csect.csaddr, t.start);
            while(byteCount < bytes.size())
            {

                string currAddr = recs.addHex(startAddr, toHex(byteCount));

                string currRow = getCurrRow(currAddr, "0");
                string lastrow;

                if(mem.size() == 0)
                    lastrow = "00000";
                else
                    lastrow =  mem.back().adr;

                if(mem.size() == 0 || toDec(recs.subHex(currRow, lastrow)) > 0)
                {

                    AddressRow tempAR;
                    tempAR = initializeAddRow(tempAR);
                    tempAR.adr = currRow;

                    if(tempAR.adr.size() < 5)
                        tempAR.adr = "0" + tempAR.adr;
                    
                    int idx = toDec(recs.subHex(currAddr, currRow));
                    if(idx < 15)
                        tempAR.cells.at(idx) = bytes[byteCount];
                    
                    mem.push_back(tempAR);
                }
                else if(toDec(recs.subHex(currRow, mem.back().adr)) == 0)
                {
                    int idx = toDec(recs.subHex(currAddr, currRow));
                    if(idx < 15)
                        mem.back().cells.at(idx) = bytes[byteCount];
                }
                byteCount++;      
            }
        }
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
string LinkLoader::getCurrRow(string lastRow, string offset)
{
    string res = recs.addHex(lastRow, offset);
    res.pop_back();
    res += "0";
        
    return res;
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
void LinkLoader::calcExecute()
{
    if(!recs.progs.empty() && !recs.progs[0].tr.empty())
        execAddr = (recs.addHex(recs.progs[0].tr[0].start, "02170"));
    else
        execAddr = "02170";
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
void LinkLoader::writeMemory()
{
    ofstream outFile;

    outFile.open(outPath);

    outFile << setw(10) << "ADDRESS" << setw(10) << "0" << setw(5) << "1" << setw(5) << "2" << setw(5) << "3" << setw(5) << "4" << setw(5) << "5" << setw(5)
     << "6" << setw(5) << "7" << setw(5) << "8" << setw(5) << "9" << setw(5) << "A" << setw(5) << "B" << setw(5) << "C" << setw(5)
      << "D" << setw(5) << "E" << setw(5) << "F" << endl;

    for(AddressRow row : mem)
    {
            outFile << setw(10) << row.adr << setw(10);

            for(string cell : row.cells)
                outFile << cell << setw(5);

            outFile << endl;
    }


    calcExecute();
    outFile << "\nExecution begins at address:   <" + execAddr + ">" << endl;


    outFile.close();

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
void LinkLoader::trimMemory()
{
    //get last csect

    //calculate csaddr + length

    //grab last memory row

    //if there are values after end value, change them to blanks

    int idx;

    for(int i = 0; i < recs.estab.size(); i++)
    {
        if(recs.estab[i].csect != "")
            idx = i;
    }

    string end = recs.addHex(recs.estab[idx].csaddr, recs.estab[idx].length);

    for(int i = 0; i < mem.back().cells.size(); i++)
    {
        string currIdx = recs.addHex(mem.back().adr, toHex(i));

        if(toDec(recs.subHex(end, currIdx)) < 0)
            mem.back().cells.at(i) = "";
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
void LinkLoader::modify()
{
    for(int i = 0; i < recs.progs.size(); i++)
    {
        //for each text record
        for(ModRecord m : recs.progs[i].mr)
        {
            //calculate relative address(mr addr + csaddr)
            bool isf4 = false;
            string relAddr = recs.addHex(m.addr, recs.progs[i].csect.csaddr);

            string relRow = getCurrRow(relAddr, "0");

            int idx = toDec(recs.subHex(relAddr, relRow));
            string ogAddr, first4;

            for(int i = 0; i < mem.size(); i++)
            {
                if(stoi(mem[i].adr) - stoi(relRow) == 0)
                {
                    first4 = mem[i].cells[idx] + mem[i].cells[idx + 1];
                    
                    if(first4.at(2) == '1')
                    {isf4 = true;
                        ogAddr = mem[i].cells[idx] + mem[i].cells[idx + 1] + mem[i].cells[idx + 2] + mem[i].cells[idx + 3];
                    }
                    else
                        ogAddr = mem[i].cells[idx] + mem[i].cells[idx + 1] + mem[i].cells[idx + 2];

                    string changed = recs.addHex(ogAddr, recs.progs[i].csect.csaddr);

                    if(isf4)
                    {
                        mem[i].cells[idx] = changed.substr(0, 2);
                        mem[i].cells[idx+1] = changed.substr(2, 2);
                        mem[i].cells[idx+2] = changed.substr(4, 2);
                        mem[i].cells[idx+3] = changed.substr(6, 2); 
                    }
                    else
                    {
                        mem[i].cells[idx] = changed.substr(0, 2);
                        mem[i].cells[idx+1] = changed.substr(2, 2);
                        mem[i].cells[idx+2] = changed.substr(4, 2);  
                    }


                }
            }

        }
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
int LinkLoader::toDec(string hexIn)
{
    stringstream ss;
    int x;
    ss << hex << hexIn;
    ss >> x;
    return x;
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
string LinkLoader::toHex(int in)
{
    stringstream ss;

    ss << hex << in;
    string res = ss.str();

    return res;
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
AddressRow LinkLoader::initializeAddRow(AddressRow tempRow)
{
    for(int i = 0; i < 16; i++)
        tempRow.cells.push_back("UU");

    return tempRow;
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
void LinkLoader::displayRow(AddressRow tempRow)
{
    cout << setw(10) << tempRow.adr << setw(10);

    for(string cell : tempRow.cells)
        cout << cell << setw(5);

    cout << endl;

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
void LinkLoader::displayMemory()
{
    cout << setw(10) << "ADDRESS" << setw(10) << "0" << setw(5) << "1" << setw(5) << "2" << setw(5) << "3" << setw(5) << "4" << setw(5) << "5" << setw(5)
     << "6" << setw(5) << "7" << setw(5) << "8" << setw(5) << "9" << setw(5) << "A" << setw(5) << "B" << setw(5) << "C" << setw(5)
      << "D" << setw(5) << "E" << setw(5) << "F" << endl;
    for(AddressRow row : mem)
        displayRow(row);
    
    calcExecute();
    cout << "\nExecution begins at address:   <" + execAddr + ">" << endl;
    return;
}
