#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "reserved.h"
#include "syntactic.h"
using namespace std;

vector<Grammar> tok;
static Gramatica grammar;
void Analyze()
{

    string tokenFile = "tokens.txt";
    ReadToken(tokenFile);
    Grammar temp,temp2;
    grammar = programa;

    vector<Grammar>::iterator it = tok.begin();

    while(it != tok.end())
    {
    switch(grammar)
      {
         case programa:
             grammar = secuenciaInst;
             temp = tok.front();
             temp2 = tok.back();
             if(temp.ID!="INICIO")
             {
                 cout << "Error, inicio no definido" << endl;
             }
             else if(temp2.ID!="FINAL")
             {
                 cout << "Error, final no definido" << endl;
             }
        break;

         case secuenciaInst:
              temp = *it;
              if(IsInstruccion(temp))
                  Instruccion(temp,it);





         break;


      }
    ++it;
    }

/*
    for(auto it = tok.begin();it != tok.end();++it)
    {
        cout << it->tokenString << ' ' << it->tokenType << ' ' << it->ID << endl;
    }
*/
}

bool IsInstruccion(Grammar temp)
{
    return(temp.ID == "instMientras" || temp.ID == "instEscribe"
            || temp.ID == "SI" || temp.tokenType == "ASIGNACION");
}


void Instruccion(Grammar temp, vector<Grammar>::iterator& it)
{

     if(temp.ID == "instMientras")
      {
         mientras(temp,it);
      }
     else if(temp.tokenType == "ASIGNACION")
     {
         Asignacion(temp,it);
     }
     else if(temp.ID == "instEscribe")
     {
         escribe(temp,it);
     }
     else if(temp.ID == "SI")
     {
         si(temp,it);
     }

}

bool mientras(Grammar temp, vector<Grammar>::iterator& it)
{
  vector<Grammar>::iterator eto;
  eto=it;
  temp=*eto;
  bool instFound=false;
  Parentesis(temp,it,temp.ID);

    for(eto; eto != tok.end();++eto)
    {
        temp = *eto;
        if(!instFound && (temp.tokenType == "PARENTHESIS_DERECHO"))
        {
            instFound=true;
            auto ato = eto;

            for(int i=0;i<2;i++)
            {
                ato++;
                temp=*ato;
                if(IsInstruccion(temp))
                {
                    Instruccion(temp,ato);
                    break;
                }

                else if(i==1)
                {
                    cout << "Error, se espera instruccion despues de WHILE" << endl;
                }

            }
        }

        else if(temp.ID=="finMientras")
        {
            return true;
        }
    }
    cout << "Error, finmientras no definido" << endl;

  return false;
}

bool Parentesis(Grammar temp, vector<Grammar>::iterator& it,string& id)
{
    vector<Grammar>::iterator eto;
    bool left_found=false, right_found=false,exp=false;
    ++it;
    temp = *it;

    if(temp.tokenType=="PARENTHESIS_IZQUIERDO")
    {
        left_found = true;
    }
    else {
        cout << "Error, parentesis izquiero no definido" << endl;
    }
      eto = ++it;
      exp = Expresion(temp,eto,id);
       for(eto; eto != tok.end();++eto)
        {
            temp = *eto;
            if(temp.tokenType=="PARENTHESIS_DERECHO")
               {
                  right_found = true;
                  break;
               }
        }
        if(eto==tok.end())
        {
            cout << "Error, parentesis derecho no definido" << endl;
        }

    return(left_found && right_found && exp);
}



bool Expresion(Grammar temp, vector<Grammar>::iterator& it,string& id)
{
    vector<Grammar>::iterator eto;
    bool factor=false, op=false;
    int count = 1;

    if(id=="instEscribe")
    {
        //string puede ser lo que sea//
        return true;
    }

    for(eto=it;temp.tokenType != "PARENTHESIS_DERECHO";++eto)
    {
        temp = *eto;
        op=false;
        if(count==1)
        {
            if((temp.tokenType == "ENTERO") || (temp.tokenType == "IDENTIFICADOR"))
            {
                factor=true;
            }

            else {
                cout << "Error, entero o identificador esperado despues de parentesis izquierdo" << endl;
                return false;
            }
        }

        else if(factor && (count % 2 != 0))
        {
            if((temp.tokenType == "IDENTIFICADOR") || (temp.tokenType == "ENTERO"))
            {
                factor=true;
            }
            else {
                cout << "Error, identificador o entero esperado antes de " << temp.tokenString << endl;
                return false;
            }
        }      //ultimo siempre es un digito, identificador o parentesis derecho//
        else if (factor && (count % 2 == 0) && (temp.tokenType == "opBinario" || temp.tokenType == "PARENTHESIS_DERECHO"))
        {
            op=true;
        }

        else {
            cout << "Error, operador binario esperado antes de " << temp.tokenString << endl;
            return false;
        }

        count++;
    }
    return (factor || op);
}

bool Asignacion(Grammar temp, vector<Grammar>::iterator it)
{
    vector<Grammar>::iterator eto;
    bool asignacion =false, identificador=true,delimitador=false;
    eto=it;


    eto--;
    temp=*eto;
    if(temp.tokenType == "IDENTIFICADOR")
     identificador=true;
    else
    {
        cout << "Error, identificador esperado antes de operador de asignacion" << endl;
    }

    eto+=2;
    temp=*eto;
    if((temp.tokenType == "IDENTIFICADOR") || (temp.tokenType == "ENTERO"))
        asignacion=true;
    else
    {
        cout << "Error, identificador o entero esperado despues de operador de asignacion" << endl;
    }

    if(asignacion && identificador)
    {
     eto++;
     temp=*eto;
     if(temp.tokenType == "DELIMITADOR")
         delimitador=true;
     else
     {
         cout << "Error, delimitador no encontrado" << endl;
     }
    }
    return(asignacion && identificador && delimitador);
}

bool escribe(Grammar temp, vector<Grammar>::iterator& it)
{
    return(Parentesis(temp,it,temp.ID));
}



bool si(Grammar temp, vector<Grammar>::iterator& it)
{
    vector<Grammar>::iterator eto;
    eto=it;
    temp=*eto;
    bool instFound=false;
    Parentesis(temp,it,temp.ID);

      for(eto; eto != tok.end();++eto)
      {
          temp = *eto;

          if(!instFound && (temp.tokenType == "PARENTHESIS_DERECHO"))
          {
              instFound=true;
              auto ato = eto;

              for(int i=0;i<2;i++)
              {
                  ato++;
                  temp=*ato;
                  if(IsInstruccion(temp))
                  {
                      Instruccion(temp,ato);
                      break;
                  }

                  else if(i==1)
                  {
                      cout << "Error, se espera instruccion despues de SI" << endl;
                  }

              }
          }


          else if(temp.ID=="finSi")
          {
              return true;
          }
          else if(temp.ID=="SINO")
          {
              auto ito = eto;

              for(int i=0;i<2;i++)
              {
                  ito++;
                  temp=*ito;
                  if(IsInstruccion(temp))
                  {
                      Instruccion(temp,ito);
                      break;
                  }

                  else if(i==1)
                  {
                      cout << "Error, se espera instruccion despues de SINO" << endl;
                  }

              }
          }
      }
      cout << "Error, finSi no definido" << endl;

    return false;
}


void ReadToken(string& file)
{

    ifstream in;
    string first, second, third;
    in.open(file.c_str());
    if(in.is_open())
    {
        for (int i=0;!in.eof();i++)
        {
            Grammar TKN;

            in >> first >> second;

            if(second == "opBinario" || second == "ASIGNACION" || second == "RESERVADA")
            {
                in >> third;
                TKN.tokenString = first;
                TKN.tokenType = second;
                TKN.ID = third;
            }
            else
            {
                TKN.tokenString = first;
                TKN.tokenType = second;

            }
            tok.push_back(TKN);

        }
    }
    else
        cerr << "File was not opened" << endl;

}
