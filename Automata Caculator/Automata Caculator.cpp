#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

#define STACK_SIZE 20

//��ū ����
enum TknKind {
	print, Lparen, Rparen, Plus, Minus, Multi, Divi, Pow
	,Assign, VarName, IntNum, EofTkn, Others 
};

struct Token
{
	TknKind kind; //������ ������ ����ü�� ����
	int intVal; //������̳� ���� ��ȣ�� �����ϴ� ����
	
	Token() //�⺻ ������
	{
		kind = Others;
		intVal = 0;
	}

	Token(TknKind k, int d = 0) //�Ű������� �ִ� ������
	{
		kind = k;
		int val = d;
	}
};

void input();

int errF;
int stack[STACK_SIZE+1]; //�迭���� 0�� �ƴ� 1���� �����ϱ� ����
int stack_mm; //���� ����
Token token; //��ū���� �����ϱ� ���� ����
char buf[80], *bufp; //�Է¹���
int ch; //������ ���ڸ� ����
int var[26]; //���� a-z
int errF; //�����߻�

int main(void)
{
	while (1)
	{
		input(); //�Է�
		token = nextTKN(); //������ū
		statement();
		if (errF) cout << "--err--\n";
	}

	return 0;
}

void input()
{
	errF = 0;
	stack_mm = 0;
	cin.getline(buf, 80);
	bufp = buf;
	ch = nextCh();

}

void statement()
{
	int vNbr;

	switch (token.kind)
	{
	case VarName:
		vNbr = token.intVal;
		token = nextTkn();
		chkTkn(assign); if (errF) break;
		token = nextTkn();
		expression();
		var[vNbr] = pop();
		break;
	case Print:
		token = nextTkn();
		expression();
		chkTkn(EofTkn); if (errF) break;
		cout << "" << pop() << endl;
		return;
	default:
		errF = 1;
	}
	chkTkn(EofTkn);
}

void expression()
{
	TknKind op;

	term();
	while (token.kind==Plus || token.kind==Minus)
	{
		op = token.kind;
		token = nextTkn();
		term();
		operate(op);
	}
}

void term()
{
	TknKind op;
	
	factor();
	while (token.kind == Multi || token.kind == Divi)
	{
		op = token.kind;
		token = nextTkn();
		factor();
		operate(op);
	}
}

void factor()
{
	switch (token.kind)
	{
	case VarName:
		push(var[token.intVal]);
		break;
	case IntNum:
		push(token.intVal);
		break;
	case Lparen:
		token = nextTkn();
		expression();
		chkTkn(Rparen);
		break;
	default:
		errF = 1;
	}
	token = nextTkn();
}

Token nextTkn()
{
	TknKind kd = Others;
	int num;
}