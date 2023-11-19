# Compiler_X++

## Installation

## Use

### Compile

```bash
# inside the scanner folder
g++ principal.cpp scanner.cpp -o compiler
```

### Run

```bash
./compiler teste.mj
```
## Gramática sem recursão a esquerda

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


## Authors

|  [<img src="https://github.com/edu010101.png?size=460&u=071f7791bb03f8e102d835bdb9c2f0d3d24e8a34&v=4" width=115><br><sub>Eduardo Lopes</sub>](https://github.com/edu010101) |  [<img src="https://github.com/albertohiguti.png?size=460&u=071f7791bb03f8e102d835bdb9c2f0d3d24e8a34&v=4" width=115><br><sub>Alberto Higuti</sub>](https://github.com/albertohiguti) 
| :---: | :---: |

## License
The [MIT License]() (MIT)

Copyright :copyright: 2023 - JOVA

