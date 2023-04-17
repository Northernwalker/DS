#include"../../../stack/stack.h"

#include <stdio.h>
#include<string.h>

#define N_OPTR 9 //���������

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
	/*              |-------------------- �� ǰ �� �� �� --------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};



void readNumber(char*& p, Stack<float>& stk) { //����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
	stk.push((float)(*p - '0')); //��ǰ��λ��Ӧ����ֵ��ջ
	while (isdigit(*(++p))) //ֻҪ�������н��ڵ����֣�����λ���������������
		stk.push(stk.pop() * 10 + (*p - '0')); //����ԭ��������׷������λ������ֵ������ջ
	if ('.' != *p) return; //�˺��С���㣬����ζ�ŵ�ǰ�������������
	float fraction = 1; //������ζ�Ż���С������
	while (isdigit(*(++p))) //��λ����
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //С������
}

Operator optr2rank(char op) { //�������ת������
	switch (op) {
	case '+': return ADD; //��
	case '-': return SUB; //��
	case '*': return MUL; //��
	case '/': return DIV; //��
	case '^': return POW; //�˔�
	case '!': return FAC; //�׳�
	case '(': return L_P; //������
	case ')': return R_P; //������
	case '\0': return EOE; //��ʼ������ֹ��
	default: exit(-1); //δ֪�����
	}
}

char orderBetween(char op1, char op2) {//�Ƚ����������֮������ȼ�
	return pri[optr2rank(op1)][optr2rank(op2)];
}



float calcu(char optr, float opnd) {//������Ϊ������ʱ������һ�º���
	int result = opnd;
	for (int i = opnd - 1; i > 0; i--) {
		result = result * i;
	}
	return result;
}


float calcu(float opnd1, char op, float opnd2) {
	float result = 1;
	switch (op) //�ж������
	{
	case '+': {
		result = opnd1 + opnd2;
		return result; }
	case '-': {
		result = opnd1 - opnd2;
		return result; }
	case '*': {
		result = opnd1 * opnd2;
		return result; }
	case '/': {
		result = opnd1 / opnd2;
		return result; }
	case '^': {
		for (int i = 0; i < opnd2; i++)
			result *= opnd1;
		return result; }
	}//switch
}

float evaluate(char* S/* char*& RPN*/) { //�ԣ����޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN
	Stack<float> opnd;
	Stack<char> optr; //������ջ�������ջ
	optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
	while (!optr.empty()) { //�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
		if (isdigit(*S)) { //����ǰ�ַ�Ϊ����������
			readNumber(S, opnd);
			//append(RPN, opnd.top()); //��������������������RPNĩβ
		}else //����ǰ�ַ�Ϊ���������
			switch (orderBetween(optr.top(), *S)) {//���䲻ջ�������֮�����ȼ��ߵͷֱ���
			    case '<': //ջ����������ȼ�����ʱ
				    optr.push(*S);
					S++; //�����Ƴ٣���ǰ�������ջ
				    break;
			    case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
				    optr.pop();
					S++; //�����Ų�������һ���ַ�
				    break;
			    case '>': { //ջ����������ȼ�����ʱ����ʵ����Ӧ�ļ��㣬�������������ջ
				    char op = optr.pop(); 
					//append(RPN, op); //ջ���������ջ��������RPNĩβ
				    if ('!' == op) { //������һԪ�����
					    float pOpnd = opnd.pop(); //ֻ��ȡ��һ������������
					    opnd.push(calcu(op, pOpnd)); //ʵ��һԪ���㣬�����ջ
				    }else { //������������Ԫ�������
					    float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //ȡ����ǰ������
					    opnd.push(calcu(pOpnd1, op, pOpnd2)); //ʵ�ֶ�Ԫ���㣬�ᖈ��ջ
				    }
				    break;
			    }
			    default: exit(-1); //���﷨���󣬲�������ֱ���˳�
		    }//switch
	}//while
	return opnd.pop(); //�������������ļ�����
}



int main() {//�ټ�������
	char s1[] = "2.3+3.5";
	cout << "2.3+3.5=" << evaluate(s1) << endl;
	char s2[] = "7.3-3.5";
	cout << "7.3-3.5=" << evaluate(s2) << endl;
	char s3[] = "2*6";
	cout << "2*6=" << evaluate(s3) << endl;
	char s4[] = "8/2";
	cout << "8/2=" << evaluate(s4) << endl;
	char s5[] = "4^6";
	cout << "4^6=" << evaluate(s5) << endl;
	char s6[] = "2!+4!";
	cout << "2!+4!=" << evaluate(s6) << endl;
	char s7[] = "(2.3+3.5)*(7.3-3.5)+2*6^2+8/2+2!+4!";
	cout << "(2.3+3.5)*(7.3-3.5)+2*6^2+8/2+2!+4!=" << evaluate(s7) << endl;

}
