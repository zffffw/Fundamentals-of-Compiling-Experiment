/*程序功能：将中缀表达式转换为后缀表达式的翻译器
  程序输入：常数、变量以及'+'和'-"构成的中缀表达式
            程序使用词法分析功能。
			例如: 在键盘上输入90-abc+23
  原始文法描述：
           expr --> expr + term
                  | expr - term
                  | term
 
           term --> term * factor
                  | term / factor
                  | factor
           factor --> ( expr )
                  | ID
                  | NUM
  消除左递归后的语法制导的翻译方案：
            expr --> term  rest_expr

            rest_expr --> + term {print('+')} rest_expr
                   | - term {print('-')} rest_expr
   		             | 空

            term --> factor rest_term
 
            rest_term --> * factor {print('*')} rest_term
                     | / factor {print('/')} rest_term
                     | 空
            factor --> ( {print('(')}  expr  ) {print(')')}
            | ID {print('lexeme')}
            | NUM {print('tokenval')}
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TOKEN_NUM 500
#define TOKEN_ID 600
void Rest_Term();
void Rest_Expr();
void Expr();
void Term();
void Factor();


int LookAhead; //存放词法单元类型
int lineno = 1;
int tokenval = 0;
char lexeme[1024];

//判断是否是限定的几个符号 + - * / ( ) 空格 换行
bool isSymbol(int t) {
    char symbols[8] = "+-*/() ";
    int i = 0;
    bool flag = false;
    while(symbols[i]) {
        if (symbols[i] == t) {
            flag = true;
            break;
        }
        ++i;
    }
    return flag;
}

int GetToken()
{
	int t, i;
	while (1) {
		t = getchar();
		if (t == ' ' || t == '\t') 
			continue;
		else if (isdigit(t)) {
			tokenval = 0;
			do {
				tokenval = tokenval * 10 + t -'0';
				t = getchar();
			} while (isdigit(t));
			ungetc(t, stdin);
			return TOKEN_NUM;
		}
        else if( isalpha(t) ) {
            i=0; 
            do {
                lexeme[i++]=t; t = getchar(); 
            }while( isalpha(t) || isdigit(t) );
            lexeme[i]='\0'; ungetc(t, stdin);
            return TOKEN_ID;
        }
        else if (!isSymbol(t) && t != '\n') {
            printf("\n输入的符号错误，出现了除 + - * / 外的特殊符号%c, 超出\"编译器\"的能力\n", t);
            exit(1);
        }
		else {
			tokenval = 0;
			return t;//例如t=’+’，则把’+’的ASCII作为’+’的TokenName。
		}
	}
}

void Match(int t)
{
	if( LookAhead==t ) 
		LookAhead = GetToken(); //继续往前看后一个词法单元
    else {
		printf("\n表达式错误：不匹配\"%c\"\n", t); 
		exit(1); //结束程序
	}
}

void Factor() {
    if ( LookAhead == '(') { //判断括号表达式
        printf("(");
        Match('(');
        Expr();
        Match(')');
        printf(")");
    }
    else if( LookAhead==TOKEN_NUM) {
		printf("%d ",tokenval); 
        Match(LookAhead); 
	}
	else if( LookAhead==TOKEN_ID) {
		printf("%s ",lexeme); 
        Match(LookAhead);
	}
    else {
        if(LookAhead == '\n') {
            printf("\n表达式不完整，例如*后面没有factor项\n");
        } else {
		    printf("\n表达式错误：Factor函数中需要输入整数或变量, 而现在出现的是\"%c\"\n", LookAhead);
        }
		exit(1); //结束程序
	}
}

void Term() {
    Factor();
    Rest_Term();
}

void Rest_Term() {
    switch( LookAhead ) {
	    case '*':
			Match('*'); Factor();printf("* "); Rest_Term(); // term --> * factor {print('* ')} rest_term
			break;
		case '/':
			Match('/'); Factor(); printf("/ "); Rest_Term(); // term --> / factor {print('/ ')} rest_trem
			break;
		default:   // rest_term --> 空
			break;
	}
}



void Rest_Expr() {
    switch( LookAhead ) {
	    case '+':
			Match('+'); Term();printf("+ "); Rest_Expr(); // rest --> + term {print('+')} rest_expr
			break;
		case '-':
			Match('-'); Term(); printf("- "); Rest_Expr(); // rest --> - term {print('-')} rest_expr
			break;
		default:   // rest_expr --> 空
			break;
	}
}



void Expr() {
    Term();
    Rest_Expr();
}


int main() {
    printf("请输入中缀表达式：");
	LookAhead = GetToken();

	printf("其后缀表达式为：");
	Expr();
    
	if( LookAhead !='\n' ) {
		printf("\n输入的表达式错误.\n");
		exit(1);
	}

	printf("\n表达式分析成功！\n");
	// system("pause");
	return 0;
}