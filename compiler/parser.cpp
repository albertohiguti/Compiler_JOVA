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
	// TODO
	mainClass();
}

// Continuar....

void Parser::mainClass()
{
}

void Parser::error(string str)
{
	cout << "Linha " << scanner->getLine() << ": " << str << endl;

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
		 VarDeclList -> VarDecl VarDeclList'
			 VarDecl -> Type ID VarDeclOpt ;
					  | Type [] ID VarDeclOpt ;
		  VarDeclOpt -> , ID VarDeclOpt
					  | ϵ
				Type -> int
					  | string
					  | ID
	ConstructDeclListOpt -> ConstructDeclList
					  | ϵ
	ConstructDeclList -> ConstructDecl ConstructDeclList'
	   ConstructDecl -> constructor MethodBody
	MethodDeclListOpt -> MethodDeclList
					  | ϵ
	  MethodDeclList -> MethodDecl MethodDeclList'
		  MethodDecl -> int ID MethodBody
					  | string ID MethodBody
					  | ID ID MethodBody
					  | int [] id MethodBody
					  | string [] id MethodBody
					  | ID [] id MethodBody
		  MethodBody -> ( ParamListOpt ) { StatementsOpt }
		ParamListOpt -> ParamList
					  | ϵ
		   ParamList -> Param ParamList'
			   Param -> int ID
					  | string ID
					  | ID ID
					  | int [] ID
					  | string [] ID
					  | ID [] ID
	   StatementsOpt -> Statements
					  | ϵ
		  Statements -> Statement Statements'
		   Statement -> int ID VarDeclOpt ; VarDeclList'
					  | string ID VarDeclOpt ; VarDeclList'
					  | ID ID VarDeclOpt ; VarDeclList'
					  | int [] ID VarDeclOpt ; VarDeclList'
					  | string [] ID VarDeclOpt ; VarDeclList'
					  | ID [] ID VarDeclOpt ; VarDeclList'
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
					  | int [ Expression ]
					  | string [ Expression ]
					  | ID [ Expression ]
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
			 ArgList -> + Factor * UnaryExpression + Term ArgList'
					  | - Factor * UnaryExpression + Term ArgList'
					  | + Factor / UnaryExpression + Term ArgList'
					  | - Factor / UnaryExpression + Term ArgList'
					  | + Factor % UnaryExpression + Term ArgList'
					  | - Factor % UnaryExpression + Term ArgList'
					  | + Factor + Term ArgList'
					  | - Factor + Term ArgList'
					  | + Factor * UnaryExpression - Term ArgList'
					  | - Factor * UnaryExpression - Term ArgList'
					  | + Factor / UnaryExpression - Term ArgList'
					  | - Factor / UnaryExpression - Term ArgList'
					  | + Factor % UnaryExpression - Term ArgList'
					  | - Factor % UnaryExpression - Term ArgList'
					  | + Factor - Term ArgList'
					  | - Factor - Term ArgList'
					  | + Factor * UnaryExpression ArgList'
					  | - Factor * UnaryExpression ArgList'
					  | + Factor / UnaryExpression ArgList'
					  | - Factor / UnaryExpression ArgList'
					  | + Factor % UnaryExpression ArgList'
					  | - Factor % UnaryExpression ArgList'
					  | + Factor ArgList'
					  | - Factor ArgList'
					  | + Factor * UnaryExpression + Term RelOp NumExpression ArgList'
					  | - Factor * UnaryExpression + Term RelOp NumExpression ArgList'
					  | + Factor / UnaryExpression + Term RelOp NumExpression ArgList'
					  | - Factor / UnaryExpression + Term RelOp NumExpression ArgList'
					  | + Factor % UnaryExpression + Term RelOp NumExpression ArgList'
					  | - Factor % UnaryExpression + Term RelOp NumExpression ArgList'
					  | + Factor + Term RelOp NumExpression ArgList'
					  | - Factor + Term RelOp NumExpression ArgList'
					  | + Factor * UnaryExpression - Term RelOp NumExpression ArgList'
					  | - Factor * UnaryExpression - Term RelOp NumExpression ArgList'
					  | + Factor / UnaryExpression - Term RelOp NumExpression ArgList'
					  | - Factor / UnaryExpression - Term RelOp NumExpression ArgList'
					  | + Factor % UnaryExpression - Term RelOp NumExpression ArgList'
					  | - Factor % UnaryExpression - Term RelOp NumExpression ArgList'
					  | + Factor - Term RelOp NumExpression ArgList'
					  | - Factor - Term RelOp NumExpression ArgList'
					  | + Factor * UnaryExpression RelOp NumExpression ArgList'
					  | - Factor * UnaryExpression RelOp NumExpression ArgList'
					  | + Factor / UnaryExpression RelOp NumExpression ArgList'
					  | - Factor / UnaryExpression RelOp NumExpression ArgList'
					  | + Factor % UnaryExpression RelOp NumExpression ArgList'
					  | - Factor % UnaryExpression RelOp NumExpression ArgList'
					  | + Factor RelOp NumExpression ArgList'
					  | - Factor RelOp NumExpression ArgList'
		VarDeclList' -> VarDecl VarDeclList'
					  | ϵ
	ConstructDeclList' -> ConstructDecl ConstructDeclList'
					  | ϵ
	 MethodDeclList' -> MethodDecl MethodDeclList'
					  | ϵ
		  ParamList' -> , Param ParamList'
					  | ϵ
		 Statements' -> Statement Statements'
					  | ϵ
			ArgList' -> , Expression ArgList'
					  | ϵ
*/

// Program -> ClassList | ϵ
// ClassList -> ClassDecl ClassList | ClassDecl
// ClassDecl -> class ID ClassBody | class ID extends ID ClassBody
// ClassBody -> { VarDeclListOpt ConstructDeclListOpt MethodDeclListOpt }
// VarDeclListOpt -> VarDeclList | ϵ
// VarDeclList -> VarDecl VarDeclListTail
// VarDeclListTail -> , VarDecl VarDeclListTail | ϵ
// VarDecl -> Type VarDeclRest ;
// VarDeclRest -> ID VarDeclOpt | [] ID VarDeclOpt
// VarDeclOpt -> , ID VarDeclOpt | ϵ
// Type -> int | string | ID
// ConstructDeclListOpt -> ConstructDeclList | ϵ
// ConstructDeclList -> ConstructDecl ConstructDeclList
// ConstructDecl -> constructor MethodBody
// MethodDeclListOpt -> MethodDeclList | ϵ
// MethodDeclList -> MethodDecl MethodDeclList
// MethodDecl -> Type ID MethodBody | Type [] ID MethodBody
// MethodBody -> ( ParamListOpt ) { StatementsOpt }
// ParamListOpt -> ParamList | ϵ
// ParamList -> Param ParamListTail
// ParamListTail -> , Param ParamListTail | ϵ
// Param -> Type ID ParamRest
// ParamRest -> ϵ | [] ID ParamRest
// StatementsOpt -> Statements | ϵ
// Statements -> Statement StatementsTail
// StatementsTail -> Statement StatementsTail | ϵ
// Statement -> VarDeclList | AtribStat | PrintStat | ReadStat | ReturnStat | SuperStat | IfStat | ForStat | break ; | ;
// AtribStat -> LValue = Expression | LValue = AllocExpression
// PrintStat -> print Expression
// ReadStat -> read LValue
// ReturnStat -> return Expression
// SuperStat -> super ( ArgListOpt )
// IfStat -> if ( Expression ) { Statements } ElseOpt
// ElseOpt -> else { Statements } | ϵ
// ForStat -> for ( AtribStatOpt ; ExpressionOpt ; AtribStatOpt ) { Statements }
// AtribStatOpt -> AtribStat | ϵ
// ExpressionOpt -> Expression | ϵ
// LValue -> ID LValueComp
// LValueComp -> LValueCompTail
// LValueCompTail -> . ID LValueCompTail | [ Expression ] LValueCompTail | ( ArgListOpt ) LValueCompTail | ϵ
// Expression -> NumExpression ExpressionTail
// ExpressionTail -> RelOp NumExpression ExpressionTail | ϵ
// AllocExpression -> new ID ( ArgListOpt ) | Type [ Expression ]
// NumExpression -> Term NumExpressionTail
// NumExpressionTail -> + Term NumExpressionTail | - Term NumExpressionTail | ϵ
// Term -> UnaryExpression TermTail
// TermTail -> * UnaryExpression TermTail | / UnaryExpression TermTail | % UnaryExpression TermTail | ϵ
// UnaryExpression -> + Factor | - Factor | Factor
// Factor -> INTEGER_LITERAL | STRING_LITERAL | LValue | ( Expression )
// ArgListOpt -> ArgList | ϵ
// ArgList -> Expression ArgListTail
// ArgListTail -> , Expression ArgListTail | ϵ
