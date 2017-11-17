grammar Instant;

program
    : stmt ( ';' stmt )* ( ';' )?
    ;

stmt
    : IDENT '=' expr               # AssignExpr
    | expr                         # SExpr
    ;

expr
    : expr '/' expr                # DivExpr
    | expr '*' expr                # MulExpr
    | expr '-' expr                # SubExpr
    | <assoc=right> expr '+' expr  # AddExpr
    | IDENT                        # VarExpr
    | INT                          # ConstExpr
    | '(' expr ')'                 # ParensExpr
    ;

fragment Letter  : Capital | Small ;
fragment Capital : [A-Z\u00C0-\u00D6\u00D8-\u00DE] ;
fragment Small   : [a-z\u00DF-\u00F6\u00F8-\u00FF] ;
fragment Digit : [0-9] ;

INT : Digit+ ;
fragment ID_First : Letter | '_';
IDENT : ID_First (ID_First | Digit)* ;

WS : (' ' | '\r' | '\t' | '\n')+ ->  skip;
