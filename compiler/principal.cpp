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

    // createEnumTranslator();

    Token *token;

    Parser *parser = new Parser(argv[1]);

    parser->run();

    // do
    // {
    //     token = scanner->nextToken();
    //     // cout << t->name << " ";
    //     std::cout << "Name " << name_translator[token->name] << " Attribute " << attributes_translator[token->attribute] << " Lexeme " << token->lexeme << "\n";

    // } while (token->name != END_OF_FILE);

    return 0;
}

void print(Token *token)
{
    cout << attributes_translator[token->name];

    if (token->attribute != UNDEF)
        cout << "(" << attributes_translator[token->attribute] << ")";

    cout << " ";
}
