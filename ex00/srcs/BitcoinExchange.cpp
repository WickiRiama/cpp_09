/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:10 by mriant            #+#    #+#             */
/*   Updated: 2023/05/05 18:36:18 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "BitcoinExchange.hpp"
#include "colors.h"

//==============================================================================
// Conctructors and Destructor
//==============================================================================

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(std::string const &file)
{
	setDatabase(file);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

//==============================================================================
// Operators
//==============================================================================

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
	{
		this->_database = rhs._database;
	}
	return *this;
}

//==============================================================================
// DataBase Functions
//==============================================================================

void BitcoinExchange::setDatabase(std::string const &file)
{
	std::ifstream myfile;
	std::string line;

	myfile.open(file.c_str());
	if (myfile.is_open())
	{
		getline(myfile, line);
		while(getline(myfile, line))
		{
			parseDataLine(line);
		}
		myfile.close();
	}
	else
		std::cerr << "Error: could not open file." << std::endl;
}

void BitcoinExchange::parseDataLine(std::string const &line)
{
	size_t pos = line.find(',', 0);
	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 1);
	_database[date] = atof(value.c_str());
}

//==============================================================================
// Input Functions
//==============================================================================

bool BitcoinExchange::isLeap(int year) const
{
	return ((year % 4 == 0 && year % 100 != 0) ||
			year % 400 == 0);
}

bool BitcoinExchange::checkDigits(std::string const & nb) const
{
	for (size_t i = 0; i < nb.size(); i++)
	{
		if (!isdigit(nb[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::checkFloatDigit(std::string const & nb) const
{
	int nb_points = 0;
	for (size_t i = 0; i < nb.size(); i++)
	{
		if (i == 0 && !isdigit(nb[i]) && nb[i] != '-')
			return false;
		else if (nb[i] == '.')
			nb_points++;
		else if (i != 0 && !isdigit(nb[i]))
			return false;
	}
	if (nb_points > 1)
		return false;
	return true;
}

bool BitcoinExchange::checkDate(std::string const &date) const
{
	size_t pos_year = date.find("-", 0);
	size_t pos_month = date.find("-", pos_year + 1);

	if (pos_year == std::string::npos || pos_month == std::string::npos)
		return false;

	std::string year_str = date.substr(0, pos_year).c_str();
	std::string month_str = date.substr(pos_year + 1, pos_month - pos_year - 1).c_str();
	std::string day_str = date.substr(pos_month + 1);
	if (!checkDigits(year_str) || !checkDigits(month_str) || !checkDigits(day_str))
		return false;

	int year, month, day;
	if (!(std::stringstream(year_str) >> year) ||
		!(std::stringstream(month_str) >> month) ||
		!(std::stringstream(day_str) >> day))
		return false;
	
	if (year < 0 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11) &&
		day > 31)
			return false;
	if (month == 2 && 
		((isLeap(year) && day > 29) || (!isLeap(year) && day > 28)))
		return false;

	return true;
}

bool BitcoinExchange::checkValue(std::string const &value_str) const
{
	if (!checkFloatDigit(value_str))
	{
		std::cout << "Error: bad input => " << value_str << std::endl;
		return false;
	}
	float value;
	if (!(std::stringstream(value_str) >> value))
	{
		if (value_str[0] == '-')
			std::cout << "Error: not a positive number." << std::endl;
		else
			std::cout << "Error: too large a number." << std::endl;
		return false;
	}
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large a number." << std::endl;
		return false;
	}

	return true;
}

bool BitcoinExchange::parseInputLine(std::string const &line, std::string *date, float *nb)
{
	size_t pos = line.find(" | ", 0);
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return false;
	}
	*date = line.substr(0, pos);
	std::string nb_str = line.substr(pos + 3);
	if (!checkDate(*date))
	{
		std::cout << "Error: bad input => " << *date << std::endl;
		return false;
	}
	if (!checkValue(nb_str))
		return false;
	
	*nb = atof(nb_str.c_str());
	return true;
}

void BitcoinExchange::printValue(std::string const &date, float const &nb) const
{
	std::map<std::string, float>::const_iterator it = _database.begin();
	while(it != _database.end() && date >= it->first)
	{
		it++;
	}
	if (it == _database.begin())
		std::cout << "Error: Database starts at " << _database.begin()->first << std::endl;
	else
	{
		it--;
		std::cout << date << " => " << nb << " = " << it->second * nb << std::endl;
	}
}

void BitcoinExchange::printDatedValues(std::string const &file)
{
	std::ifstream myfile;
	std::string line;
	std::string date;
	float nb;

	myfile.open(file.c_str());
	if(myfile.is_open())
	{
		getline(myfile, line);
		while(getline(myfile, line))
		{
			if (parseInputLine(line, &date, &nb))
				printValue(date, nb);
		}
		myfile.close();
	}
	else
		std::cerr << "Error: could not open file." << std::endl;
}
