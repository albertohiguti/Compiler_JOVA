#include "parser.h"

string *attributes_translator, *name_translator;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Erro, tente usar algo como: ./xpp_compiler inputFilePath.xpp\n";
        return 1;
    }

    bool debugMode = argv[2] != NULL && std::strcmp(argv[2], "-d") == 0;

    Token *token;
    Parser *parser = new Parser(argv[1], debugMode);

    parser->run();

    return 0;
}
