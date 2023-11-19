#include "scanner.h"

class Parser
{
private:
	Scanner *scanner;
	Token *lToken;
	Token *cToken;
	string *attributes_translator, *name_translator;
	bool debugMode;

	void advance();
	void match(int);
	void lookAhead(int pseudoPos = -1);
	void createEnumTranslator();

public:
	Parser(string, bool);
	void run();
	void program();
	void classList();
	void classDecl();
	void classBody();
	void varDeclListOpt();
	void varDeclList();
	void varDecl();
	void varDeclOpt();
	void type();
	void constructDeclListOpt();
	void constructDeclList();
	void constructDecl();
	void methodDeclListOpt();
	void methodDeclList();
	void methodDecl();
	void methodBody();
	void paramListOpt();
	void paramList();
	void param();
	void statementsOpt();
	void statements();
	void statement();
	void atribStat();
	void printStat();
	void readStat();
	void returnStat();
	void superStat();
	void ifStat();
	void forStat();
	void atribStatOpt();
	void expressionOpt();
	void lValue();
	void lValueComp();
	void expression();
	void AllocExpression();
	void numExpression();
	void term();
	void unaryExpression();
	void factor();
	void argListOpt();
	void argList();
	void varDeclListLine();
	void constructDeclListLine();
	void methodDeclListLine();
	void paramListLine();
	void statementsLine();
	void argListLine();

	void error(string);
};