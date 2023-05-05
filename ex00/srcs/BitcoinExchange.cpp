/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:10 by mriant            #+#    #+#             */
/*   Updated: 2023/05/05 16:06:21 by mriant           ###   ########.fr       */
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
	setCurrentYear();
	_start_year = _current_year;
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
		this->_start_year = rhs._start_year;
		this->_current_year = rhs._current_year;
	}
	return *this;
}

//==============================================================================
// DataBase Functions
//==============================================================================

void BitcoinExchange::setCurrentYear(void)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	_current_year = ltm->tm_year + 1900;
}


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
	int year = atoi(line.substr(0, 4).c_str());
	_database[date] = atoi(value.c_str());
	if (year < _start_year)
	{
		_start_year = year;
	}
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

bool BitcoinExchange::checkDate(std::string const &date) const
{
	size_t pos_year = date.find("-", 0);
	size_t pos_month = date.find("-", pos_year + 1);

	if (pos_year == std::string::npos || pos_month == std::string::npos)
		return false;

	std::string year_str = date.substr(0, pos_year).c_str();
	std::string month_str = date.substr(pos_year + 1, pos_month - pos_year - 1).c_str();
	std::string day_str = date.substr(pos_month + 1, date.size()).c_str();
	if (!checkDigits(year_str) || !checkDigits(month_str) || !checkDigits(day_str))
		return false;

	std::stringstream ss(year_str);
	int year, month = 0, day = 0;
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

bool BitcoinExchange::checkValue(std::string const &value) const
{
	(void) value;
	return true;
}

void BitcoinExchange::parseInputLine(std::string const &line)
{
	size_t pos = line.find(" | ", 0);
	if (pos == std::string::npos)
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return;
	}
	std::string date = line.substr(0, pos);
	std::string nb = line.substr(pos + 3);
	if (!checkDate(date))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return;
	}
	if (!checkValue(nb))
		return;
}

void BitcoinExchange::printDatedValues(std::string const &file)
{
	std::ifstream myfile;
	std::string line;

	myfile.open(file.c_str());
	if(myfile.is_open())
	{
		getline(myfile, line);
		while(getline(myfile, line))
		{
			parseInputLine(line);
		}
		myfile.close();
	}
	else
		std::cerr << "Error: could not open file." << std::endl;
}
