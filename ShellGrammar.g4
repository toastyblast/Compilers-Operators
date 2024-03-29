grammar ShellGrammar;

sequence
    :   pipeline ( seqDelim pipeline )* lastAmpersand=AMPERSAND? EOF
    ;

seqDelim: ( SEMICOLON | AMPERSAND | X2AMPERSANDCO | X2LINECO);

pipeline
    :   simpleCommand
            ( PIPE simpleCommand )*
    ;

simpleCommand
    :   string+ ioRedirect*
    ;

ioRedirect
    :   REDIRECT string
    |   REDIRECTFD
    ;

string
    :   QUOTEDSTRING
    |   STRING
    ;

SEMICOLON: ';';
AMPERSAND: '&';
//CO - controll operator
X2AMPERSANDCO: '&&';
X2LINECO: '||';
PIPE:      '|';

fragment Digit: [0-9];
REDIRECTFD:  Digit? ('>' | '>>' | '<') ('&' Digit);
REDIRECT:    Digit? ('>' | '>>' | '<');

fragment EscapedQuote:    '\\"';
QUOTEDSTRING: '"' ( EscapedQuote | ~('\n'|'\r') )*? '"';

fragment EscapedSpace:    '\\ ';
fragment StringCharacter:  ~('\n'|'\r'|' '|'\t'|'"'|'|'|'&') | EscapedSpace;
STRING:  StringCharacter+;

WS: [ \r\n\t]+ -> skip;
