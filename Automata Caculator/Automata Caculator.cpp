#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

#define STACK_SIZE 20

//토큰 종류
enum TknKind {
	print, Lparen, Rparen, Plus, Minus, Multi, Divi, Pow
	,Assign, VarName, IntNum, EofTkn, Others 
};

struct Token
{
	TknKind kind; //열거형 변수를 구조체에 선언
	int intVal; //상수값이나 변수 번호를 지정하는 변수
	
	Token() //기본 생성자
	{
		kind = Others;
		intVal = 0;
	}

	Token(TknKind k, int d = 0) //매개변수가 있는 생성자
	{
		kind = k;
		int val = d;
	}
};

void input();

int errF;
int stack[STACK_SIZE+1]; //배열값이 0이 아닌 1부터 시작하기 위함
int stack_mm; //스택 관리
Token token; //토큰값을 저장하기 위한 변수
char buf[80], *bufp; //입력버퍼
int ch; //가져온 문자를 저장
int var[26]; //변수 a-z
int errF; //오류발생

int main(void)
{
	while (1)
	{
		input(); //입력
		token = nextTKN(); //최초토큰
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