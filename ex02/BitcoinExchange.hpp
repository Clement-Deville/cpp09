/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:08:59 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/20 12:41:37 by cdeville         ###   ########.fr       */
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
#include <ctime>

#define DATE_SIZE (sizeof("YYYY-MM-DD") - 1)

typedef std::map<time_t, double> b_map_t;

class BitcoinExchange
{
private:
	std::map<time_t, double> _database;
	void	process_line(std::string &line) const;
	double calculate_rate(time_t timestamp, double value) const;
	void	fill_map(std::string &line);
public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &path);
	BitcoinExchange(const BitcoinExchange &Cpy);
	BitcoinExchange &operator=(const BitcoinExchange &Other);
	~BitcoinExchange();

	void parse(const std::string &filename) const;
	void	print_map(void) const;
};

bool check_csv_header(const std::string &header);
