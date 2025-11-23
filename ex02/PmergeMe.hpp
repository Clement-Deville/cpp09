/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:17 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 22:10:56 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "iostream"
#include <deque>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cmath>

struct PmergeMe
{
	std::deque<int> upers;
	std::deque<int> lowers;
};

void	parse_argument(int argc, const char *argv[],
		std::deque<int> &parsed_nbs);
void	print_sequence(std::deque<int> &to_print, const char *message);
void	generate_pairs(std::deque<int> &uper, std::deque<int> &lowers);
void	merge_sort(std::deque<int> &data, int deepness);
