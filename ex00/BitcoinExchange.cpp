/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:14 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/21 08:26:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/**========================================================================
 *                   CONSTRUCTOR/DESTRUCTORS/OPERATORS
 *========================================================================**/

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const std::string &path)
{
	std::ifstream	file(path.c_str());
	std::string		line;
	int				count = 0;

	if (!file)
	{
		std::cout << "Error: could not open file." << std::endl;
		throw std::runtime_error("BitcoinExchange constructor exception");
	}

	if (!std::getline(file, line))
	{
		if (!file.eof())
		{
			std::cout << "Error: could not read file." << std::endl;
			throw std::runtime_error("BitcoinExchange constructor exception");
		}
		throw std::runtime_error("No data extracted");
	}

	if (!check_csv_header(line))
		throw std::runtime_error("Incorrect csv header");

	while (file)
	{
		if(!std::getline(file, line))
		{
			if (!file.eof())
			{
				std::cout << "Error: could not read file." << std::endl;
				throw std::runtime_error("BitcoinExchange constructor exception");
			}
		}
		if (line.empty() || line[0] == '#')
			continue;
		fill_map(line);
		count++;
	}
	if (!count)
		throw std::runtime_error("No data extracted");
	// print_map();
}


BitcoinExchange::BitcoinExchange(const BitcoinExchange &Cpy)
{
	*this = Cpy;
}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &Other)
{
	if (this == &Other)
		return (*this);
	this->_database = Other._database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

/**========================================================================
 *                           METHODS
 *========================================================================**/

int str_to_int(std::string &str)
{
	long nb;

	for (int i = 0; str[i]; i++)
	{
		if (std::isdigit(str[i]) == false)
			return (-1);
	}
	nb = std::strtol(str.c_str(), NULL, 10);
	if (errno == ERANGE)
		return (-1);
	return (static_cast<int>(nb));
}

time_t check_validity(std::string &year, std::string &month, std::string &day)
{
	int	year_nb;
	int month_nb;
	int	day_nb;
	struct tm date;

	std::memset(&date , 0, sizeof(tm));
	if (year.size() != 4)
		return (-1);
	year_nb = str_to_int(year);
	if (year_nb == -1 || year_nb < 1970)
		return (-1);

	if (month.size() != 2)
		return (-1);
	month_nb = str_to_int(month);
	if (month_nb < 1 || month_nb > 12)
		return (-1);

	if (day.size() != 2)
		return (-1);
	day_nb = str_to_int(day);
	if (day_nb < 1 || day_nb > 31)
		return (-1);

	/* Check des mois ayant 31 jours */
	if (day_nb == 31)
	{
		if (month_nb == 4 || month_nb == 6 || month_nb == 9 || month_nb == 11)
			return (-1);
	}

	/* Check special de fevrier et des annees bissextile */
	if (month_nb == 2)
	{
		if (day_nb > 29)
			return (-1);
		if (day_nb == 29)
		{
			/* Si l'annee n'est pas un multiple de 4 ou qu'elle est un multiple de 100
				sans etre un multiple de 400 */
			if (year_nb % 4 != 0 || (year_nb % 100 == 0 && year_nb % 400 != 0))
				return (-1);
		}
	}
	date.tm_mday = day_nb;
	date.tm_mon = month_nb -1;
	date.tm_year = year_nb;
	return (std::mktime(&date));
}

time_t	check_date(std::string date)
{
	std::string			tokens[4];

	int i = 0;
	if (date.size() != DATE_SIZE)
		return (-1);
	if (date[4] != '-' || date[7] != '-')
		return (-1);
	date[4] = ' ';
	date[7] = ' ';

	std::istringstream	iss(date);
	for (;i < 4 && iss >> tokens[i]; i++)
	{}
	if (i != 3)
		return (-1);
	return (check_validity(tokens[0], tokens[1], tokens[2]));
}

double	check_value(std::string &value, bool is_conf)
{
	char	*endptr;
	double	fnb;

	fnb = std::strtod(value.c_str(), &endptr);
	if (endptr != &value.c_str()[value.size()])
	{
		std::cout << "Error: must be a number: " << value << std::endl;
		return (-1.0);
	}
	if ((errno == ERANGE) || fnb > (is_conf? 2147483648: 1000))
	{
		std::cout << "Error: too large number: " << value << std::endl;
		return(-1.0);
	}
	if (fnb < 0)
	{
		std::cout << "Error: not a positive number: " << value << std::endl;
		return(-1.0);
	}
	return (fnb);
}

std::string format_time(time_t timestamp)
{
	std::ostringstream iss;

	struct tm *data;
	data = std::localtime(&timestamp);
	iss.fill('0');
	iss.width(4);
	iss << data->tm_year << '-';
	iss.width(2);
	iss.fill('0');
	iss << data->tm_mon + 1 << '-';
	iss.width(2);
	iss.fill('0');
	iss << data->tm_mday;
	return (iss.str());
}

void	BitcoinExchange::print_map(void) const
{
	b_map_t::const_iterator it;

	for (it = this->_database.begin(); it != this->_database.end(); it++)
	{
		std::cout << format_time(it->first) << "," << it->second << std::endl;
	}
}

bool check_csv_header(const std::string &header)
{
	int	ret;
	int i = 0;

	ret = false;
	while (header[i] && std::isprint(header[i]) && header[i] != ',')
		i++;
	if (!i || header[i++] != ',')
		return (false);
	if (std::isprint(header[i]) && header[i++] != ',')
	{
		while (std::isprint(header[i]) && header[i++] != ',')
			i++;
		if (header[i])
			return (false);
	}
	return (true);
}

void	BitcoinExchange::fill_map(std::string &line)
{
	double value;
	std::string word[3];
	time_t timestamp;
	int i = 0;

	if (line.length() < DATE_SIZE + 2 || line[10] != ',')
		throw std::runtime_error("Incorrect line format");
	line[10] = ' ';
	std::istringstream iss(line);
	for (; i < 3 && iss >> word[i]; i++)
	{
	}
	if (i != 2)
		throw std::runtime_error("Incorrect line format");
	timestamp = check_date(word[0]);
	if (timestamp == -1)
		throw std::runtime_error("Incorrect line format");
	value = check_value(word[1], true);
	if (value == -1.0)
		throw std::runtime_error("Incorrect line format");
	this->_database[timestamp] = value;
}

double	BitcoinExchange::calculate_rate(time_t timestamp, double value) const
{
	b_map_t::const_iterator it;
	double	rate;

	it = this->_database.lower_bound(timestamp);
	if (it == this->_database.begin())
		return (-1.0);
	if (it != this->_database.end() && it->first == timestamp)
		return (value * it->second);
	rate = (--it)->second;
	return (value * rate);
}


void	BitcoinExchange::process_line(std::string &line) const
{
	std::istringstream iss(line);
	std::string word[4];
	double	value;
	time_t timestamp;
	int i = 0;

	for (; i < 4 && iss >> word[i]; i++)
	{
	}
	if (i != 3)
	{
		std::cout << "Wrong number of argument, usage: 'YYYY-MM-DD | {integer|decimal}'" << std::endl;
		return;
	}
	timestamp = check_date(word[0]);
	if (timestamp == -1)
	{
		std::cout << "Error: bad input => " << word[0] << std::endl;
		return;
	}
	if (word[1] != "|")
	{
		std::cout << "Error: bad separator => " << word[1] << std::endl;
		return;
	}
	value = check_value(word[2], false);
	if (value == -1.0)
		return;
	value = calculate_rate(timestamp, value);
	if (value == -1.0)
	{
		std::cout << "Error: No data yet for that date: " << word[1] << std::endl;
		return;
	}
	std::cout << word[0] << " => " << word[2] << " = ";

	std::cout << std::fixed;
	std::cout.precision(2);
	std::cout << value << std::endl;
}

bool check_input_header(const std::string &header)
{
	int	ret;
	int i = 0;

	ret = false;
	while (header[i] && std::isprint(header[i]) && !std::isspace(header[i]))
	{
		i++;
	}
	if (!i || !std::isspace(header[i++]))
		return (false);
	if (header[i++] != '|' || !std::isspace(header[i++]))
		return (false);
	if (std::isprint(header[i++]))
	{
		while (std::isprint(header[i]))
			i++;
		if (header[i])
			return (false);
	}
	return (true);
}

void BitcoinExchange::parse(const std::string &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file)
	{
		std::cout << "Error: could not open file." << std::endl;
		return;
	}
	if (!std::getline(file, line))
	{
		if (!file.eof())
			std::cout << "Error: could not read file." << std::endl;
		return;
	}
	if (!check_input_header(line))
	{
		std::cout << "Error: bad header" << std::endl;
		return ;
	}
	while (file)
	{
		if(!std::getline(file, line))
		{
			if (!file.eof())
				std::cout << "Error: could not read file." << std::endl;
			return;
		}
		if (line.empty() || line[0] == '#')
			continue;
		process_line(line);
	}
	return;
}
