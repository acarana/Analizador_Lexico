#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include "Reserved.h"
#include "token.h"
using namespace std;


ErrorCode GetToken(string file, int& i, FILE out, token& tokeru)
{
    FILE * pFile;
    ErrorCode Code = NO_ERROR;
    State = START;
    tokeru.TokenType = UNDEFINED;
    tokeru.TokenString = "";
    tokeru.intvariable = 0;

    while(file[i] == ' ')
    {
        i++;
    }

    while( (State != END) && (Code == NO_ERROR) )
    {
        char ch = file[i];
        tokeru.TokenString += ch;

        switch(State)
        {
////////////////////////////////////////////////////////////////////////////
          case START:
            if(isalpha(ch))
            {
                State = IDENTIFIER_FOUND;
                if(isupper(ch))
                    tokeru.TokenType = ERROR;
                break;
            }

            if(isdigit(ch))
            {
                State = INTEGER_FOUND;
                break;
            }

            switch(ch)
            {


            case ' ':
               tokeru.TokenString.pop_back();
                break;

              case '\n':
              tokeru.TokenString.pop_back();
                break;

              case ';':
                State = END;
                tokeru.TokenType = DELIMITADOR;
              break;

              case '(':
                State = END;
                tokeru.TokenType = PARENTHESIS_IZQUIERDO;
                break;

              case ')':
                State = END;
                tokeru.TokenType = PARENTHESIS_DERECHO;
                break;


              case '=':
              case '!':
              case '+':
              case '-':
              case '*':
              case '/':
              case '<':
              case '>':
                State = OPERATOR_FOUND;
                break;
            }
            break;

//---------------------------------------------------------------------------

        case IDENTIFIER_FOUND:
            if (isupper(ch))
            {
                State = IDENTIFIER_FOUND;
                tokeru.TokenType = ERROR;
            }
            else if(isalnum(ch))
                {
                    State = IDENTIFIER_FOUND;
                }
            else
            {
                State = END;
                tokeru.TokenString.pop_back();
                ITE = Llave.find(tokeru.TokenString);

                if(ITE == Llave.end())
                  {
                    if(tokeru.TokenType != ERROR)
                       tokeru.TokenType = IDENTIFICADOR;
                  }
                else
                {
                    tokeru.TokenType = RESERVADA;
                    tokeru.keyID = (Keywords)ITE->second;
                }
            }
            break;

////////////////////////////////////////////////////////////////////////////////

        case INTEGER_FOUND:
            if(isdigit(ch))
                State = INTEGER_FOUND;
            else
            {
                State = END;
                tokeru.TokenString.pop_back();

                if(isdigit(tokeru.TokenString[0]) && isdigit(tokeru.TokenString[1]))
                   tokeru.TokenType = ENTERO;

                else
                   tokeru.TokenType = ERROR;
            }
            break;

////////////////////////////////////////////////////////////////////////////////////

        case COMMENT_FOUND1:
            if(ch == '\\')
            {
                tokeru.TokenType = LINE_COMMENT;
                State = END;
                break;
            }

            else
            {
                if(ch == '*')
                {
                    tokeru.TokenType = START_COMMENT;
                    State = END;
                    break;
                }
                else
                    return UNKNOWN_CHAR;
            }


//---------------------------------------------------------------------------



//---------------------------------------------------------------------------



///////////////////////////////////////////////////////////////////////////
        case OPERATOR_FOUND:
            switch(tokeru.TokenString[0])
            {

              case '+':
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = SUMAR;

                break;

              case '-':
                     State = END;
                     tokeru.TokenType = opBinario;
                     tokeru.operatorID = RESTAR;
                break;

              case '*':

                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MULTIPLICAR;

                break;

              case '/':

                   if(ch == '*')
                       {

                                    State = COMMENT_FOUND2;
                                    tokeru.TokenType = START_COMMENT;
                                    GetComment(file, i, out, tokeru);
                        }
                     else
                             {
                                 if(ch == '/')
                                   {


                                       State = COMMENT_FOUND1;
                                       tokeru.TokenType = LINE_COMMENT;
                                       GetComment(file, i, out, tokeru);

                                     }
                                 else
                                   {

                                       State = END;
                                      tokeru.TokenType = opBinario;
                                      tokeru.operatorID = DIVIDIR;
                                   }
                              }

                break;


              case '=':
                if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = IGUAL;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = ASIGNACION;
                    tokeru.operatorID = OPERADOR_ASIGNACION;
                }
                break;

              case '<':
                    if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MENOR_O_IGUAL;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MENOR;

                }
                break;

              case '>':
                    if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MAYOR_O_IGUAL;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MAYOR;
                }
                break;
            }
            break;
        }
///////////////////////////////////////////////////////////////////////////////////
        i++;


   }


      string str;
     switch(tokeru.TokenType)
                {
                    case opBinario :

                            str =  tokeru.TokenString + "\t"+ TokenTypesSTR[tokeru.TokenType] + "\t" + OperatorSTR[tokeru.operatorID]  + "\n";
                            break;
                     case RESERVADA :

                            str = tokeru.TokenString + " \t"+TokenTypesSTR[tokeru.TokenType] + "\t" + KeywordSTR[tokeru.keyID]+" \n" ;
                            break;
                     case ASIGNACION :
                         str =  tokeru.TokenString + " \t"+ TokenTypesSTR[tokeru.TokenType] + "\t" + OperatorSTR[tokeru.operatorID]  + "\n";
                         break ;
                     case START_COMMENT:
                         break;
                     case LINE_COMMENT:
                         break;
                     case END_COMMENT:
                         break;

                     default :


                            str =  tokeru.TokenString+ "\t" + TokenTypesSTR[tokeru.TokenType] + " \n" ;
                            break;
                }
   pFile = fopen ("tokens.txt","a");

   fputs (str.c_str(),pFile);
   fclose (pFile);

    return NO_ERROR;
}


ErrorCode GetComment(string file, int& i, FILE&out, token& tokeru)
{
    FILE * pFile ;
    pFile = fopen ("myfile.txt","a");
   string str;
   switch(tokeru.TokenType)
   {
     case START_COMMENT : str =  tokeru.TokenString + "              \t "+ TokenTypesSTR[tokeru.TokenType]  +"\n";
     case LINE_COMMENT  : str =  tokeru.TokenString + "              \t "+ TokenTypesSTR[tokeru.TokenType]  +"\n";

   }
    fputs (str.c_str(), pFile);
    /////////////////////////////////////////////
    switch(State)
    {
    case  COMMENT_FOUND1 :
        while (file[i]!='\n')
            i++;
        break;
    case  COMMENT_FOUND2 :
        do{
            while (file[i++]!='*');
        }
        while(file[i]!='/');
        tokeru.TokenType=END_COMMENT;
        str =  "*/              \t "+ TokenTypesSTR[tokeru.TokenType]  +"\n";
        fputs (str.c_str(), pFile);

        break;
    }

    fclose (pFile);
    State = END;

    return NO_ERROR;
}

string Read(string filename)
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

void Map()
{
    Llave["Si"] = SI;
    Llave["sino"] = SINO;
    Llave["Mientras"] = instMientras;
    Llave["Escribe"] = instEscribe;
    Llave["inicio"] = INICIO;
    Llave["final"] = FINAL;
    Llave["finsi"] = finSi;
    Llave["finmientras"] = finMientras;
}
