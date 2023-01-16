# BlaanTeam Interpreter

This interpreter is designed to evaluate mathematical expressions and return the result. It supports basic operations such as addition, subtraction, multiplication, and division, as well as more advanced functions will be added soon.


## Grammar

```
    program = block

    block = "let" ident "=" expression {"," ident "=" expression}
            | ident "lambda" args ":" expression
            | ident "(" {args} ")"
            | condition ? expression: expression;
    
    args = ident {"," ident}

    condition = expression
                | expression ("=="|"!="|"<"|"<="|">"|">=") expression 

    expression = ("+"|"-") term { ("+"|"-") term };

    term = factor {("*"|"/"|"^") factor};

    factor = ident | number | "(" expression ")";

```