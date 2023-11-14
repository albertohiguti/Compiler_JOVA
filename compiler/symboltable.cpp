#include "symboltable.h"

SymbolTable::SymbolTable()
{
    parent = 0;
}

bool SymbolTable::add(STEntry *t)
{
    if (!(symbols.find(t->token->lexeme) == symbols.end()))
        return false;
    symbols.insert({t->token->lexeme, t});
    return true;
}

bool SymbolTable::remove(string name)
{
    return symbols.erase(name) != 0;
}

void SymbolTable::clear()
{
    symbols.clear();
}

bool SymbolTable::isEmpty()
{
    return symbols.empty();
}

STEntry *SymbolTable::get(string name)
{
    SymbolTable *table = this;

    auto s = table->symbols.find(name);

    if (s != table->symbols.end())
        return s->second;
    else
    {
        return 0;
    }
}
