/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:10 by mriant            #+#    #+#             */
/*   Updated: 2023/05/05 11:54:04 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>

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
// Functions
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
