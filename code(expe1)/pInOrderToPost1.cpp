/*�����ܣ�����׺���ʽת��Ϊ��׺���ʽ�ķ�����
  �������룺��������(0~9)�Լ�'+'��'-"���ɵ���׺���ʽ
            Ϊ�˼򻯳�������Դʷ��������ܣ�����Ҫ����ʽ�в����пո�ȷָ�����
			����: �ڼ���������9-5+2
  ԭʼ�ķ�������
           expr --> expr + term
                  | expr - term
                  | term
           term --> 0
                  | 1
                  | 2
	              ......
                  | 9

  ������ݹ����﷨�Ƶ��ķ��뷽����
            expr --> term  rest 

            rest --> + term {print('+')} rest
                   | - term {print('-')} rest
   		           | ��

            term --> 0  {print('0')}
                   | 1  {print('1')}
                   | 2  {print('2')}
		              ......
                   | 9  {print('9')} 
*/
#include <stdio.h>
#include <stdlib.h>

char LookAhead;

void Match(char t)
{
	if( LookAhead==t ) 
		LookAhead = getchar(); //������ǰ����һ���ַ�
    else {
		printf("\n���ʽ����Match��������Ҫ������ַ�Ϊ%c������ʵ���������%c\n", t, LookAhead );
		exit(1); //��������
	}

}

void Term()
{char t;
	if( LookAhead>='0' && LookAhead<='9' ) {
		t = LookAhead; Match(t); printf("%c",t);
	}
    else {
		printf("\n���ʽ����Term��������Ҫ���������ַ��������������%c\n", LookAhead );
		exit(1); //��������
	}
}

void Rest()
{
	switch( LookAhead ) {
	    case '+':
			Match('+'); Term(); putchar('+'); Rest(); // rest --> + term {print('+')} rest
			break;
		case '-':
			Match('-'); Term(); putchar('-'); Rest(); // rest --> - term {print('-')} rest
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
	LookAhead = getchar();

	printf("���׺���ʽΪ��");
	Expr();
    
	if( LookAhead !='\n' ) {
	    //���磺3+45
		printf("\n����ı��ʽ���󣬴�����ַ���%c\n", LookAhead);
		exit(1);
	}

	printf("\n���ʽ�����ɹ���\n");
	
	return 0;
}
