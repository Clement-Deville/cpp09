/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/24 09:03:06 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main( int ac, const char **argv )
{
	std::deque<int> test;


	if (ac < 2)
	{
		std::cerr << "Error" <<std::endl;
		return (1);
	}

	// int index = 0;
	// int	range = 0;
	// int n = 1;

	// while (n < 10)
	// {
	// 	set_next_range(index, n , range);
	// 	std::cout << "Index: " << index << " n: " << n << " range: " << range << std::endl;
	// 	n++;
	// }

	try {
		parse_argument(ac, argv, test);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	print_sequence(test, "Before:");
	merge_sort(test, 0);
	print_sequence(test, "After:");
	return (0);
}
