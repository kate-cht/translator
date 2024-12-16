#pragma once
#include "term.h"
#include <string>
#include "mStack.h"
#include <iostream>
using namespace std;

class translator 
{
private:
	map<types, size_t> states{ { operand_, 0 }, { operation_, 1 }, { open_bracket_, 2 }, { close_bracket_, 3 } };
	mVector<term*> terms;
	mVector<term*> pz; // польская запись
	string expression;
	
public:

	translator(string str) {
		expression = str;
	} 
	string get_expression()
	{
		return expression;
	}
	~translator() {
		for (size_t i = 0; i < terms.size(); i++)
		{
			delete terms[i];
		}
	}
	void parser() // перевод выражения-строки в вектор лексем
	{
		string str = expression;
		size_t state_numb = 0, sz = str.size();
		string N;
		if (sz == 0) 
			throw logic_error("no_expression");
		for (size_t i = 0; i < sz; i++) {
			if (state_numb == 0) {
				if (str[i] == '(')
					terms.push_back(new open_bracket);
				if (str[i] == ')')
					terms.push_back(new close_bracket);
				if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-')
					terms.push_back(new operation(str[i]));
				if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
					state_numb = 1;
					N += str[i];
				}
				
			}
			else {
				if (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
					N += str[i];
				else if (str[i] == '(') {
					state_numb = 0;
					terms.push_back(new operand(stod(N)));
					terms.push_back(new open_bracket);
					N = "";
				}
				else if (str[i] == ')') {
					state_numb = 0;
					terms.push_back(new operand(stod(N)));
					terms.push_back(new close_bracket);
					N = "";
				}
				else if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') {
					state_numb = 0;
					terms.push_back(new operand(stod(N)));
					terms.push_back(new operation(str[i]));
					N = "";
				}
				else throw logic_error("expression_syntax_error");
			}
		}
		if ((N != ""))
			terms.push_back(new operand(stod(N)));
	}

	void print_expression()
	{
		size_t sz = terms.size();
		for (size_t i = 0; i < sz; ++i)
		{
			if (terms[i]->getType() == operand_)
				cout << ((operand*)(terms[i]))->getValue() << " ";
			else cout << ((operation*)(terms[i]))->getOperation() << " ";
		}
		cout << endl;
	}

	void syntax_analysis() // синтаксический анализ
	{
		size_t state, sz = terms.size();
		if (!(checkBrackets(expression)))
			throw logic_error("incorrect_bracket");
		if (terms[0]->getType() == operand_)
			state = 0;
		if (terms[0]->getType() == operation_ || terms[0]->getType() == close_bracket_)
			throw logic_error("expression_syntax_error");
		if (terms[0]->getType() == open_bracket_) {
			state = 2;
		}		
		for (size_t i = 1; i < sz; i++) {
			
			switch (state)
			{
			case 0:
				if (terms[i]->getType() == operand_ || terms[i]->getType() == open_bracket_) {
					throw logic_error("expression_syntax_error");
				}
				state = states[terms[i]->getType()];
				break;
			case 1:
				if (terms[i]->getType() == operation_ || terms[i]->getType() == close_bracket_) {
					throw logic_error("expression_syntax_error");
				}
				state = states[terms[i]->getType()];
				break;
			case 2:
				if (terms[i]->getType() == operation_ || terms[i]->getType() == close_bracket_) {
					throw logic_error("expression_syntax_error");
				}
				state = states[terms[i]->getType()];
				break;
			case 3:
				if (terms[i]->getType() == open_bracket_ || terms[i]->getType() == operand_) {
					throw logic_error("expression_syntax_error");
				}
				state = states[terms[i]->getType()];
				break;
			}
		}
		state = states[terms[sz - 1]->getType()];
		if (state == 1 || state == 2){
			throw logic_error("expression_syntax_error");
		}
	}

	void converter() // перевод вектора лексем в ПЗ
	{
		mStack<term*> st; //стек операций

		int sz = terms.size();
		for (size_t i = 0; i < sz; i++) 
		{
			if (terms[i]->getType() == operand_)
			{
				pz.push_back(terms[i]);
			}

			if (terms[i]->getType() == operation_)
			{
				if (!(st.isEmpty()))
				{
					while ((!(st.isEmpty())) && st.top()->getType() == operation_ && ((operation*)(terms[i]))->getPriority() <= ((operation*)(st.top()))->getPriority())
					{
						pz.push_back(st.top());
						st.pop();
					}
					st.push(terms[i]);
				}
				else st.push(terms[i]);
			}

			if (terms[i]->getType() == open_bracket_)
			{
				st.push(terms[i]);
			}
			if (terms[i]->getType() == close_bracket_)
			{
				while ((!(st.isEmpty())) && (st.top()->getType() != open_bracket_))
				{
					pz.push_back(st.top());
					st.pop();
				}
				st.pop();
			}	
		}
		while (!(st.isEmpty()))
		{
			pz.push_back(st.top());
			st.pop();
		}
	}

	void print_polish()
	{
		size_t sz = pz.size();
		if (pz.isEmpty())
			cout << "empty";
		for (size_t i = 0; i < sz; ++i)
		{
			if (pz[i]->getType() == operand_)
				cout << ((operand*)(pz[i]))->getValue() << " ";
			else cout << ((operation*)(pz[i]))->getOperation() << " ";
		}
		std::cout << std::endl;
	}


	char invertBrackets(char ch)
	{
		if (ch == '(') return ')';
		else if (ch == '[') return ']';
		else if (ch == '{') return '}';
		return ' ';
	}

	bool checkBrackets(string& s)
	{
		mStack<char> stack;
		size_t len = s.length();
		for (size_t i = 0; i < len; i++)
		{
			if (s[i] == '(' || s[i] == '{' || s[i] == '[')
				stack.push(s[i]);
			else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
				if (!stack.isEmpty() && s[i] == invertBrackets(stack.top()))
					stack.pop();
				else return 0;
		}
		if (stack.isEmpty())
			return 1;
		else return 0;
	}



	double calculate() // вычисление в ПЗ
	{
		mStack<double> res;
		double left, right;
		int sz = pz.size();
		for (size_t i = 0; i < sz; i++)
		{
			if (pz[i]->getType() == operand_)
			{
				res.push(((operand*)(pz[i]))->getValue());
			}
			if (pz[i]->getType() == operation_ )
			{
				right = res.top();
				res.pop();
				left = res.top();
				res.pop();
				switch (((operation*)(pz[i]))->getOperation())
				{
				case('+'):
					res.push(left + right);
					break;
				case('-'):
					res.push(left - right);
					break;
				case('*'):
					res.push(left * right);
					break;
				case('/'):
					if (right != 0)
						res.push(left / right);
					else throw runtime_error("Runtime error: division by zero!");
					break; 
				}
			}

		}
		return res.top();
	}
	double get_result()
	{
		this->parser();
		this->syntax_analysis();
		this->converter();
		return this->calculate();
		
	}
};

