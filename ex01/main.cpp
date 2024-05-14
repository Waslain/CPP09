/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:56:02 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/04 15:36:00 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>

bool IsOp(char c){
	//Check for operators.
	switch (c){
		case '+':
		case '-':
		case '*':
		case '/':
			return true;
		default:
			return false;
	}
}

bool doOperation(std::stack<int> &numbers, char token)
{
	if (numbers.size() < 2) {
		std::cerr << "Error: not enough numbers to do operation" << std::endl;
		return false;
	}
	int a = numbers.top();
	numbers.pop();
	int b = numbers.top();
	numbers.pop();
	switch (token){
		case '+':
			numbers.push(b + a);
			break;
		case '-':
			numbers.push(b - a);
			break;
		case '*':
			numbers.push(b * a);
			break;
		case '/':
			if (b == 0){
				std::cerr << "Error: division by zero" << std::endl;
				return false;
			}
			numbers.push(b / a);
			break;
	}
	return true;
}

void RPN(char *str)
{
	std::stack<int> stack;
	std::istringstream iss(str);
	char token;

	while (iss >> token)
	{
		if (isdigit(token)){
			stack.push(token -	'0');
		}
		else if (IsOp(token)){
			if (doOperation(stack, token) == false)
				return ;
		}
		else {
			std::cerr << "Error: invalid input" << std::endl;
			return ;
		}
	}
	if (!iss.eof() || stack.size() != 1) {
		std::cerr << "Error: invalid input" << std::endl;
		return ;
	}
	std::cout << stack.top() << std::endl;
	return ;
}


int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid args number" << std::endl;
		return (1);
	}
	else
		RPN(argv[1]);
	return (0);
}
