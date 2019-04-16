#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
#include <map>
#include "Reserved.h"
using namespace std;



static States State;
static map<string,Keywords> Llave;
static map<string,Keywords>::iterator ITE;

struct token
{
    TokenTypes TokenType;
    string TokenString;

    union
    {
        Keywords keyID;
        int intvariable;
        char charvariable;
        Operators operatorID;
    };
};

ErrorCode GetToken(string file, int& i, FILE out, token& tokeru);
void Write(string file, token& tokeru, FILE& out);
ErrorCode GetComment(string file, int& i, FILE&out, token& tokeru);
void Map();
string Read(string filename);

#endif // TOKEN_H
