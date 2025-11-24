/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/24 19:41:59 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>

int main( int ac, const char **argv )
{
	std::deque<int> dq;
	std::vector<int> v;

	if (ac < 2)
	{
		std::cerr << "Error" <<std::endl;
		return (1);
	}

	try {
		parse_argument(ac, argv, dq);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	print_sequence(dq, "Before:");
	merge_sort(dq, 0);
	print_sequence(dq, "After:");
	return (0);
}
