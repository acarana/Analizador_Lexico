#ifndef RESERVED_H
#define RESERVED_H
#include <iostream>
#include <string>
using namespace std;

enum Keywords {SI, SINO, instMientras, instEscribe, INICIO, FINAL, finMientras, finSi};

enum ErrorCode { NO_ERROR, UNKNOWN_CHAR, ILLEGAL_ESCAPE_CHAR, END_OF_COMMENT_NOT_FOUND};

enum States { START,END, COMMENT_FOUND1, COMMENT_FOUND2, IDENTIFIER_FOUND, CHAR_FOUND1,
              CHAR_FOUND2, STRING_FOUND, STRING_FOUND1, STRING_FOUND2, STRING_ESCAPE,
              INTEGER_FOUND, OPERATOR_FOUND};

enum TokenTypes { UNDEFINED, LINE_COMMENT, START_COMMENT, END_COMMENT, IDENTIFICADOR,
                  KEYWORD, CHAR, ENTERO, STRING, opBinario, ASIGNACION, COMMA,
                  PARENTHESIS_IZQUIERDO, PARENTHESIS_DERECHO};

enum Operators { NEGATIVE, INCREMENT, DECREASE, NOT,
                ASIGNMENT_OPERATOR, ADD, MULTIPLY, SUBSTRACT, DIVIDE,
                EQUAL, NOT_EQUAL, LESSER_THAN, GREATER_THAN,
                LESS_OR_EQUAL, GREATER_OR_EQUAL,
                COUT_OPERATOR, CIN_OPERATOR};


const string TokenTypesSTR[] = {"UNDEFINED", "LINE_COMMENT", "START_COMMENT", "END_COMMENT",
                                "IDENTIFICADOR", "KEYWORD", "CHAR", "ENTERO","STRING","opBinario",
                                "ASIGNACION", "COMMA","PARENTHESIS_IZQUIERDO",
                                "PARENTHESIS_DERECHO"};
const string ErrorCodeSTR[] = {"NO_ERROR", "UNKNOWN_CHAR", "ILLEGAL_ESCAPE_CHAR", "END_OF_COMMENT_NOT_FOUND"};
const string KeywordSTR[] = { "SI", "SINO", "instMientras", "instEscribe", "INICIO", "FINAL", "finMientras", "finSi"};
const string OperatorSTR[] = {"NEGATIVE", "INCREMENT", "DECREASE", "NOT",
                              "ASIGNMENT_OPERATOR", "ADD", "MULTIPLY", "SUBSTRACT", "DIVIDE",
                              "EQUAL", "NOT_EQUAL", "LESSER_THAN", "GREATER_THAN",
                              "LESS_OR_EQUAL", "GREATER_OR_EQUAL",
                              "COUT_OPERATOR", "CIN_OPERATOR"};



#endif // RESERVED_H
