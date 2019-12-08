#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cmath>

using namespace std;

#define STACK_SIZE 20

//토큰 종류
enum TknKind {
	Print, Lparen, Rparen, Plus, Minus, Multi, Divi, Pow
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
void statement();
void expression();
void term();
void factor();
Token nextTkn();
int nextCh();
void operate(TknKind op);
void push(int n);
int pop();
void chkTkn(TknKind kd);
//double pow(double x, double y);

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
		token = nextTkn(); //최초토큰
		statement();
		if (errF) cout << "--err--\n";
	}

	system("pause");
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
		chkTkn(Assign); if (errF) break;
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

Token nextTkn()                            /* 다음 토큰 */
{
	TknKind kd = Others;
	int  num;

	while (isspace(ch))                    /* 공백 건너뛰기 */
		ch = nextCh();
	if (isdigit(ch)) {                     /* 숫자 */
		for (num = 0; isdigit(ch); ch = nextCh())
			num = num * 10 + (ch - '0');
		return Token(IntNum, num);
	}
	else if (islower(ch)) {                /* 변수 */
		num = ch - 'a';                    /* 변수 번호 0-25 */
		ch = nextCh();
		return Token(VarName, num);
	}
	else {
		switch (ch) {
		case '(':  kd = Lparen; break;
		case ')':  kd = Rparen; break;
		case '+':  kd = Plus;   break;
		case '-':  kd = Minus;  break;
		case '*':  kd = Multi;  break;
		case '^':  kd = Pow;    break;
		case '/':  kd = Divi;   break;
		case '=':  kd = Assign; break;
		case '?':  kd = Print;  break;
		case '\0': kd = EofTkn; break;
		}
		ch = nextCh();
		return Token(kd);
	}
}

int nextCh()                               /* 다음 1문자 */
{
	if (*bufp == '\0') return '\0'; else return *bufp++;
}

void operate(TknKind op)                   /* 연산 실행 */
{
	int d2 = pop(), d1 = pop();

	if (op == Divi && d2 == 0) { cout << "  division by 0\n"; errF = 1; }
	if (errF) return;
	switch (op) {
	case Plus:  push(d1 + d2); break;
	case Minus: push(d1 - d2); break;
	case Multi: push(d1*d2); break;
	case Divi:  push(d1 / d2); break;
	}
}

void push(int n)                           /* 스택 저장 */
{
	if (errF) return;
	if (stack_mm + 1 > STACK_SIZE) { cout << "stack overflow\n"; exit(1); }
	stack[++stack_mm] = n;
}

int pop()                                  /* 스택 추출 */
{
	if (errF) return 1;                    /* 오류 시는 단순히 1을 반환한다 */
	if (stack_mm < 1) { cout << "stack underflow\n"; exit(1); }
	return stack[stack_mm--];
}

void chkTkn(TknKind kd)                    /* 토큰 종인 확인 */
{
	if (token.kind != kd) errF = 1;        /* 불일치 */
}