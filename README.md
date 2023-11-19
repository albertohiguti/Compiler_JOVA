# Compiler_X++

## Observações

Caso você esteja usando o editor de código VSCode é possível visualizar esse arquivo README como se estivesse em um navegador, para isso basta clicar no botão "Open Preview" no canto superior direito da tela.

Caso contrário, você pode visualizar esse arquivo README clicando [aqui](https://github.com/albertohiguti/Compiler_Xpp)

Este repositório contém um arquivo chamado teste.xpp que tenta abordar todos os aspectos da linguagem X++. Fique a vontade para utilizá-lo com outros trabalhos.

## Uso

### Compilar

```bash
# Execute o seguinte comando dentro do diretório "compiler"
g++ *.cpp -o xpp_compiler
```

### Executar

```bash
./xpp_compiler teste.xpp
```

### Executar com Debug Mode

O Debug Mode é uma funcionalidade que imprime na tela o que está acontecendo durante a execução do programa. Para ativá-lo, basta adicionar a flag "-d" na hora de executar o programa.

```bash
./xpp_compiler teste.xpp -d
```
## Sobre

### Tratamento de Ambiguidades

Em alguns não terminais da linguagem apresentada, existem ambiguidades não solucionáveis através de um lookahead de um único token. Para resolver esse problema, foi criado um lookAhead de N tokens, que funciona juntamente com o lookahead padrão, onde ele é ativado apenas nos casos de possíveis ambiguidades.

### Gramática sem recursão a esquerda

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

