
#pragma once

#include <iostream>
#include <map>
using namespace std;


enum types
{
	operand_, operation_, open_bracket_, close_bracket_
};


class term
{
protected:
	map<char, size_t> priorit{ {'+',  1}, {'-', 1}, {'/', 2}, {'*', 2} };
	
	types type;
public:
	types getType() const noexcept { return type; };
};

class operand: public term
{
	double value;
public:
	operand(double val)
	{
		value = val;
		type = operand_;
	};
	double getValue() const noexcept
	{
		return value;
	};
	~operand()
	{

	}
};

class operation : public term
{
	char oper;
	int priority;
public:
	operation(char op)
	{
		oper = op;
		priority = priorit[op];
		type = operation_;
	}; 
	size_t getPriority() const noexcept
	{
		return priority;
	};
	char getOperation() const noexcept
	{
		return oper;
	};
	 
};


class open_bracket : public term
{
	char bracket;
public:
	open_bracket() : bracket('(') { type = open_bracket_; };
	char getOperation() const noexcept {
		return bracket;
	};
};

class close_bracket : public term
{
private:
	char bracket;
public:
	close_bracket() : bracket(')') { type = close_bracket_; };
	char getOperation() const noexcept {
		return bracket;
	};
};