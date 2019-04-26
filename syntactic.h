#ifndef SYNTACTIC_H
#define SYNTACTIC_H
#include <iostream>
#include <string>
#include <vector>
#include "reserved.h"
using namespace std;

struct Grammar
{
    string tokenString;
    string tokenType;
    string ID;
};

extern vector<Grammar> tok;

void Analyze();
void ReadToken(string& file);
void Instruccion(Grammar temp, vector<Grammar>::iterator& it);
bool IsInstruccion(Grammar temp);
bool mientras(Grammar temp, vector<Grammar>::iterator& it);
bool Expresion(Grammar temp, vector<Grammar>::iterator& it,string& id);
bool Parentesis(Grammar temp, vector<Grammar>::iterator& it,string& id);
bool Asignacion(Grammar temp, vector<Grammar>::iterator it);
bool escribe(Grammar temp, vector<Grammar>::iterator& it);
bool si(Grammar temp, vector<Grammar>::iterator& it);

#endif // SYNTACTIC_H
