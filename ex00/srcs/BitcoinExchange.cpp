/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:10 by mriant            #+#    #+#             */
/*   Updated: 2023/04/28 17:06:34 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

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
	try
	{
		setDatabase(file);
	}
	catch (WrongDataFormatException &e)
	{
		std::cout << RED << e.what() << RES << std::endl;
		database.clear();
	}
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
		this->database = rhs.database;
	}
	return *this;
}

//==============================================================================
// Functions
//==============================================================================

void BitcoinExchange::setDatabase(std::string const &file)
{
	std::ifstream myfile;
	std::string line;

	myfile.open(file.c_str());
	if (myfile.is_open())
	{
		while(getline(myfile, line))
		{
			try
			{
				parseDataLine(line);
			}
			catch (WrongDataFormatException &e)
			{
				myfile.close();
				throw WrongDataFormatException();
			}
		}
		myfile.close();
	}
}

void BitcoinExchange::parseDataLine(std::string const &line)
{
	size_t pos = line.find(',', 0);
	if (pos == std::string::npos)
		throw WrongDataFormatException();
	std::string date = line.substr(0, pos);
	std::string value = line.substr(pos + 1);
	database[date] = atoi(value.c_str());
}
