#include <iostream>
#include <ctype.h> //Funções de caracteres
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

enum Names
{
    ID,
    INTEGER_LITERAL,
    OP,
    SEP,
    STRING,
    COMMENT,
    END_OF_FILE
};

enum Attributes
{
    // op
    UNDEF,  // 0
    EQ,     // 1
    NE,     // 2
    GT,     // 3
    GE,     // 4
    LT,     // 5
    LE,     // 6
    ASSIGN, // 7
    ADD,    // 8
    SUB,    // 9
    MUL,    // 10
    DIV,    // 11
    MODULE, // 12

    // sep
    LPARENTESES, // 13
    RPARENTESES, // 14
    LSQUARE,     // 15
    RSQUARE,     // 16
    LBRACE,      // 17
    RBRACE,      // 18
    DOT,         // 19
    SEMICOLON,   // 20
    COMMA,       // 21

    // string
    QUOTE,  // 21
    LQUOTE, // 22
    RQUOTE, // 23

    // comment
    LINECOMMENT,   // 24
    LBLOCKCOMMENT, // 25
    RBLOCKCOMMENT, // 26

    // reserved words
    CLASS,      // 27
    EXTENDS,    // 28
    INT,        // 29
    STRING_T,   // 30
    BREAK,      // 31
    PRINT,      // 32
    READ,       // 33
    RETURN,     // 34
    SUPER,      // 35
    IF,         // 36
    ELSE,       // 37
    FOR,        // 38
    NEW,        // 39
    CONSTRUCTOR // 40
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

    Token(int name, string lexeme)
    {
        this->name = name;
        this->lexeme = lexeme;
        attribute = UNDEF;
    }
};
