#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
	this->createEnumTranslator();
}

void Parser::advance()
{
	lToken = scanner->nextToken();
	std::cout << "Leu o token " << name_translator[lToken->name] << " " << attributes_translator[lToken->attribute] << " " << lToken->lexeme << "\n";
}

void Parser::lookAhead(int pseudoPos)
{
	cToken = scanner->checkNextToken(pseudoPos);
}

void Parser::match(int t)
{
	std::string name = name_translator[t];
	std::string attribute = attributes_translator[t];
	std::string tokenName = name_translator[lToken->name];
	std::string tokenAttribute = attributes_translator[lToken->attribute];

	std::cout << "Trying to match " << tokenName << " Or " << tokenAttribute << " With " << name << " Or " << attribute << "\n";
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado " + std::to_string(lToken->name) + " " + std::to_string(lToken->attribute) + " " + std::to_string(t));
}

void Parser::run()
{
	advance();
	program();
	cout << "Compilação encerrada com sucesso!\n";
}

void Parser::program()
{
	classList();
}

void Parser::classList()
{
	classDecl();

	if (lToken->name != END_OF_FILE)
		classList();
}

void Parser::classDecl()
{
	std::cout << "classDecl" << std::endl;
	match(CLASS);
	match(ID);

	if (lToken->name == EXTENDS)
	{
		match(EXTENDS);
		match(ID);
	}

	classBody();
}

void Parser::classBody()
{
	match(LBRACE);
	varDeclListOpt();
	constructDeclListOpt();
	methodDeclListOpt();
	match(RBRACE);
}

void Parser::varDeclListOpt()
{
	std::cout << "varDeclListOpt" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID)
		varDeclList();
}

void Parser::varDeclList()
{
	std::cout << "varDeclList" << std::endl;
	varDecl();
	varDeclListLine();
}

void Parser::varDecl()
{
	std::cout << "varDecl" << std::endl;
	type();
	if (lToken->attribute == LSQUARE)
	{
		match(LSQUARE);
		match(RSQUARE);
	}

	match(ID);
	varDeclOpt();
	std::cout << "leu o opcional e ta indo ler o ;" << std::endl;
	match(SEMICOLON);
}

void Parser::varDeclOpt()
{
	std::cout << "varDeclOpt" << std::endl;
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		match(ID);
		varDeclOpt();
	}
}

void Parser::type()
{
	std::cout << "type" << std::endl;
	if (lToken->name == INT)
		match(INT);
	else if (lToken->name == STRING_T)
		match(STRING_T);
	else
		match(ID);
}

void Parser::constructDeclListOpt()
{
	std::cout << "constructDeclListOpt" << std::endl;
	if (lToken->name == CONSTRUCTOR)
		constructDeclList();
}

void Parser::constructDeclList()
{
	constructDecl();
	constructDeclListLine();
}

void Parser::constructDecl()
{
	match(CONSTRUCTOR);
	methodBody();
}

void Parser::methodDeclListOpt()
{
	std::cout << "methodDeclListOpt" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID)
		methodDeclList();
}

void Parser::methodDeclList()
{
	std::cout << "methodDeclList" << std::endl;
	methodDecl();
	methodDeclListLine();
}

void Parser::methodDecl()
{
	std::cout << "methodDecl" << std::endl;
	type();
	if (lToken->attribute == LSQUARE)
	{
		match(LSQUARE);
		match(RSQUARE);
	}

	match(ID);
	methodBody();
}

void Parser::methodBody()
{
	std::cout << "methodBody" << std::endl;
	match(LPARENTESES);
	paramListOpt();
	match(RPARENTESES);
	match(LBRACE);
	statementsOpt();
	match(RBRACE);
}

void Parser::paramListOpt()
{
	std::cout << "paramListOpt" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID)
		paramList();
}

void Parser::paramList()
{
	std::cout << "paramList" << std::endl;
	param();
	paramListLine();
}

void Parser::param()
{
	cout << "param" << endl;
	type();
	if (lToken->attribute == LSQUARE)
	{
		match(LSQUARE);
		match(RSQUARE);
	}

	match(ID);
}

void Parser::statementsOpt()
{
	std::cout << "statementsOpt" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
		statements();
}

void Parser::statements()
{
	std::cout << "statements" << std::endl;
	statement();
	statementsLine();
}

void Parser::statement()
{
	std::cout << "statement" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T)
	{
		std::cout << "entrou no int ou string" << std::endl;
		varDeclList();
	}
	else if (lToken->name == ID)
	{

		lookAhead();
		std::cout << "Look ahead result: " << name_translator[cToken->name] << " " << attributes_translator[cToken->attribute] << "\n";
		if (cToken->attribute == ASSIGN)
		{
			atribStat();
		}
		else if (cToken->attribute == DOT)
		{
			atribStat();
		}
		else if (cToken->name == ID)
		{
			varDeclList();
		}
		else if (cToken->attribute == LSQUARE)
		{
			lookAhead(scanner->getPos() + 1);
			std::cout << "Look ahead result: " << name_translator[cToken->name] << " " << attributes_translator[cToken->attribute] << "\n";
			if (cToken->attribute == RSQUARE)
				varDeclList();
			else
				atribStat();
		}
	}
	else if (lToken->name == PRINT)
	{
		printStat();
		match(SEMICOLON);
	}
	else if (lToken->name == READ)
	{
		readStat();
		match(SEMICOLON);
	}
	else if (lToken->name == RETURN)
	{
		returnStat();
		match(SEMICOLON);
	}
	else if (lToken->name == SUPER)
	{
		superStat();
		match(SEMICOLON);
	}
	else if (lToken->name == IF)
		ifStat();
	else if (lToken->name == FOR)
		forStat();
	else if (lToken->name == BREAK)
	{
		match(BREAK);
		match(SEMICOLON);
	}
	else
		match(SEMICOLON);
}

void Parser::atribStat()
{
	std::cout << "atribStat" << std::endl;
	lValue();
	match(ASSIGN);
	if (lToken->name == NEW)
		AllocExpression();
	else
		expression();
}

void Parser::printStat()
{
	std::cout << "printStat" << std::endl;
	match(PRINT);
	expression();
}

void Parser::readStat()
{
	std::cout << "readStat" << std::endl;
	match(READ);
	cout << "readStat" << endl;
	lValue();
}

void Parser::returnStat()
{
	std::cout << "returnStat" << std::endl;
	match(RETURN);
	expression();
}

void Parser::superStat()
{
	std::cout << "superStat" << std::endl;
	match(SUPER);
	match(LPARENTESES);
	argListOpt();
	match(RPARENTESES);
}

void Parser::ifStat()
{
	std::cout << "ifStat" << std::endl;
	match(IF);
	match(LPARENTESES);
	expression();
	match(RPARENTESES);
	match(LBRACE);
	statements();
	match(RBRACE);

	if (lToken->name == ELSE)
	{
		match(ELSE);
		match(LBRACE);
		statements();
		match(RBRACE);
	}
}

void Parser::forStat()
{
	std::cout << "forStat" << std::endl;
	match(FOR);
	match(LPARENTESES);
	atribStatOpt();
	match(SEMICOLON);
	expressionOpt();
	match(SEMICOLON);
	atribStatOpt();
	match(RPARENTESES);
	match(LBRACE);
	statements();
	match(RBRACE);
}

void Parser::atribStatOpt()
{
	std::cout << "atribStatOpt" << std::endl;
	if (lToken->name == ID)
	{
		lValue();
		match(ASSIGN);
		if (lToken->name == NEW)
			AllocExpression();
		else
			expression();
	}
}

void Parser::expressionOpt()
{
	std::cout << "expressionOpt" << std::endl;
	if (lToken->attribute == ADD || lToken->attribute == SUB)
		expression();
}

void Parser::lValue()
{
	std::cout << "lvalue" << std::endl;
	match(ID);
	lValueComp();
}

void Parser::lValueComp()
{
	std::cout << "lvaluecomp" << std::endl;
	if (lToken->attribute == DOT)
	{
		std::cout << "entrou no lvaluecomp" << std::endl;
		match(DOT);
		match(ID);
		if (lToken->attribute == LSQUARE)
		{
			match(LSQUARE);
			expression();
			match(RSQUARE);
		}
		else if (lToken->attribute == LPARENTESES)
		{
			match(LPARENTESES);
			argListOpt();
			match(RPARENTESES);
		}
		lValueComp();
	}
	else if (lToken->attribute == LSQUARE)
	{
		match(LSQUARE);
		expression();
		match(RSQUARE);
		lValueComp();
	}
}

void Parser::expression()
{
	std::cout << "expression" << std::endl;
	numExpression();

	if (lToken->name == OP)
	{
		match(lToken->attribute);
		numExpression();
	}
}

void Parser::AllocExpression()
{
	std::cout << "AllocExpression" << std::endl;
	if (lToken->name == NEW)
	{
		match(NEW);
		match(ID);
		match(LPARENTESES);
		argListOpt();
		match(RPARENTESES);
	}
	else
	{
		type();
		match(LSQUARE);
		expression();
		match(RSQUARE);
	}
}

void Parser::numExpression()
{
	std::cout << "numExpression" << std::endl;
	term();

	if (lToken->attribute == ADD || lToken->attribute == SUB)
	{
		match(lToken->attribute);
		term();
	}
}

void Parser::term()
{
	std::cout << "term" << std::endl;
	unaryExpression();

	if (lToken->attribute == MUL || lToken->attribute == DIV || lToken->attribute == MODULE)
	{
		match(lToken->attribute);

		unaryExpression();
	}
}

void Parser::unaryExpression()
{
	std::cout << "unaryExpression" << std::endl;
	if (lToken->attribute == ADD || lToken->attribute == SUB)
	{
		match(lToken->attribute);
		factor();
	}
}

void Parser::factor()
{
	std::cout << "factor" << std::endl;
	if (lToken->name == INTEGER_LITERAL)
		match(INTEGER_LITERAL);
	else if (lToken->name == STRING)
		match(STRING);
	else if (lToken->name == ID)
	{
		match(ID);
		lValueComp();
	}
	else
	{
		match(LPARENTESES);
		expression();
		match(RPARENTESES);
	}
}

void Parser::argListOpt()
{
	std::cout << "argListOpt" << std::endl;
	if (lToken->attribute == ADD || lToken->attribute == SUB)
		argList();
}

void Parser::argList()
{
	std::cout << "argList" << std::endl;
	expression();
	argListLine();
}

void Parser::varDeclListLine()
{
	std::cout << "varDeclListLine" << std::endl;
	lookAhead(scanner->getPos() + 0);
	if ((lToken->name == INT || lToken->name == STRING_T || lToken->name == ID) && (cToken->name == ID || cToken->attribute == LSQUARE))
	{
		varDecl();
		varDeclListLine();
	}
}

void Parser::constructDeclListLine()
{
	if (lToken->name == CONSTRUCTOR)
	{
		constructDecl();
		constructDeclListLine();
	}
}

void Parser::methodDeclListLine()
{
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID)
	{
		methodDecl();
		methodDeclListLine();
	}
}

void Parser::paramListLine()
{
	std::cout << "paramListLine" << std::endl;
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		param();
		paramListLine();
	}
}

void Parser::statementsLine()
{
	std::cout << "statementsLine" << std::endl;
	if (lToken->name == INT || lToken->name == STRING_T || lToken->name == ID || lToken->name == PRINT || lToken->name == READ || lToken->name == RETURN || lToken->name == SUPER || lToken->name == IF || lToken->name == FOR || lToken->name == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		statementsLine();
	}
}

void Parser::argListLine()
{
	std::cout << "argListLine" << std::endl;
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		expression();
		argListLine();
	}
}

void Parser::error(string str)
{
	cout << str << endl;

	exit(EXIT_FAILURE);
}

void Parser::createEnumTranslator()
{
	attributes_translator = new string[28]{
		"UNDEF",		 // 0
		"EQ",			 // 1
		"NE",			 // 2
		"GT",			 // 3
		"GE",			 // 4
		"LT",			 // 5
		"LE",			 // 6
		"ASSIGN",		 // 7
		"ADD",			 // 8
		"SUB",			 // 9
		"MUL",			 // 10
		"DIV",			 // 11
		"MODULE",		 // 12
		"LPARENTESES",	 // 13
		"RPARENTESES",	 // 14
		"LSQUARE",		 // 15
		"RSQUARE",		 // 16
		"LBRACE",		 // 17
		"RBRACE",		 // 18
		"DOT",			 // 19
		"SEMICOLON",	 // 20
		"COMMA",		 // 21
		"QUOTE",		 // 22
		"LQUOTE",		 // 23
		"RQUOTE",		 // 24
		"LINECOMMENT",	 // 25
		"LBLOCKCOMMENT", // 26
		"RBLOCKCOMMENT"	 // 27
	};

	name_translator = new string[28]{
		"ID",
		"INTEGER_LITERAL",
		"OP",
		"SEP",
		"STRING",
		"COMMENT",
		"END_OF_FILE",
		"CLASS",
		"EXTENDS",
		"INT",
		"STRING_T",
		"BREAK",
		"PRINT",
		"READ",
		"RETURN",
		"SUPER",
		"IF",
		"ELSE",
		"FOR",
		"NEW",
		"CONSTRUCTOR"};
}
/*
Program -> ClassList
					  | ϵ
		   ClassList -> ClassDecl ClassList
					  | ClassDecl
		   ClassDecl -> class ID ClassBody
					  | class ID extends ID ClassBody
		   ClassBody -> { VarDeclListOpt ConstructDeclListOpt MethodDeclListOpt }
	  VarDeclListOpt -> VarDeclList
					  | ϵ
		 VarDeclList -> VarDecl VarDeclListLine
			 VarDecl -> Type ID VarDeclOpt ;
					  | Type [] ID VarDeclOpt ;
		  VarDeclOpt -> , ID VarDeclOpt
					  | ϵ
				Type -> int
					  | string
					  | ID
	ConstructDeclListOpt -> ConstructDeclList
					  | ϵ
	ConstructDeclList -> ConstructDecl ConstructDeclListLine
	   ConstructDecl -> constructor MethodBody
	MethodDeclListOpt -> MethodDeclList
					  | ϵ
	  MethodDeclList -> MethodDecl MethodDeclListLine
		  MethodDecl -> Type ID MethodBody | Type [] ID MethodBody
		  MethodBody -> ( ParamListOpt ) { StatementsOpt }
		ParamListOpt -> ParamList
					  | ϵ
		   ParamList -> Param ParamListLine
			   Param -> Type ID | Type [] ID
	   StatementsOpt -> Statements
					  | ϵ
		  Statements -> Statement StatementsLine
		   Statement -> VarDeclList
					  | AtribStat ;
					  | PrintStat ;
					  | ReadStat ;
					  | ReturnStat ;
					  | SuperStat ;
					  | IfStat
					  | ForStat
					  | break ;
					  | ;
		   AtribStat -> LValue = Expression
					  | LValue = AllocExpression
		   PrintStat -> print Expression
			ReadStat -> read LValue
		  ReturnStat -> return Expression
		   SuperStat -> super ( ArgListOpt )
			  IfStat -> if ( Expression ) { Statements }
					  | if ( Expression ) { Statements } else { Statements }
			 ForStat -> for ( AtribStatOpt ; ExpressionOpt ; AtribStatOpt ) { Statements }
		AtribStatOpt -> LValue = Expression
					  | LValue = AllocExpression
					  | ϵ
	   ExpressionOpt -> Expression
					  | ϵ
			  LValue -> ID LValueComp
		  LValueComp -> . ID LValueComp
					  | . ID [ Expression ] LValueComp
					  | . ID ( ArgListOpt ) LValueComp
					  | [ Expression ] LValueComp
					  | ϵ
		  Expression -> NumExpression
					  | NumExpression RelOp NumExpression
	 AllocExpression -> new ID ( ArgListOpt )
					  | Type [ Expression ]
	   NumExpression -> Term + Term
					  | Term - Term
					  | Term
				Term -> UnaryExpression * UnaryExpression
					  | UnaryExpression / UnaryExpression
					  | UnaryExpression % UnaryExpression
					  | UnaryExpression
	 UnaryExpression -> + Factor
					  | - Factor
			  Factor -> INTEGER_LITERAL
					  | STRING_LITERAL
					  | ID LValueComp
					  | ( Expression )
		ArgListOpt -> ArgList
					  | ϵ
		ArgList -> Expression ArgListLine
	VarDeclListLine -> VarDecl VarDeclListLine
					  | ϵ
	ConstructDeclListLine -> ConstructDecl ConstructDeclListLine
					  | ϵ
	 MethodDeclListLine -> MethodDecl MethodDeclListLine
					  | ϵ
		  ParamListLine -> , Param ParamListLine
					  | ϵ
		 StatementsLine -> Statement StatementsLine
					  | ϵ
			ArgListLine -> , Expression ArgListLine
					  | ϵ
*/
