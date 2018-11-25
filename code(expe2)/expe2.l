%{
%}
whitespace [ ]*
filename [A-Za-z.0-9]+
include "#"({whitespace})"include"({whitespace})("<"|"\"")({filename})(">"|"\"")
digit [0-9]
number {digit}+
letter [a-zA-Z]
identifier ({letter}|_)(_|{letter}|{digit})*
delim [\t \n]+
calop "+"|"-"|"*"|"/"
relop	"<"|"<="|"="|">"|">="|"!="|"=="
basic "int"|"char"|"bool"|"float"
%%
{include} {printf("%s\n", yytext);}
"if"  {printf("%s\n", yytext);}
"while"  {printf("%s\n", yytext);}
"do"  {printf("%s\n", yytext);}
"break"  {printf("%s\n", yytext);}
"real"  {printf("%s\n", yytext);}
"true"  {printf("%s\n", yytext);}
"false"  {printf("%s\n", yytext);}
"("  {printf("%s\n", yytext);}
")"  {printf("%s\n", yytext);}
"{"  {printf("%s\n", yytext);}
"}"  {printf("%s\n", yytext);}
"["  {printf("%s\n", yytext);}
"]"  {printf("%s\n", yytext);}
","  {printf("%s\n", yytext);}
";"  {printf("%s\n", yytext);}
"!"  {printf("%s\n", yytext);}
"//"[^\n]*      {/*跳过注释*/}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {/*跳过注释*/} 
"return" {printf("%s\n", yytext);}
{basic} {printf("%s\n", yytext);}
{calop} {printf("%s\n", yytext);}
{relop} {printf("%s\n", yytext);}
{number}	{printf("(%s,%s)\n", "NUM", yytext);}
{identifier}	{printf("(%s,%s)\n", "ID", yytext);}
{delim}	{/*跳过空白*/}

%%

int main(int argc, char* argv[]) {
    ++argv,--argc;
    if(argc>0)
        yyin=fopen(argv[0],"r");
    else
        yyin=stdin;
    ++argv,--argc;
    if(argc>0)
        yyout=fopen(argv[0],"w");
    else
        yyout=stdout;
    yylex();
}

int yywrap()
{
    return 1;
}
