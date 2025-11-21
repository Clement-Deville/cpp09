/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:14 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/21 10:07:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool is_operator(char c)
{
	if (c == '*' || c == '/' || c == '-' || c == '+')
		return (true);
	return (false);
}

void	process_operator(char ope, stack_t &numbers)
{
	int a;
	int b;

	if (numbers.size() < 2)
		throw std::runtime_error("Error");
	b = numbers.top();
	numbers.pop();
	a = numbers.top();
	numbers.pop();
	switch (ope)
	{
	case '*':
		a *= b;
		break;
	case '+':
		a += b;
		break;
	case '-':
		a -= b;
		break;
	case '/':
		if (b == 0)
			throw std::runtime_error("Error");
		a /= b;
		break;
	default:
		throw std::runtime_error("Error");
		break;
	}
	numbers.push(a);
}

void	process_token(std::string &token, stack_t &numbers)
{
	if (token.size() == 1)
	{
		if (isdigit(token[0]))
			numbers.push(token[0] - '0');
		else if (is_operator(token[0]))
			process_operator(token[0], numbers);
		else
			throw std::runtime_error("Error");
	}
	else
	{
		if (token.size() != 2 || token[0] != '-' || isdigit(token[1]) == false)
			throw std::runtime_error("Error");
		numbers.push((token[1] - '0') * -1);
	}
}

void parse(std::string arg)
{
	std::istringstream iss(arg);
	std::string	token;
	stack_t	numbers;

	while (iss >> token)
		process_token(token, numbers);
	if (numbers.size() != 1)
		throw std::runtime_error("Error");
	std::cout << numbers.top() << std::endl;
}
