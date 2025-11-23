/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 16:45:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main( int ac, const char **argv )
{
	std::deque<int> test;
	std::deque<int> lowers;


	if (ac < 2)
	{
		std::cerr << "Error" <<std::endl;
		return (1);
	}

	try {
		parse_argument(ac, argv, test);
		generate_pairs(test, lowers);
		print_sequence(test, "Upers:");
		print_sequence(lowers, "Lowers:");
	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0) ;
	print_sequence(test, "Before:");
	merge_sort(test);
	print_sequence(test, "After:");
	// print_sequence(&data.upers, "U:");
	// print_sequence(&data.lowers, "L:");
	return (0);
}
