/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:03 by mriant            #+#    #+#             */
/*   Updated: 2023/05/11 16:16:07 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <cstdlib>

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
		_paired_vec = rhs._paired_vec;
	}
	return *this;
}

//==============================================================================
// Sort Functions
//==============================================================================

void PmergeMe::sort(char **input)
{
// Parsing
	if (parseInput(input))
		return;
	std::cout << "Before:\t";
	printVector(_input_vec);
	std::cout << std::endl;
// 1 - Former paires
	setPairedVec();
// 2 - Trier chaque paire
// 3 - Trier les paires entres elle par plus grand élément > merge sort
// 4 - Extraire les plus petits éléments des paires
// 5 - Insérer les plus petits éléments à leur place Insert sort + binary search
}

bool PmergeMe::parseInput(char **input)
{
	int tmp;

	for (int i = 1; input[i]; i++)
	{
		std::stringstream ss(input[i]);
		ss >> tmp;
		if (ss.fail() || !ss.eof() || tmp < 0)
		{
			std::cout << "Error" << std::endl;
			return EXIT_FAILURE;
		}
		_input_vec.push_back(tmp);
	}
	return EXIT_SUCCESS;
}

void PmergeMe::setPairedVec(void)
{
	std::vector<int> tmp;
	
	if (_input_vec.size() < 1)
	{
		_paired_vec.clear();
		return;
	}
	for (size_t i = 0; i < _input_vec.size(); i++)
	{
		tmp.push_back(_input_vec[i]);
		if (i % 2 == 1 || i == _input_vec.size() - 1)
		{
			_paired_vec.push_back(tmp);
			tmp.clear();
		}
	}
}


//==============================================================================
// Utils Functions
//==============================================================================

void PmergeMe::printVector(std::vector<int> vec) const
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << " ";
	}
}

void PmergeMe::printPairedVector(std::vector<std::vector<int> > vec) const
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "[";
		printVector(vec[i]);
		std::cout << "]";
		if (i < vec.size() - 1)
			std::cout << " ";
	}
}
