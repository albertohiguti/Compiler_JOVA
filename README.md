# Compiler_JOVA

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


## Authors

|  [<img src="https://github.com/edu010101.png?size=460&u=071f7791bb03f8e102d835bdb9c2f0d3d24e8a34&v=4" width=115><br><sub>Eduardo Lopes</sub>](https://github.com/edu010101) |  [<img src="https://github.com/albertohiguti.png?size=460&u=071f7791bb03f8e102d835bdb9c2f0d3d24e8a34&v=4" width=115><br><sub>Alberto Higuti</sub>](https://github.com/albertohiguti) 
| :---: | :---: |

## License
The [MIT License]() (MIT)

Copyright :copyright: 2023 - JOVA

