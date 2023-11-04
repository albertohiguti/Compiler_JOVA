#include "scanner.h"
#include "parser.h"

string *attributes_translator, *name_translator;

void print(Token *);
void createEnumTranslator();
void freeVetor();

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        cout << "Error, try using: ./compiler inputFilePath.mj\n";
        return 1;
    }

    Scanner *scanner = new Scanner(argv[1]);

    createEnumTranslator();

    Token *token;

    do
    {
        token = scanner->nextToken();
        // cout << t->name << " ";
        std::cout << "Name " << name_translator[token->name] << " Attribute " << attributes_translator[token->attribute] << " Lexeme " << token->lexeme << "\n";

    } while (token->name != END_OF_FILE);

    delete scanner;

    return 0;
}

void createEnumTranslator()
{
    attributes_translator = new string[27]{
        "UNDEF",         // 0
        "EQ",            // 1
        "NE",            // 2
        "GT",            // 3
        "GE",            // 4
        "LT",            // 5
        "LE",            // 6
        "ASSIGN",        // 7
        "ADD",           // 8
        "SUB",           // 9
        "MUL",           // 10
        "DIV",           // 11
        "MODULE",        // 12
        "LPARENTESES",   // 13
        "RPARENTESES",   // 14
        "LSQUARE",       // 15
        "RSQUARE",       // 16
        "LBRACE",        // 17
        "RBRACE",        // 18
        "DOT",           // 19
        "SEMICOLON",     // 20
        "QUOTE",         // 21
        "LQUOTE",        // 22
        "RQUOTE",        // 23
        "LINECOMMENT",   // 24
        "LBLOCKCOMMENT", // 25
        "RBLOCKCOMMENT"  // 26
    };

    name_translator = new string[7]{
        "ID",
        "INTEGER_LITERAL",
        "OP",
        "SEP",
        "STRING",
        "COMMENT",
        "END_OF_FILE"};
}

void print(Token *token)
{
    cout << attributes_translator[token->name];

    if (token->attribute != UNDEF)
        cout << "(" << attributes_translator[token->attribute] << ")";

    cout << " ";
}
