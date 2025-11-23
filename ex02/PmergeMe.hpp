/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:05:17 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/23 12:39:33 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iostream"
#include <deque>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>

std::deque<int> *parse_argument(int argc, const char *argv[]);
void	print_sequence(std::deque<int> *to_print, const char *message);
