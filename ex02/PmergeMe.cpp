/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:57 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 15:35:44 by cdeville         ###   ########.fr       */
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

void	generate_pairs(std::deque<int> &arg, PmergeMe &data)
{
	std::deque<int>::const_iterator it;
	int								a;
	int								b;

	for (it = arg.begin(); it != arg.end(); it++)
	{
		a = *it;
		if (++it == arg.end())
		{
			data.lowers.push_back(a);
			break;
		}
		b = *it;
		if (a < b)
			std::swap(a, b);
		data.upers.push_back(a);
		data.lowers.push_back(b);
	}
}

void	sort_small(std::deque<int> &arg)
{
	switch (arg.size())
	{
	case 3:
		if (arg[0] < arg[1])
		{
			if (arg[1] < arg[2]) /* 1 2 3 */
				return;
			else
			{
				if (arg[2] > arg[0]) /* 1 3 2 */
					std::swap(arg[1], arg[2]);
				else /* 2 3 1 */
				{
					std::swap(arg[0], arg[1]);
					std::swap(arg[0], arg[2]);
				}
			}
		}
		else /* arg[0] > arg[1] */
		{
			if (arg[0] < arg[2]) /* 2 1 3*/
				std::swap(arg[0], arg[1]);
			else
			{
				if (arg[1] > arg[2]) /* 3 2 1 */
					std::swap(arg[0], arg[2]);
				else /* 2 3 1 */
				{
					std::swap(arg[0], arg[1]);
					std::swap(arg[1], arg[2]);
				}
			}
		}
		break;
		case 2:
		{
			if (arg[0] > arg[1])
				std::swap(arg[1], arg[0]);
			break;
		}
	default:
		break;
	}
}

void	merge_sort(std::deque<int> &arg)
{
	if (arg.size() <= 3)
		sort_small(arg);
}
