/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:45:32 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 09:12:52 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
		
}

RPN::RPN(std::string arg)
{
	int i = 0;
	try
	{
		checkInput(arg);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	i = 0;
	try
	{
		processInput(arg);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

void RPN::checkInput(std::string arg)
{
	if (arg.find_first_not_of("0123456789+-*/ ") != arg.npos)
		throw std::runtime_error("Error - wrong input");
}

void RPN::processInput(std::string arg)
{
	int i = 0;
	float a = 0;
	float b = 0;
	while (arg[i])
	{
		if (arg[i] == ' ')
			i++;
		else if (isdigit(arg[i]))
			st.push(atof(&arg[i++]));
		else if (strchr("+-*/", arg[i]))
		{
			if (st.size() < 2)
				throw std::runtime_error("Error - too many operators");
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			st.push(operate(arg[i], a, b));
			i++;
		}

	}
	if (st.size() != 1)
		throw std::runtime_error("Error - not enough operators");
	std::cout << st.top() << std::endl;
}

float	RPN::operate(char c, float a, float b)
{
	switch (c)
	{
		case '+':
			return a + b;
			break;
		case '-':
			return a - b;
			break;
		case '*':
			return a * b;
			break;
		case '/':
			return a / b;
			break;
		default:
			throw std::runtime_error("Error - error during operation");
			break;
	}
}

RPN::RPN(const RPN &copy)
{
	st = copy.st;
}

RPN &RPN::operator=(const RPN &copy)
{
	st = copy.st;
}

RPN::~RPN()
{
}