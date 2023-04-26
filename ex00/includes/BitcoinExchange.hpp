/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:08:47 by mriant            #+#    #+#             */
/*   Updated: 2023/04/26 11:29:45 by mriant           ###   ########.fr       */
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
	BitcoinExchange(BitcoinExchange const &src);
	~BitcoinExchange(void);

	BitcoinExchange &operator=(BitcoinExchange const &rhs);

private:
	std::map<std::string, float> database;
};

#endif
