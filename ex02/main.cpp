/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 22:14:46 by cdeville         ###   ########.fr       */
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
