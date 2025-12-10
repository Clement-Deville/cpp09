/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:23:43 by cdeville          #+#    #+#             */
/*   Updated: 2025/12/10 09:57:17 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <sys/time.h>
#include <typeinfo>

// double timestamp()
// {
// 	timeval	t;
// 	gettimeofday(&t, 0);
// 	return (t.tv_sec + t.tv_usec);
// }

long time_passed(timeval &start, timeval &end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000 +
				(end.tv_usec - start.tv_usec));
}

int main( int ac, const char **argv )
{
	std::deque<int> dq;
	std::vector<int> v;
	timeval start[2];
	timeval end[2];

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

	gettimeofday(&start[0], 0);
	merge_sort(dq, 0);
	gettimeofday(&end[0], 0);

	gettimeofday(&start[1], 0);
	merge_sort(v, 0);
	gettimeofday(&end[1], 0);

	print_sequence(dq, "After:");
	std::cout << "Time to process a range of " << dq.size()
		<< " elements with std::deque: " << time_passed(start[0], end[0]) << " us" << std::endl;
	std::cout << "Time to process a range of " << v.size()
		<< " elements with std::vector: " << time_passed(start[1], end[1]) << " us" << std::endl;
		return (0);
}
