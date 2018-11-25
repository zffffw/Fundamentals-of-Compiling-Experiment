#include "lex.yy.c"
#include "myyacc.tab.h"

int lookahead;

void type();
void Block();
void stmt();
void term();
void restExpr();

void expr();
void match(int TokenID)
{
    if( lookahead == TokenID ) 
	{
		// if(lookahead >= 258 ) {
		// 	printf("*%d\n", lookahead);
		// } else {
		// 	printf("*%c\n", lookahead);
		// }
		lookahead = yylex();
	}
	else 
	{
        printf("error\n");
	}
}

void factor() {
	if(lookahead == '(') {
		match('(');
		printf("factor -> ( expr ) \n");
		expr();
		match(')');
	} else if (lookahead == ID) {
		match(ID);
		printf("factor -> ID\n");
	} else if (lookahead == NUMBER) {
		match(NUMBER);
		printf("factor -> NUM\n");
	}

}

void restTerm() {
	if(lookahead == '*') {
		match('*');
		printf("restTerm ->  * factor\n");
		term();
		restTerm();
	} else if(lookahead == '/') {
		match('/');
		printf("restTerm ->  / factor\n");
		term();
		restTerm();
	} else if(lookahead == '+' || lookahead == '-' || lookahead == ')' || lookahead == ';' || lookahead == ID || lookahead == NUMBER || lookahead == RELOP_E || lookahead == RELOP_GE || lookahead == RELOP_GT || lookahead == RELOP_LE || lookahead == RELOP_LT) {
		printf("restTerm -> ε\n");
	}
}
void restExpr() {
	if(lookahead == '+') {
		match('+');
		printf("restExpr ->  + term\n");
		term();
		restExpr();
	} else if(lookahead == '-') {
		match('-');
		printf("restExpr ->  - term\n");
		term();
		restExpr();
	} else if(lookahead == ';' || lookahead == ')' || lookahead == RELOP_E || lookahead == RELOP_GE || lookahead == RELOP_GT || lookahead == RELOP_LE || lookahead == RELOP_LT) {
		printf("restExpr -> ε\n");
	}
}

void term() {
	printf("term -> factor restTerm\n");
	factor();
	restTerm();
}

void expr() {
	printf("expr -> term restExpr\n");
	term();
	restExpr();
}

void relop() {
	if (lookahead == RELOP_LT) {
		match(RELOP_LT);
		printf("relop ->  < expr\n");
		expr();
	} else if (lookahead == RELOP_LE) {
		match(RELOP_LE);
		printf("relop ->  <= expr\n");
		expr();
	} else if (lookahead == RELOP_GT) {
		match(RELOP_GT);
		printf("relop ->  > expr\n");
		expr();
	} else if (lookahead == RELOP_GE) {
		match(RELOP_GE);
		printf("relop ->  >= expr\n");
		expr();
	} else if (lookahead == RELOP_EE) {
		match(RELOP_EE);
		printf("relop ->  >= expr\n");
		expr();
	} else if (lookahead == '+' || lookahead == '-' || lookahead == ';' || lookahead == ')') {
		printf("relop -> ε\n");
	} 
}

void _bool() {
	printf("bool -> expr relop\n");
	expr();
	relop();
}

void B() {
	if (lookahead == ELSE) {
		match(ELSE);
		printf("B ->  else stmt\n");
		stmt();
	} else if (lookahead == ID || lookahead == '}' || lookahead == IF || lookahead == WHILE || lookahead == DO || lookahead == BREAK || lookahead == '{') {
		printf("B -> ε\n");
	}

}

void stmt()
{
	if(lookahead == ID) {
		match(ID);
		printf("stmt ->  ID  = expr; \n");
		match('=');
		expr();
		match(';');
	} else if(lookahead == IF) {
		match(IF);
		printf("stmt -> if (bool) stmt B\n");
		match('(');
		_bool();
		match(')');
		stmt();
		B();
	} else if(lookahead == WHILE) {
		match(WHILE);
		printf("stmt ->  while (bool) stmt \n");
		match('(');
		_bool();
		match(')');
		stmt();

	} else if (lookahead == DO) {
		match(DO);
		printf("stmt -> do stmt while (bool) ; \n");
		stmt();
		match(WHILE);
		match('(');
		_bool();
		match(')');
		match(';');
	} else if(lookahead == BREAK) {
		printf("stmt -> break;\n");
		match(BREAK);
		match(';');
	} else if (lookahead == '{') {
		printf("stmt -> block\n");
		Block();
	}
}

void stmts() {
	if (lookahead == ID || lookahead == IF || lookahead == WHILE || lookahead == DO || lookahead == BREAK || lookahead == '{') {
		printf("stmts -> stmt stmts\n");
		stmt();
		stmts();
	} else if (lookahead == '}'){
		printf("stmts -> ε\n");
	}
}

void decl() {
	printf("decl -> type id;\n");
	type();
	match(ID);
	match(';');
}

void type() {
	if(lookahead == INT) {
		match(INT);
		printf("type -> int\n");
	} else if (lookahead == FLOAT) {
		match(FLOAT);
		printf("type -> float\n");
	} else if (lookahead == CHAR) {
		match(CHAR);
		printf("type -> char\n");
	} else {
		printf("error type\n");
	}
}

void decls()
{
	if(lookahead == INT || lookahead == FLOAT || lookahead == CHAR) {
		printf("decls -> decl decls\n");
		decl();
		decls();
	} else if (lookahead == ID || lookahead == IF || lookahead == WHILE || lookahead == DO || lookahead == BREAK || lookahead == '{' || lookahead == '}') {
		printf("decls -> ε\n");
	} else {
		printf("error decls\n");
	}
}
void Block()
{
	printf("Block -> { decls stmts }\n");
   	match('{');
   	decls();
	stmts();
   	match('}');
}

void Program()
{
	printf("Program -> Block\n");
	Block();
}

int main()
{ 
	char filename[1000];
	printf("请输入要编译的源程序文件名："); 
	gets(filename);
	BeginCompileOneFile( filename );
	//当flex扫描到文件末尾，yylex函数返回0
    lookahead = yylex();

	Program();
	printf("ok\n");
	EndCompileOneFile();

	getchar();
	
	return 0;
}
