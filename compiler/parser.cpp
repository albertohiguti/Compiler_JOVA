#include "parser.h"

Parser::Parser(string input)
{
	scanner = new Scanner(input);
}

void Parser::advance()
{
	lToken = scanner->nextToken();
}

void Parser::match(int t)
{
	if (lToken->name == t || lToken->attribute == t)
		advance();
	else
		error("Erro inesperado");
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
	match(CLASS);
	match(ID);

	if (lToken->attribute == EXTENDS)
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
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID)
		varDeclList();
}

void Parser::varDeclList()
{
	varDecl();
	varDeclListLine();
}

void Parser::varDecl()
{
	type();
	if (lToken->attribute == LSQUARE)
	{
		match(LSQUARE);
		match(RSQUARE);
	}

	match(ID);
	varDeclOpt();
	match(SEMICOLON);
}

void Parser::varDeclOpt()
{
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		match(ID);
		varDeclOpt();
	}
}

void Parser::type()
{
	if (lToken->attribute == INT)
		match(INT);
	else if (lToken->attribute == STRING_T)
		match(STRING_T);
	else
		match(ID);
}

void Parser::constructDeclListOpt()
{
	if (lToken->attribute == CONSTRUCTOR)
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
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID)
		methodDeclList();
}

void Parser::methodDeclList()
{
	methodDecl();
	methodDeclListLine();
}

void Parser::methodDecl()
{
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
	match(LPARENTESES);
	paramListOpt();
	match(RPARENTESES);
	match(LBRACE);
	statementsOpt();
	match(RBRACE);
}

void Parser::paramListOpt()
{
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID)
		paramList();
}

void Parser::paramList()
{
	param();
	paramListLine();
}

void Parser::param()
{
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
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID || lToken->attribute == PRINT || lToken->attribute == READ || lToken->attribute == RETURN || lToken->attribute == SUPER || lToken->attribute == IF || lToken->attribute == FOR || lToken->attribute == BREAK || lToken->attribute == SEMICOLON)
		statements();
}

void Parser::statements()
{
	statement();
	statementsLine();
}

void Parser::statement()
{
	if (lToken->attribute == INT || lToken->attribute == STRING_T)
		varDeclList();
	else if (lToken->attribute == ID)
	{
		// find how to solve the ambiguity
	}
	else if (lToken->attribute == PRINT)
	{
		printStat();
		match(SEMICOLON);
	}
	else if (lToken->attribute == READ)
	{
		readStat();
		match(SEMICOLON);
	}
	else if (lToken->attribute == RETURN)
	{
		returnStat();
		match(SEMICOLON);
	}
	else if (lToken->attribute == SUPER)
	{
		superStat();
		match(SEMICOLON);
	}
	else if (lToken->attribute == IF)
		ifStat();
	else if (lToken->attribute == FOR)
		forStat();
	else if (lToken->attribute == BREAK)
	{
		match(BREAK);
		match(SEMICOLON);
	}
	else
		match(SEMICOLON);
}

void Parser::atribStat()
{
	lValue();
	match(ASSIGN);
	if (lToken->attribute == NEW)
		AllocExpression();
	else
		expression();
}

void Parser::printStat()
{
	match(PRINT);
	expression();
}

void Parser::readStat()
{
	match(READ);
	lValue();
}

void Parser::returnStat()
{
	match(RETURN);
	expression();
}

void Parser::superStat()
{
	match(SUPER);
	match(LPARENTESES);
	argListOpt();
	match(RPARENTESES);
}

void Parser::ifStat()
{
	match(IF);
	match(LPARENTESES);
	expression();
	match(RPARENTESES);
	match(LBRACE);
	statements();
	match(RBRACE);

	if (lToken->attribute == ELSE)
	{
		match(ELSE);
		match(LBRACE);
		statements();
		match(RBRACE);
	}
}

void Parser::forStat()
{
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
	if (lToken->attribute == ID)
		lValue();
	match(ASSIGN);
	if (lToken->attribute == NEW)
		AllocExpression();
	else
		expression();
}

void Parser::expressionOpt()
{
	if (lToken->attribute == ADD || lToken->attribute == SUB)
		expression();
}

void Parser::lValue()
{
	match(ID);
	lValueComp();
}

void Parser::lValueComp()
{
	if (lToken->attribute == DOT)
	{
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
	numExpression();

	if (lToken->name == OP)
	{
		match(lToken->attribute);
		numExpression();
	}
}

void Parser::AllocExpression()
{
	if (lToken->attribute == NEW)
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
	term();

	if (lToken->attribute == ADD || lToken->attribute == SUB)
	{
		match(lToken->attribute);
		term();
	}
}

void Parser::term()
{
	unaryExpression();

	if (lToken->attribute == MUL || lToken->attribute == DIV || lToken->attribute == MODULE)
	{
		match(lToken->attribute);
		unaryExpression();
	}
}

void Parser::unaryExpression()
{
	match(lToken->attribute);
	factor();
}

void Parser::factor()
{
	if (lToken->name == INTEGER_LITERAL)
		match(INTEGER_LITERAL);
	else if (lToken->name == STRING)
		match(STRING);
	else if (lToken->attribute == ID)
	{
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
	if (lToken->attribute == ADD || lToken->attribute == SUB)
		argList();
}

void Parser::argList()
{
	expression();
	argListLine();
}

void Parser::varDeclListLine()
{
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID)
	{
		varDecl();
		varDeclListLine();
	}
}

void Parser::constructDeclListLine()
{
	if (lToken->atrr == CONSTRUCTOR)
	{
		constructDecl();
		constructDeclListLine();
	}
}

void Parser::methodDeclListLine()
{
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID)
	{
		methodDecl();
		methodDeclListLine();
	}
}

void Parser::paramListLine()
{
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		param();
		paramListLine();
	}
}

void Parser::statementsLine()
{
	// solve the first ambiguity to solve this method
	if (lToken->attribute == INT || lToken->attribute == STRING_T || lToken->attribute == ID || lToken->attribute == PRINT || lToken->attribute == READ || lToken->attribute == RETURN || lToken->attribute == SUPER || lToken->attribute == IF || lToken->attribute == FOR || lToken->attribute == BREAK || lToken->attribute == SEMICOLON)
	{
		statement();
		statementsLine();
	}
}

void Parser::argListLine()
{
	if (lToken->attribute == COMMA)
	{
		match(COMMA);
		expression();
		argListLine();
	}
}

void Parser::error(string str)
{
	// cout << "Linha " << scanner->getLine() << ": " << str << endl;

	exit(EXIT_FAILURE);
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