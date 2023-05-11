/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:03 by mriant            #+#    #+#             */
/*   Updated: 2023/05/11 13:41:45 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//==============================================================================
// Constructors and Destructor
//==============================================================================

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(PmergeMe const &src)
{
	*this = src;
}

PmergeMe::~PmergeMe(void)
{
}

//==============================================================================
// Operators
//==============================================================================

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs)
{
	if (this != &rhs)
	{
		_input_vec = rhs._input_vec;
	}
	return *this;
}

//==============================================================================
// Functions
//==============================================================================

void PmergeMe::sort(std::string input)
{
// parsing
// 1 - Former paires
// 2 - Trier chaque paire
// 3 - Trier les paires entres elle par plus grand élément > merge sort
// 4 - Extraire les plus petits éléments des paires
// 5 - Insérer les plus petits éléments à leur place Insert sort + binary search
}
