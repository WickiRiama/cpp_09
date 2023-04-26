/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:18:10 by mriant            #+#    #+#             */
/*   Updated: 2023/04/26 11:41:03 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//==============================================================================
// Conctructors and Destructor
//==============================================================================

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src);
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
	return this;
}

//==============================================================================
// Functions
//==============================================================================
