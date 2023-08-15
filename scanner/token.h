#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    IF,//2
    ELSE,//3
    THEN,//4
    OP,//5
    EQ,//6
    NE,//7
    GT,//8
    GE,//9
    LT,//10
    LE,//11
    ASSIGN,//12
    ADD,
    SUB,
    MUL,
    DIV,
    MODULE,
    INTEGER,
    SEP,
    LPARENTESES,
    RPARENTESES,
    LSQUARE,
    RSQUARE,
    LBRACE,
    RBRACE,
    COMMA,
    DOT,
    SEMICOLON,
    LQUOTE,
    RQUOTE,
    LINECOMMENT,
    BLOCKCOMMENT,
    END_OF_FILE
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};