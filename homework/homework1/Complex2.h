#include<iostream>
#include<math.h>
using namespace std;

class complex
{
public:
	complex() { real = rand() % 10; imag = rand() % 10; model = real * real + imag * imag;} //有参和无参的构造函数
	double getreal() { return real; }//返回实部
	double getimag() { return imag; }//返回虚部
	double getmodel() {
		model = sqrt(model);
		return model;
	}
	void givereal(double i) {real = i;}
	void giveimag(double i) { imag = i; }
	void display() {
		cout << "(" << real << "," << imag << "i) " ;
	}
	bool operator>(complex& c)const
	{
		if (real > c.real)
			return true;
		else if (real == c.real)
		{
			if (imag > c.imag)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	bool operator<(complex& c)const
	{
		if (real < c.real)
		{
			return true;
		}
		else if (real == c.real)
		{
			if (imag < c.imag)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	bool operator>=(complex& c)const
	{
		if (*this < c)
			return false;
		else
			return true;
	}
	bool operator<=(complex& c)const
	{
		if (*this > c)
			return false;
		else
			return true;
	}
	bool operator==(complex& c)const
	{
		if ((*this > c) || (*this < c))
			return false;
		else
			return true;
	}
	bool operator!=(complex& c)
	{
		if (*this == c)
			return false;
		else
			return true;
	}
	complex operator++(int)//后置加加
	{
		complex temp = *this;
		real++;
		return temp;

	}
	complex& operator++()//前置加加
	{
		real++;
		return *this;
	}
	complex& operator+=(double x)
	{
		real += x;
		return (complex&)*this;
	}
private:
	double real;
	double imag;
	double model;
};
