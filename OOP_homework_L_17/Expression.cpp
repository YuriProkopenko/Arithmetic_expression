#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>
#include "Expression.h"
using namespace std;

void Expression::Plus(stack<char>& symbols, stack<double>& numbers) {
	double temp_numb_two = numbers.top();
	numbers.pop();
	double temp_numb_one = numbers.top();
	numbers.pop();
	numbers.push(temp_numb_one + temp_numb_two);
	symbols.pop();
}

void Expression::Minus(stack<char>& symbols, stack<double>& numbers) {
	double temp_numb_two = numbers.top();
	numbers.pop();
	double temp_numb_one = numbers.top();
	numbers.pop();
	numbers.push(temp_numb_one - temp_numb_two);
	symbols.pop();
}

void Expression::Multy(stack<char>& symbols, stack<double>& numbers) {
	double temp_numb_two = numbers.top();
	numbers.pop();
	double temp_numb_one = numbers.top();
	numbers.pop();
	numbers.push(temp_numb_one * temp_numb_two);
	symbols.pop();
}

void Expression::Divis(stack<char>& symbols, stack<double>& numbers) {
	double temp_numb_two = numbers.top();
	numbers.pop();
	double temp_numb_one = numbers.top();
	numbers.pop();
	numbers.push(temp_numb_one / temp_numb_two);
	symbols.pop();
}

void Expression::Degree(stack<char>& symbols, stack<double>& numbers) {
	int temp_numb_two = numbers.top();
	numbers.pop();
	int temp_numb_one = numbers.top();
	numbers.pop();
	numbers.push(pow(temp_numb_one, temp_numb_two));
	symbols.pop();
}

bool Expression::Is_main_Symb(stack<char> symbols) {
	if (symbols.top() == '*' || symbols.top() == '/' || symbols.top() == '^')
		return true;
	else
		return false;
}

bool Expression::Is_main_Exp(char symb) {
	if (symb == '*' || symb == '/' || symb == '^')
		return true;
	else 
		return false;
}

double Expression::CheckNum(int pos) {
	double result;
	string number;
	stringstream s_number;
	while (example[pos] >= 48 && example[pos] <= 57 || example[pos] == '.') {
		number += example[pos];
		pos++;
	}
	s_number << number;
	s_number >> result;
	return result;
}

bool Expression::CheckExpression() {
	try {
		string symbols("+-*/^");
		string sym_without_min("+*/^");
		string numbers("0123456789");
		int check = 0;
		int count_open = 0;
		int count_close = 0;
		int len = this->example.length();
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < symbols.length(); j++) 
				if (example[i] == symbols[j] || example[i] == '(' || example[i] == ')' || example[i] == '.')
					check++;
			for (int j = 0; j <numbers.length(); j++)
				if (example[i] == numbers[j])
					check++;
			if (check == 0)
				throw 1;
			check = 0;
			for (int j = 0; j < symbols.length(); j++) {
				if (example[i] == symbols[j])
					for (int k = 0; k < symbols.length(); k++)
						if (example[i + 1] == symbols[k])
							throw 2;
			}
			if (example[i] == '.' && example[i + 1] == '.')
				throw 3;
			for (int j = 0; j < numbers.length(); j++) {
				if (example[i] == numbers[j] && example[i + 1] == '(')
					throw 4;
			}
			if (example[i] == ')')
				for (int j = 0; j < numbers.length(); j++) {
					if (example[i + 1] == numbers[j])
						throw 5;
				}
			if (example[i] == '(' && example[i + 1] == ')')
				throw 6;
			if (example[i] == '(')
				for (int j = 0; j < sym_without_min.length(); j++) {
					if (example[i + 1] == sym_without_min[j])
						throw 7;
				}
			for (int j = 0; j < symbols.length(); j++)
				if (example[i] == symbols[j] && example[i + 1] == ')')
					throw 8;
			if (example[i] == ')' && example[i + 1] == '(')
				throw 9;
			if (example[i] == '.') {
				for (int j = 0; j < symbols.length(); j++)
					if (example[i + 1] == symbols[j] || example[i - 1] == symbols[j])
						throw 10;
				for (int j = 0; j < numbers.length(); j++) {
					if (example[i - 1] == numbers[j])
						check++;
				}
				if (check == 0)
					throw 10;
			}
			if (example[i] == '(')
				count_open++;
			if (example[i] == ')')
				count_close++;
		}
		if ( count_open != count_close)
			throw 11;
	}
	catch (int error)
	{
		if (error == 1) {
			cout << "\nIncorrect symbol in expression!";
			return false;
		}
		if (error == 2) {
			cout << "\nTwo binary characters together in a row!";
			return false;
		}
		if (error == 3) {
			cout << "\nTwo decimal points together in a row!";
			return false;
		}
		if (error == 4) {
			cout << "\nMissing expression before opening parenthesis!";
			return false;
		}
		if (error == 5) {
			cout << "\nMissing expression after closing parenthesis!";
			return false;
		}
		if (error == 6) {
			cout << "\nMissing expression between parenthesis!";
			return false;
		}
		if (error == 7) {
			cout << "\nBinary character after opening parenthesis!";
			return false;
		}
		if (error == 8) {
			cout << "\nBinary character before closing parenthesis!";
			return false;
		}
		if (error == 9) {
			cout << "\nMissing expression between parenthesis!";
			return false;
		}
		if (error == 10) {
			cout << "\nIncorrect decimal point location!";
			return false;
		}
		if (error == 11) {
			cout << "\nIncorrect count of parenthesis!";
			return false;
		}
	}
	return true;
}

double Expression::Computation(const string& examp) {
	example.insert(1, examp);
	if (!CheckExpression())
		return 0;
	double num;
	stack<char> symbols;
	stack<double> numbers;
	int len = this->example.length();
	for (int i = 0; i < len; i++) {
		if (example[i] == ')') {
			while (symbols.top() != '(') {
				if (symbols.top() == '*') {
					Multy(symbols, numbers);
				}
				if (symbols.top() == '/') {
					Divis(symbols, numbers);
				}
				if (symbols.top() == '^') {
					Degree(symbols, numbers);
				}
				if (symbols.top() == '+') {
					Plus(symbols, numbers);
				}
				if (symbols.top() == '-') {
					Minus(symbols, numbers);
				}
			}
			symbols.pop();
			continue;
		}
		if (example[i] >= 48 && example[i] <= 57 && example[i - 1] >= 48 && example[i - 1] <= 57 ||
			example[i] >= 48 && example[i] <= 57 && example[i - 1] == '.' || 
			example[i] == '.' && example[i - 1] >= 48 && example[i - 1] <= 57) {
			continue;
		}
		if (example[i] >= 48 && example[i] <= 57) {
			num = CheckNum(i);
			numbers.push(num);
			continue;
		}
		if (example[i] == '+' && symbols.top() == '(' || example[i] == '-' && symbols.top() == '(' || example[i] == '(' || example[i] == '^') {
			symbols.push(example[i]);
			continue;
		}
		if (Is_main_Exp(example[i]) && !Is_main_Symb(symbols)) {
			symbols.push(example[i]);
			continue;
		}
		if (!Is_main_Exp(example[i]) && symbols.top() == '+') {
			Plus(symbols, numbers);
			symbols.push(example[i]);
			continue;
		}
		if (!Is_main_Exp(example[i]) && symbols.top() == '-') {
			Minus(symbols, numbers);
			symbols.push(example[i]);
			continue;
		}
		if (symbols.top() == '*') {
			Multy(symbols, numbers);
			if (symbols.top() == '+') {
				Plus(symbols, numbers);
				symbols.push(example[i]);
			}
			else if (symbols.top() == '-') {
				Minus(symbols, numbers);
				symbols.push(example[i]);
			}
			else
				symbols.push(example[i]);
			continue;
		}
		if (symbols.top() == '/') {
			Divis(symbols, numbers);
			if (symbols.top() == '+') {
				Plus(symbols, numbers);
				symbols.push(example[i]);
			}
			else if (symbols.top() == '-') {
				Minus(symbols, numbers);
				symbols.push(example[i]);
			}
			else
				symbols.push(example[i]);
			continue;
		}
		if (symbols.top() == '^') {
			Degree(symbols, numbers);
			if (symbols.top() == '+') {
				Plus(symbols, numbers);
				symbols.push(example[i]);
			}
			else if (symbols.top() == '-') {
				Minus(symbols, numbers);
				symbols.push(example[i]);
			}
			else
				symbols.push(example[i]);
			continue;
		}
	}
	return numbers.top();
}