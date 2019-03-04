#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include "Reserved.h"
#include "Token.h"
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
                break;
            }

            if(isdigit(ch))
            {
                State = INTEGER_FOUND;
                break;
            }

            switch(ch)
            {

              case '\\':
                State = COMMENT_FOUND1;
                break;

              case '\'':

                tokeru.TokenString.pop_back();
                State = CHAR_FOUND1;
                break;

              case '\"':
                tokeru.TokenString.pop_back();
                State = STRING_FOUND1;
                break;

              case ',':
                State = END;
                tokeru.TokenType = COMMA;
                break;

            case ' ':
               tokeru.TokenString.pop_back();
                break;

              case '\n':
              tokeru.TokenString.pop_back();
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
            if(isalnum(ch))
                State = IDENTIFIER_FOUND;
            else
            {
                State = END;
                tokeru.TokenString.pop_back();
                ITE = KeyMap.find(tokeru.TokenString);

                if(ITE == KeyMap.end())
                    tokeru.TokenType = IDENTIFICADOR;
                else
                {
                    tokeru.TokenType = KEYWORD;
                    tokeru.keyID = (Keywords)ITE->second;
                }
            }
            if(tokeru.keyID == '(' )
                tokeru.TokenType = PARENTHESIS_IZQUIERDO;
            break;

////////////////////////////////////////////////////////////////////////////////

        case INTEGER_FOUND:
            if(isdigit(ch))
                State = INTEGER_FOUND;
            else
            {
                State = END;
                tokeru.TokenString.pop_back();

                tokeru.TokenType = ENTERO;
            }
            break;

//---------------------------------------------------------------------------

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

        case CHAR_FOUND1:
            if(ch == '\'')
            {
                State = END;
                tokeru.TokenString.pop_back();

                tokeru.charvariable = '\0';
                tokeru.TokenType = CHAR;
            }
            else
            {
                if(isprint(ch))
                    State = CHAR_FOUND2;
                else
                    return UNKNOWN_CHAR;
            };
            break;

        case CHAR_FOUND2:
            if(ch == '\'')
            {
                State = END;
                tokeru.TokenString.pop_back();

                tokeru.TokenType = CHAR;
            }
            break;

//---------------------------------------------------------------------------

        case STRING_FOUND1:
            if(ch == '\"')
            {
                State = END;
                tokeru.TokenString.pop_back();
                tokeru.TokenType = STRING;
                break;
            }


            if(ch == '\\')
            {
                State = STRING_ESCAPE;
                tokeru.TokenString.pop_back();

                break;
            }



        case STRING_ESCAPE:
            if(ch == 'n')
            {
                tokeru.TokenString.pop_back();

                State = STRING_FOUND1;
                tokeru.TokenString += '\n';
            }
            else
                return ILLEGAL_ESCAPE_CHAR;
            break;

///////////////////////////////////////////////////////////////////////////
        case OPERATOR_FOUND:
            switch(tokeru.TokenString[0])
            {
              case '!':
                if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = NOT_EQUAL;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = NOT;
                }
                break;

              case '+':
                if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = INCREMENT;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = ADD;
                }
                break;

              case '-':
                if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = DECREASE;
                }
                else
                {


                     if(isdigit(ch))
                     {

                                State = END;
                                tokeru.TokenString.pop_back();
                                tokeru.TokenType = opBinario;
                                tokeru.operatorID = NEGATIVE;
                                i--;

                    }
                    else
                    {
                        State = END;
                        tokeru.TokenType = opBinario;
                        tokeru.operatorID = SUBSTRACT;
                    }
                }
                break;

              case '*':

                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = MULTIPLY;

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
                                      tokeru.operatorID = DIVIDE;
                                   }
                              }

                break;


              case '=':
                if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = EQUAL;
                }
                else
                {
                    State = END;
                    tokeru.TokenType = ASIGNACION;
                    tokeru.operatorID = ASIGNMENT_OPERATOR;
                }
                break;

              case '<':
                    if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = LESS_OR_EQUAL;
                }
                else
                {
                    if(ch == '<')
                    {
                        State = END;
                        tokeru.TokenType = opBinario;
                        tokeru.operatorID = COUT_OPERATOR;
                    }
                    else
                    {
                        State = END;
                        tokeru.TokenType = opBinario;
                        tokeru.operatorID = LESSER_THAN;
                    }
                }
                break;

              case '>':
                    if(ch == '=')
                {
                    State = END;
                    tokeru.TokenType = opBinario;
                    tokeru.operatorID = GREATER_OR_EQUAL;
                }
                else
                {
                    if(ch == '>')
                    {
                        State = END;
                        tokeru.TokenType = opBinario;
                        tokeru.operatorID = CIN_OPERATOR;
                    }
                    else
                    {
                        State = END;
                        tokeru.TokenType = opBinario;
                        tokeru.operatorID = GREATER_THAN;
                    }
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

                            str =  tokeru.TokenString + "              \t "+ TokenTypesSTR[tokeru.TokenType] + "              \t " + OperatorSTR[tokeru.operatorID]  + "\n";
                            break;
                     case KEYWORD :

                            str = tokeru.TokenString + "              \t "+TokenTypesSTR[tokeru.TokenType] + "              \t " + KeywordSTR[tokeru.keyID]+" \n" ;
                            break;
                     case ASIGNACION :
                         str =  tokeru.TokenString + "              \t "+ TokenTypesSTR[tokeru.TokenType] + "              \t " + OperatorSTR[tokeru.operatorID]  + "\n";
                         break ;
                     case START_COMMENT:
                         break;
                     case LINE_COMMENT:
                         break;
                     case END_COMMENT:
                         break;

                     default :


                            str =  tokeru.TokenString+ "              \t " + TokenTypesSTR[tokeru.TokenType] + " \n" ;
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
    KeyMap["Si"] = SI;
    KeyMap["Sino"] = SINO;
    KeyMap["Mientras"] = instMientras;
    KeyMap["Escribe"] = instEscribe;
    KeyMap["Inicio"] = INICIO;
    KeyMap["Final"] = FINAL;


}
