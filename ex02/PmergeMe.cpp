/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:57 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 12:41:08 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int str_to_int(const char *str)
{
	long nb;

	for (int i = 0; str[i]; i++)
	{
		if (std::isdigit(str[i]) == false)
			return (-1);
	}
	nb = std::strtol(str, NULL, 10);
	if (errno == ERANGE || (nb > (long)std::numeric_limits<int>::max) || nb < 0)
		return (-1);
	return (static_cast<int>(nb));
}

void	print_sequence(std::deque<int> *to_print, const char *message)
{
	std::deque<int>::const_iterator it;
	std::stringstream				sequence;

	for (it = to_print->begin(); it != to_print->end() ;it++ )
	{
		sequence << " " << *it;
	}
	std::cout << message << sequence.str() << std::endl;
}

std::deque<int> *parse_argument(int argc, const char *argv[])
{
	int	number;
	std::deque<int> *parsed_nbs;

	parsed_nbs = new std::deque<int>;
	for (int i = 1; i < argc; i++)
	{
		number = str_to_int(argv[i]);
		if (number == -1)
		{
			delete parsed_nbs;
			throw std::runtime_error("Invalid argument");
		}
		parsed_nbs->push_back(number);
	}
	return (parsed_nbs);
}
