/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:57 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 22:44:30 by cdeville         ###   ########.fr       */
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


void	swap(int a, int b, int deepness, std::deque<int> &data)
{
	int offset;

	std::swap(data[a], data[b]);
	if (deepness == 0)
		return ;
	for (int i = deepness; i > 0; i--)
	{
		offset = data.size() / std::pow(2, deepness);
		swap(a + offset, b + offset, deepness - 1, data);
	}
}

void	insert(int src_index,
				int dest_index,
				int deepness,
				std::deque<int> &data)
{
	int	offset;
	int	tmp;

	tmp = data[src_index];
	data.erase(data.begin() + src_index);
	data.insert(data.begin() + dest_index, tmp);
	if (deepness == 0)
		return;
	for (int i = deepness; i > 0; i--)
	{
		offset = data.size() / std::pow(2, deepness);
		insert(src_index + offset,
				dest_index + offset, deepness - 1, data);
	}
}

void	sort_small(std::deque<int> &data, int deepness)
{
	switch (data.size())
	{
	case 3:
		if (data[0] < data[1])
		{
			if (data[1] < data[2]) /* 1 2 3 */
				return;
			else
			{
				if (data[2] > data[0]) /* 1 3 2 */
					swap(1, 2, deepness, data);
				else /* 2 3 1 */
				{
					swap(0, 1, deepness, data);
					swap(0, 2, deepness, data);
				}
			}
		}
		else /* arg[0] > arg[1] */
		{
			if (data[0] < data[2]) /* 2 1 3*/
				swap(0, 1, deepness, data);
			else
			{
				if (data[1] > data[2]) /* 3 2 1 */
					swap(0, 2, deepness, data);
				else /* 2 3 1 */
				{
					swap(0, 1, deepness, data);
					swap(1, 2, deepness, data);
				}
			}
		}
		break;
		case 2:
		{
			if (data[0] > data[1])
				swap(1, 0, deepness, data);
			break;
		}
	default:
		break;
	}
}

void	swap_upers(std::deque<int> &data, int deepness)
{
	int offset;
	int

	offset = data.size() / std::pow(2, deepness + 1);
	for (int i = 0; i < offset; i++)
	{
		if (data[i] < data[i + offset])
			swap(i, i + offset, deepness, data);
	}
}

void	process_insertion(std::deque<int> &data, int deepness)
{
	int	offset;
	int	to_insert;

	offset =  data.size() / std::pow(2, deepness + 1);
	to_insert = data.size() / std::pow(2, deepness); - offset - 1;
	insert(0 + offset, 0, deepness, data);
	// to smartly match index of remainings
}

void	merge_sort(std::deque<int> &data, int deepness)
{
	if (data.size() / (std::pow(2, deepness)) < 4)
	{
		sort_small(data, deepness);
		return;
	}
	swap_upers(data, deepness);
	merge_sort(data, deepness + 1);
	process_insertion(data, deepness);
}
