#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Reserved.h"
using namespace std;


string ReadFile(string filename)
{
   string content;
   ifstream in(filename);

   if(in.is_open())
     {
         string line;

         while(getline(in, line))
              {
                content +=  line+ '\n' ;
              }
         return content;
      }
    else
    cerr << "File was not opened" << endl;
}

int main()
    {

          string FileContent;
          string fileName;
          int i =0;

          token tokeru;

          cout << " Enter your filename" << endl;
          cin >> fileName;

         FileContent = ReadFile(fileName);
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
