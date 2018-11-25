/*�����ܣ�����׺���ʽת��Ϊ��׺���ʽ�ķ�����
  �������룺�����������Լ�'+'��'-"���ɵ���׺���ʽ
            ����ʹ�ôʷ��������ܡ�
			����: �ڼ���������90-abc+23
  ԭʼ�ķ�������
           expr --> expr + term
                  | expr - term
                  | term
           term --> num | ID

  ������ݹ����﷨�Ƶ��ķ��뷽����
            expr --> term  rest 

            rest --> + term {print('+')} rest
                   | - term {print('-')} rest
   		             | ��

            term --> num  {print(tokenval)}
                   | ID   {print(lexeme)}
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TKN_NUM  500
#define TKN_ID   600

int lineno = 1;
int LookAhead; //��ŵ�ǰ�Ĵʷ���Ԫ������
int tokenval = 0; char lexeme[1024];

int GetToken()
{
	int t, i;
	while (1) {
		t = getchar();
		if (t == ' ' || t == '\t') 
			;
		//else if (t == '\n')  //��Ϊ�ڸó����У��س�����Ϊ���ʽ�Ľ��������Բ��ܰѻس������ɿհ׷�
			//lineno++;
		else if (isdigit(t)) {
			tokenval = 0;
			do {
				tokenval = tokenval * 10 + t -'0';
				t = getchar();
			} while (isdigit(t));
			ungetc(t, stdin);
			return TKN_NUM;
		}
        else if( isalpha(t) ) {
            i=0; 
            do {
                lexeme[i++]=t; t = getchar(); 
            }while( isalpha(t) || isdigit(t) );
            lexeme[i]='\0'; ungetc(t, stdin);
            return TKN_ID;
        }
		else {
			tokenval = 0;
			return t;//����t=��+������ѡ�+����ASCII��Ϊ��+����TokenName��
		}
	}
}

void Match(int t)
{
	if( LookAhead==t ) 
		LookAhead = GetToken(); //������ǰ����һ���ʷ���Ԫ
    else {
		printf("\n���ʽ����\n"); 
		exit(1); //��������
	}

}

void Term()
{
	if( LookAhead==TKN_NUM) {
		printf("%d ",tokenval); Match(LookAhead); 
	}
	else if( LookAhead==TKN_ID) {
		printf("%s ",lexeme); Match(LookAhead);
	}
    else {
		printf("\n���ʽ����Term��������Ҫ�������������\n" );
		exit(1); //��������
	}
}

void Rest()
{
	switch( LookAhead ) {
	    case '+':
			Match('+'); Term();printf("+ "); Rest(); // rest --> + term {print('+')} rest
			break;
		case '-':
			Match('-'); Term(); printf("- "); Rest(); // rest --> - term {print('-')} rest
			break;
		default:   // rest --> ��
			break;
	}
}

void Expr()
{
    Term();
	Rest();
}

int main()
{
	printf("��������׺���ʽ��");
	LookAhead = GetToken();

	printf("���׺���ʽΪ��");
	Expr();
    
	if( LookAhead !='\n' ) {
		printf("\n����ı��ʽ����.\n");
		exit(1);
	}

	printf("\n���ʽ�����ɹ���\n");
	system("pause");
	return 0;
}
