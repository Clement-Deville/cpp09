/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:57 by cdeville          #+#    #+#             */
/*   Updated: 2025/12/10 09:06:55 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	print_sequence(T &to_print, const char *message)
{
	typename T::const_iterator it;
	std::stringstream				sequence;

	for (it = to_print.begin(); it != to_print.end() ;it++ )
	{
		sequence << " " << *it;
	}
	std::cout << message << sequence.str() << std::endl;
}

template <typename T>
void parse_argument(int argc, const char *argv[], T &parsed_nbs)
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

template <typename T>
void	swap(int a, int b, int deepness, T &data)
{
	int offset;

	std::swap(data[a], data[b]);
	if (deepness == 0)
		return ;
	for (int i = 1; i <= deepness; i++)
	{
		offset = data.size() >> i;
		swap(a + offset, b + offset, i - 1, data);
	}
}

template <typename T>
void	insert(int src_index,
				int dest_index,
				int deepness,
				T &data)
{
	int	offset;
	int	tmp;

	tmp = data[src_index];
	data.erase(data.begin() + src_index);
	data.insert(data.begin() + dest_index, tmp);
	if (deepness == 0)
		return;
	for (int i = 1; i <= deepness; i++)
	{
		offset = data.size() >> i;
		insert(src_index + offset,
				dest_index + offset, i - 1, data);
	}
}

template <typename T>
void	swap_upers(T &data, int deepness)
{
	int offset;

	offset = data.size() >> (deepness + 1);
	for (int i = 0; i < offset; i++)
	{
		if (data[i] < data[i + offset])
			swap(i, i + offset, deepness, data);
	}
}

template <typename T>
int	binary_search(T &data, int value, int end)
{
	typename T::iterator it;

	it = std::lower_bound(data.begin(), data.begin() + end, value);
	if (it == data.begin())
		return (0);
	return (std::distance(data.begin(), it));
}

template <typename T>
void	insert_lower_range(T &data, int index, int range, int deepness)
{
	int	target;

	int end = index - range + 1;
	for (int i = 0; i < range; i++)
	{
		target = binary_search(data, data[index], end);
		insert(index, target, deepness, data);
	}
}

template <typename T>
void	process_insertion(T &data, int deepness)
{
	int	offset;
	int	to_insert;
	int	range = 0;
	int	n = 1;
	int	index;

	offset =  data.size() >> (deepness + 1);
	to_insert = (data.size() >> deepness) - offset - 1;
	index = offset;
	insert(0 + offset, 0, deepness, data);
	while (to_insert)
	{
		set_next_range(index, n, range, to_insert);
		insert_lower_range(data, index, range, deepness);
		to_insert -= range;
	}
	// to smartly match index of remainings
}

template <typename T>
void	merge_sort(T &data, int deepness)
{

	if ((data.size() >> deepness) == 1)
		return;
	swap_upers(data, deepness);
	merge_sort(data, deepness + 1);
	process_insertion(data, deepness);
}
