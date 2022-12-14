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

 int main(int argc, char* argv[])
{

    if(argc > 1)
    {
        vector<string> files;
        for(int i = 0; i < argc; i++)
            files.push_back(argv[i]);
        
        LinkLoader LL(files);

        return 0;
    }
    else
        cout << "Correct Usage: ./output sic.obj sic2.obj sic3.obj" << endl;

    return 1;
}