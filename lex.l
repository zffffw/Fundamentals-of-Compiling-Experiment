
%{

#include "myyacc.tab.h"  /*对终结符的常量定义*/

/*书上使用该变量yylval，但该变量不是flex自带的，所以补充定义这个变量*/
int yylval;

/*该函数将变量添加到符号表中，尚未实现该功能*/
int installID() ;

/*该函数将数值添加到数值表中，尚未实现该功能*/
int installNum() ;


%}

delim		[\n\t ]
ws		{delim}+
letter		[A-Za-z]
digit		[0-9]
id		{letter}({letter}|{digit})*
number		{digit}+(\.{digit}+)?(E[+-]?{digit}+)?
relop       	<|<=|=|!=|>|>=
addop		"+"|"-"|"*"|"/"
basic		int|char|bool|float
%%

\/\/([^\n])+	{	printf("line comments : %s\n",yytext);}
{ws} {}
\/\*([^\*])*\*([\*]|[^\*\/]([^\*])*[\*])*\/      { printf("Comments:%s\n",yytext); }
"if"		{   return (IF);}
"then"		{   return (THEN);}
"else"      	{   return(ELSE);}
"while"     	{   return(WHILE);}		
"do"        	{   return(DO);}
"break"     	{   return(BREAK);}
"true"    	{   return(TRUE);}
"false"     	{   return(FALSE);}
"int"		{   return(INT);}
"char"		{   return (CHAR);}
"float"		{   return (FLOAT);}
"bool"		{   return (BOOL);}
{id}		{	sscanf( yytext, "%s", &yylval );return (ID);}
{number}	{   sscanf( yytext, "%lf", &yylval);return (NUMBER);}
"<"		{   return(RELOP_LT);}
"="		{   return('=');}
">"		{   return(RELOP_GT);}
"!="        	{   return(RELOP_NE);}
"=="        	{   return(RELOP_EE);}
"<="        	{   return(RELOP_LE);}
">="        	{   return(RELOP_GE);}
"||"		{   return(OR);}
"&&"		{ 	return(AND);}
"+"		{   return ('+');}
"-"         	{   return ('-');}
"*"         	{   return ('*');}
"/"         	{   return ('/');}
","		{	return (',');}
"("		{	return ('(');}
")"		{	return (')');}
";"		{	return (';');}
"{"		{	return ('{');}
"}"		{	return ('}');}
"["		{	return ('[');}
"]"		{	return (']');}
"."		{	return ('.');}
.       {}
%%


/*该函数设置yyin变量，fflex对yyin变量所对应的文件进行词法分析*/
void BeginCompileOneFile( const char * filename )
{  
   yyin = fopen( filename, "r");
   fseek( yyin, 0, SEEK_SET );

}

void EndCompileOneFile(void) 
{
   fclose(yyin);
   yyin = 0;
}

int yywrap()
{
	return 1;
}

int installID() 
{
   return 1;
}

int installNum() 
{
   return 1;
}


/*
#ifdef __cplusplus
    extern "C" int yylex(void);
    extern "C" void BeginCompileOneFile( const char * filename );
    extern "C" void EndCompileOneFile( void);
#endif
*/










