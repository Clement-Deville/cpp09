/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:17 by cdeville          #+#    #+#             */
/*   Updated: 2025/12/10 09:00:13 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <errno.h>
#include <algorithm>

struct PmergeMe
{
	std::deque<int> upers;
	std::deque<int> lowers;
};

void	set_next_range(int &index, int &n, int &range, int &to_insert);
int		str_to_int(const char *str);

#include "PmergeMe.tpp"
