/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:47 by mriant            #+#    #+#             */
/*   Updated: 2023/04/28 16:54:32 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
	BitcoinExchange(void);
	BitcoinExchange(std::string const &file);
	BitcoinExchange(BitcoinExchange const &src);
	~BitcoinExchange(void);

	BitcoinExchange &operator=(BitcoinExchange const &rhs);

	void setDatabase(std::string const &file);
	void parseDataLine(std::string const &line);

private:
	std::map<std::string, float> database;

public:
	class WrongDataFormatException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return "Data format must be `date,value`";
		}
	};

};

#endif
