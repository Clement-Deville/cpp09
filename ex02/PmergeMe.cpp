/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:32:27 by cdeville          #+#    #+#             */
/*   Updated: 2025/12/10 09:59:50 by cdeville         ###   ########.fr       */
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

void	set_next_range(int &index, int &n, int &range, int &to_insert)
{
	range = (1 << n) - range;
	if (to_insert < range)
		range = to_insert;
	index += range;
}

/* Forcing rotate instead of erase and insert for std::vector */
void	insert(int src_index,
				int dest_index,
				int deepness,
				std::vector<int> &data)
{
	int	offset;
	int	tmp;

	tmp = data[src_index];
	std::rotate(data.begin() + dest_index, data.begin() + src_index, data.end());
	if (deepness == 0)
		return;
	for (int i = 1; i <= deepness; i++)
	{
		offset = data.size() >> i;
		insert(src_index + offset,
				dest_index + offset, i - 1, data);
	}
}
