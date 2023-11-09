#include "token.h"

class Scanner
{
private:
    string input; // Armazena o texto de entrada
    int pos;      // Posição atual
    int lineID;   // Linha atual

public:
    // Construtor
    Scanner(string);

    // Método que retorna o próximo token da entrada
    Token *nextToken();
    Token *checkNextToken(int pseudoPos = -1);
    int getPos();

    // Método para manipular erros
    void lexicalError();
};
