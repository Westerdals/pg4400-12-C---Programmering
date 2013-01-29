#include <iostream>
#include <string>
#include "Number.h"

using namespace std;

Number calculator;

Number::Number()
{
	int num = 0;
}

Number::Number(int num)
{
	value = num;
}

Number Number::operator+(const Number num1) const 
{
	return calculator.sum(value, num1);
}

Number Number::operator-(const Number num1) const 
{
	return calculator.sub(value, num1);
}

Number Number::operator/(const Number num1) const 
{
	return calculator.divi(value, num1);
}

Number Number::operator*(const Number num1) const 
{
	return calculator.mult(value, num1);
}

/*int Calculator::Calculate(int num1, int num2, string sign)
{
	int result = 0;
	if(sign == "+")
	{
		result = calc.sum(num1, num2);
	}

	else if(sign == "-")
	{
		result = calc.sub(num1, num2);
	}

	else if(sign == "*")
	{
		result = calc.mult(num1, num2);
	}

	else if(sign == "/")
	{
		result = calc.divi(num1, num2);
	}

	return result;
}*/

int Number::sum(Number num1, Number num2){
	return num1.value + num2.value;
}

int Number::sub(Number num1, Number num2){
	return num1.value - num2.value;
}

int Number::mult(Number num1, Number num2){
	return num1.value * num2.value;
}

int Number::divi(Number num1, Number num2){
	return num1.value / num2.value;
}