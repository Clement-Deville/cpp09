/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:57 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 16:51:24 by cdeville         ###   ########.fr       */
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

void	print_sequence(std::deque<int> &to_print, const char *message)
{
	std::deque<int>::const_iterator it;
	std::stringstream				sequence;

	for (it = to_print.begin(); it != to_print.end() ;it++ )
	{
		sequence << " " << *it;
	}
	std::cout << message << sequence.str() << std::endl;
}

void parse_argument(int argc, const char *argv[], std::deque<int> &parsed_nbs)
{
	int	number;

	for (int i = 1; i < argc; i++)
	{
		number = str_to_int(argv[i]);
		if (number == -1)
			throw std::runtime_error("Invalid argument");
		parsed_nbs.push_back(number);
	}
}

// void	generate_pairs(std::deque<int> &uper, std::deque<int> &lowers)
// {
// 	std::deque<int>::const_iterator it;
// 	int								a;
// 	int								b;

// 	for (it = uper.begin(); it != uper.end(); it++)
// 	{
// 		a = *it;
// 		if (++it == uper.end())
// 		{
// 			lowers.push_back(a);
// 			break;
// 		}
// 		b = *it;
// 		if (a < b)
// 			std::swap(a, b);
// 		data.upers.push_back(a);
// 		data.lowers.push_back(b);
// 	}
// }

void	generate_pairs(std::deque<int> &uper, std::deque<int> &lowers)
{
	int a;
	int b;
	int remainder = -1;

	if (uper.size() % 2)
	{
		remainder = uper[uper.size() - 1];
		uper.pop_back();
	}
	for (std::size_t i = 0; i < uper.size(); i += 2)
	{
		a = uper[i];
		b = uper[i + 1];
		if (a < b)
			std::swap(a, b);
		uper[i / 2] = a;
		lowers.push_back(b);
	}
	if (remainder != -1)
		lowers.push_back(remainder);
	uper.erase(uper.begin() + (uper.size() / 2), uper.end());
}

void	sort_small(std::deque<int> &uper, std::deque<int> lower)
{
	switch (uper.size())
	{
	case 3:
		if (uper[0] < uper[1])
		{
			if (uper[1] < uper[2]) /* 1 2 3 */
				return;
			else
			{
				if (uper[2] > uper[0]) /* 1 3 2 */
				{
					std::swap(uper[1], uper[2]);
					std::swap(lower[1], lower[2]);
				}
				else /* 2 3 1 */
				{
					std::swap(uper[0], uper[1]);
					std::swap(uper[0], uper[2]);
					std::swap(lower[0], lower[1]);
					std::swap(lower[0], lower[2]);
				}
			}
		}
		else /* arg[0] > arg[1] */
		{
			if (uper[0] < uper[2]) /* 2 1 3*/
			{
				std::swap(uper[0], uper[1]);
				std::swap(lower[0], lower[1]);
			}
			else
			{
				if (uper[1] > uper[2]) /* 3 2 1 */
				{
					std::swap(uper[0], uper[2]);
					std::swap(lower[0], lower[2]);
				}
				else /* 2 3 1 */
				{
					std::swap(uper[0], uper[1]);
					std::swap(uper[1], uper[2]);
					std::swap(lower[0], lower[1]);
					std::swap(lower[1], lower[2]);
				}
			}
		}
		break;
		case 2:
		{
			if (uper[0] > uper[1])
			{
				std::swap(uper[1], uper[0]);
				std::swap(lower[1], lower[0]);
			}
			break;
		}
	default:
		break;
	}
}

void	insert_lowers(std::deque<int> &uper, std::deque<int> &lowers)
{
	
}

void	merge_sort(std::deque<int> &uper)
{
	std::deque<int> lowers;

	if (uper.size() <= 3)
	{
		sort_small(uper, lowers);
		return;
	}
	generate_pairs(uper, lowers);
}
