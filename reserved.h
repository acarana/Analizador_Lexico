#ifndef RESERVED_H
#define RESERVED_H
#include <iostream>
#include <string>
using namespace std;

enum Keywords {SI, SINO, instMientras, instEscribe, INICIO, FINAL, finMientras, finSi};

enum States { START,END, COMMENT_FOUND1, COMMENT_FOUND2, IDENTIFIER_FOUND,
              INTEGER_FOUND, OPERATOR_FOUND};

enum TokenTypes { ERROR, UNDEFINED, LINE_COMMENT, START_COMMENT, END_COMMENT, IDENTIFICADOR,
                  RESERVADA, ENTERO, opBinario, ASIGNACION,
                  PARENTHESIS_IZQUIERDO, PARENTHESIS_DERECHO, DELIMITADOR};

enum Operators {
                OPERADOR_ASIGNACION, SUMAR, MULTIPLICAR, RESTAR, DIVIDIR,
                IGUAL, MENOR, MAYOR,
                MENOR_O_IGUAL, MAYOR_O_IGUAL};

enum ErrorCode { NO_ERROR, UNKNOWN_CHAR, ILLEGAL_ESCAPE_CHAR, END_OF_COMMENT_NOT_FOUND};


const string TokenTypesSTR[] = {"ERROR","UNDEFINED", "LINE_COMMENT", "START_COMMENT", "END_COMMENT",
                                "IDENTIFICADOR", "RESERVADA", "ENTERO","opBinario",
                                "ASIGNACION","PARENTHESIS_IZQUIERDO",
                                "PARENTHESIS_DERECHO", "DELIMITADOR"};
const string ErrorCodeSTR[] = {"NO_ERROR", "UNKNOWN_CHAR", "ILLEGAL_ESCAPE_CHAR", "END_OF_COMMENT_NOT_FOUND"};
const string KeywordSTR[] = { "SI", "SINO", "instMientras", "instEscribe", "INICIO", "FINAL", "finMientras", "finSi"};
const string OperatorSTR[] = {
                              "OPERADOR_ASIGNACION", "SUMAR", "MULTIPLICAR", "RESTAR", "DIVIDIR",
                              "IGUAL", "MENOR", "MAYOR",
                              "MENOR_O_IGUAL", "MAYOR_O_IGUAL"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum Gramatica {programa, secuenciaInst};


#endif // RESERVED_H
