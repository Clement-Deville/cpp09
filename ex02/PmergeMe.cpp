/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:32:27 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/24 19:33:30 by cdeville         ###   ########.fr       */
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
