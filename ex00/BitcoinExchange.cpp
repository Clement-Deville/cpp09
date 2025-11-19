/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:23:14 by cdeville          #+#    #+#             */
/*   Updated: 2025/11/19 14:24:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/**========================================================================
 *                   CONSTRUCTOR/DESTRUCTORS/OPERATORS
 *========================================================================**/

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &Cpy)
{
	(void)Cpy;
}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange &Other)
{
	(void)Other;
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

int check_validity(std::string &year, std::string &month, std::string &day)
{
	int	year_nb;
	int month_nb;
	int	day_nb;

	if (year.size() != 4)
		return (false);
	year_nb = str_to_int(year);
	if (year_nb == -1)
		return (false);

	if (month.size() != 2)
		return (false);
	month_nb = str_to_int(month);
	if (month_nb < 1 || month_nb > 12)
		return (false);

	if (day.size() != 2)
		return (false);
	day_nb = str_to_int(day);
	if (day_nb < 1 || month_nb > 31)
		return (false);

	/* Check des mois ayant 31 jours */
	if (day_nb == 31)
	{
		if (month_nb == 4 || month_nb == 6 || month_nb == 9 || month_nb == 11)
			return (false);
	}

	/* Check special de fevrier et des annees bissextile */
	if (month_nb == 2)
	{
		if (day_nb > 29)
			return (0);
		if (day_nb == 29)
		{
			/* Si l'annee est un multiple de 4 et qu'elle n'est pas un multiple de 100
				si elle n'est pas un multiple de 400 */
			if (year_nb % 4 != 0 && (year_nb % 400 == 0 || year_nb % 100 != 0))
				return (false);
		}
	}
	return (true);
}

int check_date(std::string date)
{
	std::string			tokens[4];

	int i = 0;
	if (date.size() != DATE_SIZE)
		return (false);
	if (date[3] != '-' || date[5] != '-')
		return (false);
	date[3] = ' ';
	date[5] = ' ';

	std::istringstream	iss(date);
	while (i < 4 && iss >> tokens[i++])
	{}
	if (i != 3)
		return (false);
	if (check_validity(tokens[0], tokens[1], tokens[2]))
		return (false);
	return (true);
}

float	check_value(std::string &value)
{
	char	*endptr;
	float	fnb;

	fnb = std::strtof(value.c_str(), &endptr);
	if ((errno == ERANGE) || endptr != &value.c_str()[value.size()])
	{
		std::cerr << "Error: must be a number: " << value << std::endl;
		return (-1.0);
	}
	if (fnb < 0)
	{
		std::cerr << "Error: not a positive number: " << value << std::endl;
		return(-1.0);
	}
	if (fnb >= 2147483648)
	{
		std::cerr << "Error: too large number: " << value << std::endl;
		return(-1.0);
	}
	return (fnb);
}

void	process_line(std::string &line)
{
	float value;

	std::istringstream iss(line);
	std::string word[4];
	int i = 0;

	while (i < 4 && iss >> word[i++])
	{}
	if (i != 3)
	{
		std::cerr << "Wrong number of argument, usage: 'YYYY-MM-DD | {integer|decimal}'" << std::endl;
		return;
	}
	if (!check_date(word[0]))
	{
		std::cerr << "Error: bad input =>" << word[0] << std::endl;
		return;
	}
	if (word[1] != "|")
	{
		std::cerr << "Error: bad input =>" << word[0] << std::endl;
		return;
	}
	value = check_value(word[2]);
	if (value == -1.0)
		return;
}

void BitcoinExchange::parse(const std::string &filename) const
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	while (file)
	{
		if(!std::getline(file, line))
		{
			if (!file.eof())
				std::cerr << "Error: could not read file." << std::endl;
			return;
		}
		if (line.empty() || line[0] == '#')
			continue;
		process_line(line);
	}
	return;
}
