/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:47 by mriant            #+#    #+#             */
/*   Updated: 2023/05/05 15:49:59 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange(std::string const &file);
	BitcoinExchange(BitcoinExchange const &src);
	~BitcoinExchange(void);

	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	void printDatedValues(std::string const &file);

private:
	BitcoinExchange(void);
	
	std::map<std::string, float> _database;
	int _start_year;
	int _current_year;

	void setCurrentYear(void);
	void setDatabase(std::string const &file);
	void parseDataLine(std::string const &line);
	void parseInputLine(std::string const &line);
	bool checkDate(std::string const &date) const;
	bool isLeap(int year) const;
	bool checkDigits(std::string const & nb) const;
	bool checkValue(std::string const &value) const;
};

#endif
