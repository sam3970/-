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

int main(void)
{
	while (1)
	{
		input();
	}

	return 0;
}

void input()
{
	errF = 0;
	stack_mm = 0;

}