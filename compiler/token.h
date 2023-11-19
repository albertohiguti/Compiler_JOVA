#include <iostream>
#include <ctype.h> //Funções de caracteres
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

enum Names
{
    ID,              // 0
    INTEGER_LITERAL, // 1
    OP,              // 2
    SEP,             // 3
    STRING,          // 4
    COMMENT,         // 5
    END_OF_FILE,     // 6
    CLASS,           // 7
    EXTENDS,         // 8
    INT,             // 9
    STRING_T,        // 10
    BREAK,           // 11
    PRINT,           // 12
    READ,            // 13
    RETURN,          // 14
    SUPER,           // 15
    IF,              // 16
    ELSE,            // 17
    FOR,             // 18
    NEW,             // 19
    CONSTRUCTOR      // 20
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
