/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/24 22:08:49 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <sys/time.h>
#include <typeinfo>

long timestamp()
{
	timeval	t;
	gettimeofday(&t, 0);
	return (t.tv_sec + t.tv_usec);
}

int main( int ac, const char **argv )
{
	std::deque<int> dq;
	std::vector<int> v;
	long start[2];
	long end[2];

	if (ac < 2)
	{
		std::cerr << "Error" <<std::endl;
		return (1);
	}

	try {
		parse_argument(ac, argv, dq);
		parse_argument(ac, argv, v);

	}
	catch (std::exception &e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	print_sequence(dq, "Before:");
	start[0] = timestamp();
	merge_sort(dq, 0);
	end[0] = timestamp();
	start[1] = timestamp();
	merge_sort(v, 0);
	end[1] = timestamp();
	print_sequence(dq, "After:");
	std::cout << "Time to process a range of " << dq.size()
		<< " elements with std::deque: " << end[0] - start[0] << " us" << std::endl;
	std::cout << "Time to process a range of " << v.size()
		<< " elements with std::vector: " << end[1] - start[1] << " us" << std::endl;
		return (0);
}
