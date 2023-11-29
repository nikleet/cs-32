/**
 * CS 32, Homework 2, eval.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 5/3/2023
*/

#include <string>
#include <stack>
#include <cassert>
#include <iostream>

using namespace std;

bool infixToPostfix(string infix, string& postfix);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.
// Initialize the operand stack to empty
// 	For each character ch in the postfix string
// 	    if ch is an operand
// 	        push the value that ch represents onto the operand stack
// 	    else // ch is a binary operator
// 	        set operand2 to the top of the operand stack
// 			pop the stack
// 	        set operand1 to the top of the operand stack
// 			pop the stack
// 			apply the operation that ch represents to operand1 and
// 	            operand2, and push the result onto the stack
// 	When the loop is finished, the operand stack will contain one item,
// 	  the result of evaluating the expression

bool isOperator(const char ch) { return (ch == '^' || ch == '&' || ch == '!'); }

bool isOperand(const char ch) { return (ch == 'T' || ch == 'F'); }

int getPrecedence(const char ch) {
	switch (ch) {
		case '!':
			return 3;
		case '&':
			return 2;
		case '^':
			return 1;
		default:
			return -1;
	}
}

int evaluate(string infix, string& postfix, bool& result) {
	stack<bool> operands;
	bool operand1;
	bool operand2;
	if (!infixToPostfix(infix, postfix)) {
		return 1;
	}
	for (char ch : postfix) {
		if (isOperand(ch))
			operands.push(ch == 'T');
		else if (ch == '!') {
			bool temp = operands.top();
			operands.pop();
			operands.push(!temp);
		}
		else {
			operand2 = operands.top();
			operands.pop();
			operand1 = operands.top();
			operands.pop();
			if (ch == '&')
				operands.push(operand1 && operand2);
			if (ch == '^')
				operands.push((operand1 || operand2) && (operand1 != operand2));
		}
	}
	result = operands.top();
	return 0;
}
/*	Shunting-Yard Algorithm:
	Initialize postfix to empty
	Initialize the operator stack to empty
	For each character ch in the infix string
	Switch(ch)
		      case operand:
				  append ch to end of postfix
					  break
			  case '(':
				  push ch onto the operator stack
					  break
			  case ')':
				  // pop stack until matching '('
				  While stack top is not '('
					  append the stack top to postfix
					  pop the stack
					  pop the stack  // remove the '('
					  break
			  case operator:
				  While the stack is not empty and the stack top is not '('
					  and precedence of ch <= precedence of stack top
					  append the stack top to postfix
					  pop the stack
					  push ch onto the stack
					  break
	While the stack is not empty
			append the stack top to postfix
			pop the stack
	converts string infix to postfix string
*/
bool infixToPostfix(string infix, string& postfix) {
	if (infix.length() == 0)
		return false;
	postfix = "";
	int parenCount = 0;
	// initialize pch to arbitrary character space to prevent undefined behavior when i = 0
	char pch = ' '; // pch stores previous nonspace character
	stack<char> operators;
	for (int i = 0; i < infix.length(); i++) {
		char ch = infix.at(i);
		if (i > 0 && !isspace(infix.at(i - 1)))
			pch = infix.at(i - 1);
		if (!isspace(ch)) {
			switch (ch) {
			case 'T':
				if (isOperand(pch))
					return false;
				postfix += ch;
				break;
			case 'F':
				if (isOperand(pch))
					return false;
				postfix += ch;
				break;
			case '(':
				if (isOperand(pch) || pch == ')' || i == infix.length() - 1)
					return false;
				operators.push(ch);
				parenCount++;
				break;
			case ')':
				if (isOperator(pch) || pch == '(')
					return false;
				while (operators.top() != '(') {
					postfix += operators.top();
					operators.pop();
				}
				operators.pop();
				// appends all ! operators preceding a ( to postfix
				while (!operators.empty() && operators.top() == '!') {
					postfix += operators.top();
					operators.pop();
				}
				parenCount--;
				break;
			case '!':
				// if ! precedes (, push ! to the stack -- the ) case will handle it later.
				// if ! precedes !, push ! to the stack -- it will be handled in the
				// else-if statement below
				if (i != infix.length() - 1 && (infix.at(i + 1) == '(' || infix.at(i + 1) == '!'))
					operators.push(ch);
				// if ! precedes operand, append ! followed by that operand to postfix
				else if (i != infix.length() - 1 && isOperand((infix.at(i + 1)))) {
					postfix += infix.at(i + 1);
					postfix += ch;
					// handles consecutive ! operators not before a (
					// while there is a ! on top of the stack, append it to postfix
					while (!operators.empty() && operators.top() == '!') {
						postfix += operators.top();
						operators.pop();
					}
					i++; // increment i
				}
				else
					return false;
				break;
			case '&':
				if (isOperator(pch) || i == infix.length() - 1 || i == 0)
					return false;
				while (!operators.empty() && operators.top() != '('
					&& getPrecedence(ch) <= getPrecedence(operators.top())) {
					postfix += operators.top();
					operators.pop();
				}
				operators.push(ch);
				break;
			case '^':
				if (isOperator(pch) || i == infix.length() - 1 || i == 0)
					return false;
				while (!operators.empty() && operators.top() != '('
					&& getPrecedence(ch) <= getPrecedence(operators.top())) {
					postfix += operators.top();
					operators.pop();
				}
				operators.push(ch);
				break;
			default:
					return false;
			}
		}
	}
	// check for same number of closed and open parens
	if (parenCount != 0)
		return false;
	while (!operators.empty()) {
		postfix += operators.top();
		operators.pop();
	}
	return true;
}


int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("F ^ !(T & F)", pf, answer) == 0 && answer);
	assert(evaluate("!!T", pf, answer) == 0 && answer && pf == "T!!");
	assert(evaluate("T & !(T ^ F)", pf, answer) == 0 && !answer && pf == "TTF^!&");
	assert(evaluate("T & !!(T ^ F)", pf, answer) == 0 && answer && pf == "TTF^!!&");
	assert(evaluate("T & !!(T ^ !(F & T)) & T", pf, answer) == 0 && !answer && pf == "TTFT&!^!!&T&");
	evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer);
	cout << "Postfix: " << pf << "\nAnswer: " << answer << endl;
	cout << "Passed all tests" << endl;
}

