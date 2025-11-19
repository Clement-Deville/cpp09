/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:08:59 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/19 14:15:04 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <cstring>
#include <cstdlib>

#define DATE_SIZE (sizeof("YYYY-MM-DD") - 1)

class BitcoinExchange
{
private:
	std::map<std::string, int> _database;
public:
	BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange &Cpy);
	BitcoinExchange &operator=(const BitcoinExchange &Other);
	~BitcoinExchange();

	void parse(const std::string &filename) const;
};
