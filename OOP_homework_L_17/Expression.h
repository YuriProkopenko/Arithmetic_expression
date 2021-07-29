#pragma once
#include <stack>
using namespace std;

class Expression {
	string example;
	bool Is_main_Symb(stack<char> symbols);
	bool Is_main_Exp(char symb);
	void Plus(stack<char>& symbols, stack<double>& numbers);
	void Minus(stack<char>& symbols, stack<double>& numbers);
	void Multy(stack<char>& symbols, stack<double>& numbers);
	void Divis(stack<char>& symbols, stack<double>& numbers);
	void Degree(stack<char>& symbols, stack<double>& numbers);
	bool CheckExpression();
	double CheckNum(int pos);
public:
	Expression() : example("()") {}
	Expression(const string& example) : example(example) {}
	double Computation(const string& example);
};
