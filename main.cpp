#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Reserved.h"
using namespace std;



int main()
    {

          string FileContent;
          string fileName;
          int i =0;

          token tokeru;

          cout << " Enter your filename" << endl;
          cin >> fileName;

         FileContent = Read(fileName);
            FILE * pFile ;
            pFile = fopen ("tokens.txt","w");


            Map();


            while(i <= FileContent.length()-1)
            {


                    GetToken(FileContent, i, *pFile, tokeru);

                        if(i == FileContent.length()-1)
                            return 0;


            }

            fclose (pFile);


    }
