#include "symboltable.h"

class Scanner
{
private:
    string input; // Armazena o texto de entrada
    int pos;      // Posição atual
    int lineID;   // Linha atual
    SymbolTable *st;
    bool debugMode;

public:
    // Construtor
    Scanner(string, bool);

    // Método que retorna o próximo token da entrada
    Token *nextToken();
    Token *checkNextToken(int pseudoPos = -1);
    int getPos();
    void populateSymbolTable();
    // Método para manipular erros
    void lexicalError();
};
