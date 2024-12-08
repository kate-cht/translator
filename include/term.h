
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
	virtual double getValue() const noexcept = 0;
	virtual char getOperation() const noexcept = 0;
	virtual size_t  getPriority() const noexcept = 0;
};

class operand: public term
{
	double value;
	size_t  getPriority() const noexcept { return 0; };
	char getOperation() const noexcept { return 0; };
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
	double getValue() const noexcept
	{
		return 0;
	};
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
	double getValue() const noexcept { return 0; };
	size_t  getPriority() const noexcept { return 0; };
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
	double getValue() const noexcept { return 0; };
	size_t  getPriority() const noexcept { return 0; };
public:
	close_bracket() : bracket(')') { type = close_bracket_; };
	char getOperation() const noexcept {
		return bracket;
	};
};

