# BlaanTeam Interpreter

This interpreter is designed to evaluate mathematical expressions and return the result. It supports basic operations such as addition, subtraction, multiplication, and division, as well as more advanced functions will be added soon.


## Grammar

```
    program = block "." ;

    block = [ "const" ident "=" number {"," ident "=" number} ";"]
            { "procedure" ident ";" block ";" } statement ;

    statement = [ ident ":=" expression | "call" ident 
                | "?" ident | "!" expression 
                | "begin" statement {";" statement } "end" 
                | "if" condition "then" statement 
                | "while" condition "do" statement ];

    condition = "odd" expression |
                expression ("=="|"!="|"<"|"<="|">"|">=") expression ;

    expression = [ "+"|"-"] term { ("+"|"-") term};

    term = factor {("*"|"/") factor};

    factor = ident | number | "(" expression ")";

```