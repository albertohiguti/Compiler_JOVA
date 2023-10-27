#include "scanner.h"

// Construtor
Scanner::Scanner(string Input)
{
    this->input = Input;

    pos = 0;
    lineID = 1;

    ifstream inputFile(Input);

    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            this->input += line + '\n';
        }
        inputFile.close();
    }
    else
        cout << "Unable to open file";
}

// Método que retorna o próximo token da entrada
Token *Scanner::nextToken()
{
    Token *tok;
    int state = 0;

    while (true)
    {
        switch (state)
        {
        case 0: // case 9: case12: case22:
            if (input[pos] == '\0')
            {
                tok = new Token(END_OF_FILE);
                return tok;
            }
            if (input[pos] == '<')
                state = 1;
            else if (input[pos] == '>')
                state = 4;
            else if (input[pos] == '=')
                state = 7;
            else if (input[pos] == '+')
                state = 10;
            else if (input[pos] == '-')
                state = 11;
            else if (input[pos] == '*')
                state = 12;
            else if (input[pos] == '/')
                state = 15;
            else if (input[pos] == '%')
                state = 19;
            else if (input[pos] == '!')
                state = 20;
            else if (input[pos] == '(')
                state = 22;
            else if (input[pos] == ')')
                state = 23;
            else if (input[pos] == '[')
                state = 24;
            else if (input[pos] == ']')
                state = 25;
            else if (input[pos] == '{')
                state = 26;
            else if (input[pos] == '}')
                state = 27;
            else if (input[pos] == ';')
                state = 28;
            else if (input[pos] == '"')
                state = ;
            else if (input[pos] == '/')
                state = ;
            else if (isalpha(input[pos]))
                state = ;
            else if (isdigit(input[pos]))
                state = ;
            else if (isspace(input[pos]))
                state = ;
            // cout << state << " ";
            pos++;

            break;
        case 1:
            if (input[pos] == '=')
                state = 2;
            else
                state = 3;
            pos++;
            break;

        case 2:
            tok = new Token(RELOP, LE);
            return tok;

        case 3:
            tok = new Token(RELOP, LT);
            return tok;

        case 4:
            if (input[pos] == '=')
                state = 5;
            else
                state = 6;
            pos++;
            break;

        case 5:
            tok = new Token(RELOP, GE);
            return tok;

        case 6:
            tok = new Token(RELOP, GT);
            return tok;

        case 7:
            if (input[pos] == '=')
                state = 8;
            else
                state = 9;
            pos++;
            break;

        case 8:
            tok = new Token(RELOP, EQ);
            return tok;

        case 9:
            tok = new Token(RELOP, ASSIGN);
            return tok;

        case 10:
            tok = new Token(RELOP, ADD);
            return tok;

        case 11:
            tok = new Token(RELOP, SUB);
            return tok;

        case 12:
            if (input[pos] == '/')
                state = 13;
            else
                state = 14;
            pos++;
            break;

        case 13:
            tok = new Token(COMMENT, RBLOCKCOMMENT);
            return tok;

        case 14:
            tok = new Token(RELOP, MUL);
            return tok;

        case 15:
            if (input[pos] == '/')
                state = 16;
            else if (input[pos] == '*')
                state = 17;
            else
                state = 18;
            pos++;
            break;

        case 16:
            tok = new Token(COMMENT, LINECOMMENT);
            return tok;

        case 17:
            tok = new Token(COMMENT, LBLOCKCOMMENT);
            return tok;

        case 18:
            tok = new Token(COMMENT, DIV);
            return tok;

        case 19:
            tok = new Token(RELOP, MODULE);
            return tok;

        case 20:
            if (input[pos] == '=')
                state = 21;
            else
                state = 22;
            pos++;
            break;

        case 21:
            tok = new Token(RELOP, NE);
            return tok;

        case 22:
            tok = new Token(SEP, LPARENTESES);
            return tok;

        case 23:
            tok = new Token(SEP, RPARENTESES);
            return tok;

        case 24:
            tok = new Token(SEP, LSQUARE);
            return tok;

        case 25:
            tok = new Token(SEP, RSQUARE);
            return tok;

        case 26:
            tok = new Token(SEP, LBRACE);
            return tok;

        case 27:
            tok = new Token(SEP, RBRACE);
            return tok;

        case 28:
            tok = new Token(SEP, SEMICOLON);
            return tok;

        default:
            lexicalError();
        }
    }

    /*
        Token* tok;
        int state;

        state = 0;

        while (true)
        {
            switch (state)
            {
                case 0://Junção dos estados 0, 9, 12 e 22 dos diagramas
                    if (input[pos] == '\0')
                    {
                        tok = new Token(END_OF_FILE);

                        return tok;
                    }
                    if (input[pos] == '<')
                        state = 1;
                    else if (input[pos] == '=')
                        state = 5;
                    else if (input[pos] == '>')
                        state = 6;
                    else if (isalpha(input[pos]))
                        state = 10;
                    else if (isdigit(input[pos]))
                        state = 13;
                    else if (isspace(input[pos]))
                        state = 23;
                    else
                        lexicalError();

                    pos++;

                    break;

                case 1:
                    if (input[pos] == '=')
                        state = 2;
                    else if (input[pos] == '>')
                        state = 3;
                    else
                        state = 4;

                    pos++;

                    break;
                case 2:
                    tok = new Token(RELOP, LE);

                    return tok;

                case 3:
                    tok = new Token(RELOP, NE);

                    return tok;

                case 4:
                    tok = new Token(RELOP, LT);
                    pos--;
                    return tok;

                case 5:
                    tok = new Token(RELOP, EQ);

                    return tok;
                case 6:
                    if (input[pos] == '=')
                        state = 7;
                    else
                        state = 8;

                    pos++;

                    break;

                case 7:
                    tok = new Token(RELOP, GE);

                    return tok;
                case 8:
                    tok = new Token(RELOP, GT);
                    pos--;

                    return tok;
                //case 9:Juntou com o 0
                case 10:
                    if (!isalnum(input[pos]))
                        state = 11;
                    pos++;

                    break;
                case 11:
                    tok = new Token(ID);
                    pos--;

                    return tok;
                //case 12:Juntou com o 0 e com o 9
                case 13:
                    if (isdigit(input[pos]))
                        ;
                    else if (input[pos] == '.')
                        state = 14;
                    else if (input[pos] == 'E')
                        state = 16;
                    else
                        state = 20;

                    pos++;

                    break;

                case 14:
                    if (isdigit(input[pos]))
                    {
                        state = 15;
                        pos++;
                    }
                    else
                        lexicalError();

                    break;

                case 15:
                    if (isdigit(input[pos]))
                        ;
                    else if (input[pos] == 'E')
                        state = 16;
                    else
                        state = 21;

                    pos++;

                    break;

                case 16:
                    if (input[pos] == '+' || input[pos] == '-')
                        state = 17;
                    else if (isdigit(input[pos]))
                        state = 18;
                    else
                        lexicalError();

                    pos++;

                    break;

                case 17:
                    if (isdigit(input[pos]))
                    {
                        state = 18;
                        pos++;
                    }
                    else
                        lexicalError();

                    break;

                case 18:
                    if (!isdigit(input[pos]))
                        state = 19;

                    pos++;

                    break;

                case 19:
                    tok = new Token(NUMBER, DOUBLE_LITERAL);
                    pos--;
                    return tok;

                case 20:
                    tok = new Token(NUMBER, INTEGER_LITERAL);
                    pos--;
                    return tok;

                case 21:
                    tok = new Token(NUMBER, FLOAT_LITERAL);
                    pos--;
                    return tok;

                //case 22: Juntou com o 0, com o 9 e com o 12
                case 23:
                    if (!isspace(input[pos]))
                        state = 24;

                    pos++;

                    break;

                case 24:
                    pos--;
                    state = 0;

                    break;

                default:
                    lexicalError();
            }
        }
    */
} // Fim nextToken

void Scanner::lexicalError()
{
    cout << "Token mal formado\n";

    exit(EXIT_FAILURE);
}
