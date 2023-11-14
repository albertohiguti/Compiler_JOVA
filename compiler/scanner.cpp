#include "scanner.h"

// Construtor
Scanner::Scanner(string Input)
{
    pos = 0;
    lineID = 1;
    st = new SymbolTable();
    this->populateSymbolTable();

    ifstream inputFile(Input);

    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            this->input += line + "\n";
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
    string lexeme = "";

    while (true)
    {
        // std::cout << "Analyzing: " << input[pos] << " in position " << pos << " and in State " << state << "\n";

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
                state = 29;
            else if (isalpha(input[pos]))
                state = 30;
            else if (input[pos] == '_')
                state = 30;
            else if (isdigit(input[pos]))
                state = 32;
            else if (isspace(input[pos]))
                state = 34;
            else if (input[pos] == '\n')
            {
                lineID++;
                state = 34;
            }
            else if (input[pos] == ',')
                state = 37;
            else
                lexicalError();
            // cout << state << " ";
            lexeme += input[pos];
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
            tok = new Token(OP, LE);
            return tok;

        case 3:
            tok = new Token(OP, LT);
            return tok;

        case 4:
            if (input[pos] == '=')
                state = 5;
            else
                state = 6;
            pos++;
            break;

        case 5:
            tok = new Token(OP, GE);
            return tok;

        case 6:
            tok = new Token(OP, GT);
            return tok;

        case 7:
            if (input[pos] == '=')
                state = 8;
            else
                state = 9;
            pos++;
            break;

        case 8:
            tok = new Token(OP, EQ);
            return tok;

        case 9:
            tok = new Token(OP, ASSIGN);
            return tok;

        case 10:
            tok = new Token(OP, ADD);
            return tok;

        case 11:
            tok = new Token(OP, SUB);
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
            tok = new Token(OP, MUL);
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
            if (input[pos] == '\n')
            {
                lineID++;
                state = 34;
            }
            else
                state = 16;
            pos++;
            break;

        case 17:
            if (input[pos] == '*')
                state = 36;
            else
                state = 17;
            pos++;
            break;

        case 18:
            tok = new Token(OP, DIV);
            return tok;

        case 19:
            tok = new Token(OP, MODULE);
            return tok;

        case 20:
            if (input[pos] == '=')
                state = 21;
            else
                state = 22;
            pos++;
            break;

        case 21:
            tok = new Token(OP, NE);
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

        case 29:
            if (input[pos] == '"')
                state = 35;
            else
                state = 29;

            lexeme += input[pos];
            pos++;
            break;

        case 30:
            if (isalnum(input[pos]))
                state = 30;
            else if (input[pos] == '_')
                state = 30;
            else
            {
                state = 31;
                pos++;
                break;
            }
            lexeme += input[pos];
            pos++;
            break;

        case 31:
            if (st->get(lexeme))
            {
                tok = new Token(st->get(lexeme)->token->name, lexeme);
            }
            else
                tok = new Token(ID, lexeme);

            pos--;
            return tok;

        case 32:
            if (isdigit(input[pos]))
                state = 32;
            else
                state = 33;

            pos++;
            break;

        case 33:
            tok = new Token(INTEGER_LITERAL, lexeme);
            pos--;
            return tok;

        case 34:
            state = 0;
            lexeme = "";
            break;

        case 35:
            tok = new Token(STRING, lexeme);
            return tok;

        case 36:
            if (input[pos] == '/')
                state = 34;
            else
                state = 17;
            pos++;
            break;

        case 37:
            tok = new Token(SEP, COMMA);
            return tok;

        default:
            lexicalError();
        }
    }

} // Fim nextToken

void Scanner::lexicalError()
{
    cout << "Token mal formado\n";

    exit(EXIT_FAILURE);
}

Token *Scanner::checkNextToken(int pseudoPos)
{
    Token *tok;
    int state = 0;
    string lexeme = "";

    if (pseudoPos == -1)
        pseudoPos = pos;

    while (true)
    {
        // std::cout << "Analyzing: " << input[pseudoPos] << " in position " << pseudoPos << " and in State " << state << "\n";

        switch (state)
        {
        case 0: // case 9: case12: case22:
            if (input[pseudoPos] == '\0')
            {
                tok = new Token(END_OF_FILE);
                return tok;
            }
            if (input[pseudoPos] == '<')
                state = 1;
            else if (input[pseudoPos] == '>')
                state = 4;
            else if (input[pseudoPos] == '=')
                state = 7;
            else if (input[pseudoPos] == '+')
                state = 10;
            else if (input[pseudoPos] == '-')
                state = 11;
            else if (input[pseudoPos] == '*')
                state = 12;
            else if (input[pseudoPos] == '/')
                state = 15;
            else if (input[pseudoPos] == '%')
                state = 19;
            else if (input[pseudoPos] == '!')
                state = 20;
            else if (input[pseudoPos] == '(')
                state = 22;
            else if (input[pseudoPos] == ')')
                state = 23;
            else if (input[pseudoPos] == '[')
                state = 24;
            else if (input[pseudoPos] == ']')
                state = 25;
            else if (input[pseudoPos] == '{')
                state = 26;
            else if (input[pseudoPos] == '}')
                state = 27;
            else if (input[pseudoPos] == ';')
                state = 28;
            else if (input[pseudoPos] == '"')
                state = 29;
            else if (isalpha(input[pseudoPos]))
                state = 30;
            else if (input[pseudoPos] == '_')
                state = 30;
            else if (isdigit(input[pseudoPos]))
                state = 32;
            else if (isspace(input[pseudoPos]))
                state = 34;
            else if (input[pseudoPos] == '\n')
            {
                lineID++;
                state = 34;
            }
            else if (input[pseudoPos] == ',')
                state = 37;
            else
                lexicalError();
            // cout << state << " ";
            lexeme += input[pseudoPos];
            pseudoPos++;

            break;
        case 1:
            if (input[pseudoPos] == '=')
                state = 2;
            else
                state = 3;
            pseudoPos++;
            break;

        case 2:
            tok = new Token(OP, LE);
            return tok;

        case 3:
            tok = new Token(OP, LT);
            return tok;

        case 4:
            if (input[pseudoPos] == '=')
                state = 5;
            else
                state = 6;
            pseudoPos++;
            break;

        case 5:
            tok = new Token(OP, GE);
            return tok;

        case 6:
            tok = new Token(OP, GT);
            return tok;

        case 7:
            if (input[pseudoPos] == '=')
                state = 8;
            else
                state = 9;
            pseudoPos++;
            break;

        case 8:
            tok = new Token(OP, EQ);
            return tok;

        case 9:
            tok = new Token(OP, ASSIGN);
            return tok;

        case 10:
            tok = new Token(OP, ADD);
            return tok;

        case 11:
            tok = new Token(OP, SUB);
            return tok;

        case 12:
            if (input[pseudoPos] == '/')
                state = 13;
            else
                state = 14;
            pseudoPos++;
            break;

        case 13:
            tok = new Token(COMMENT, RBLOCKCOMMENT);
            return tok;

        case 14:
            tok = new Token(OP, MUL);
            return tok;

        case 15:
            if (input[pseudoPos] == '/')
                state = 16;
            else if (input[pseudoPos] == '*')
                state = 17;
            else
                state = 18;
            pseudoPos++;
            break;

        case 16:
            if (input[pseudoPos] == '\n')
            {
                lineID++;
                state = 34;
            }
            else
                state = 16;
            pseudoPos++;
            break;

        case 17:
            if (input[pseudoPos] == '*')
                state = 36;
            else
                state = 17;
            pseudoPos++;
            break;

        case 18:
            tok = new Token(OP, DIV);
            return tok;

        case 19:
            tok = new Token(OP, MODULE);
            return tok;

        case 20:
            if (input[pseudoPos] == '=')
                state = 21;
            else
                state = 22;
            pseudoPos++;
            break;

        case 21:
            tok = new Token(OP, NE);
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

        case 29:
            if (input[pseudoPos] == '"')
                state = 35;
            else
                state = 29;

            lexeme += input[pseudoPos];
            pseudoPos++;
            break;

        case 30:
            if (isalnum(input[pseudoPos]))
                state = 30;
            else if (input[pseudoPos] == '_')
                state = 30;
            else
            {
                state = 31;
                pseudoPos++;
                break;
            }
            lexeme += input[pseudoPos];
            pseudoPos++;
            break;

        case 31:
            if (st->get(lexeme))
            {
                tok = new Token(st->get(lexeme)->token->name, lexeme);
            }
            else
                tok = new Token(ID, lexeme);

            pseudoPos--;
            return tok;

        case 32:
            if (isdigit(input[pseudoPos]))
                state = 32;
            else
                state = 33;

            pseudoPos++;
            break;

        case 33:
            tok = new Token(INTEGER_LITERAL, lexeme);
            pseudoPos--;
            return tok;

        case 34:
            state = 0;
            lexeme = "";
            break;

        case 35:
            tok = new Token(STRING, lexeme);
            return tok;

        case 36:
            if (input[pseudoPos] == '/')
                state = 34;
            else
                state = 17;
            pseudoPos++;
            break;

        case 37:
            tok = new Token(SEP, COMMA);
            return tok;

        default:
            lexicalError();
        }
    }
}

int Scanner::getPos()
{
    return pos;
}

void Scanner::populateSymbolTable()
{
    Token *t;

    t = new Token(CLASS, "class");
    st->add(new STEntry(t, true));
    t = new Token(EXTENDS, "extends");
    st->add(new STEntry(t, true));
    t = new Token(INT, "int");
    st->add(new STEntry(t, true));
    t = new Token(STRING_T, "string");
    st->add(new STEntry(t, true));
    t = new Token(BREAK, "break");
    st->add(new STEntry(t, true));
    t = new Token(PRINT, "print");
    st->add(new STEntry(t, true));
    t = new Token(READ, "read");
    st->add(new STEntry(t, true));
    t = new Token(RETURN, "return");
    st->add(new STEntry(t, true));
    t = new Token(SUPER, "super");
    st->add(new STEntry(t, true));
    t = new Token(IF, "if");
    st->add(new STEntry(t, true));
    t = new Token(ELSE, "else");
    st->add(new STEntry(t, true));
    t = new Token(FOR, "for");
    st->add(new STEntry(t, true));
    t = new Token(NEW, "new");
    st->add(new STEntry(t, true));
    t = new Token(CONSTRUCTOR, "constructor");
    st->add(new STEntry(t, true));
}
