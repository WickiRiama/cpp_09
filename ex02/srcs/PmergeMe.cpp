/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:03 by mriant            #+#    #+#             */
/*   Updated: 2023/05/11 18:07:33 by mriant           ###   ########.fr       */
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
		_sorted_vec = rhs._sorted_vec;
		_insert_vec = rhs._insert_vec;
	}
	return *this;
}

//==============================================================================
// Sort Function
//==============================================================================

void PmergeMe::sort(char **input)
{
// Parsing
	if (parseInput(input))
		return;
	std::cout << "Before:\t";
	printVector(_input_vec);
	std::cout << std::endl;
// 1 - Former paires et trier contenu
	setPairedVec();
	std::cout << "Pairs before:\t";
	printPairedVector(_paired_vec);
	std::cout << std::endl;
// 3 - Trier les paires entres elle par plus grand élément > merge sort
	if (_paired_vec.size() > 0)
		mergeSortVector(_paired_vec, 0, _paired_vec.size() - 1);
	std::cout << "Pairs after:\t";
	printPairedVector(_paired_vec);
	std::cout << std::endl;
// 4 - Extraire les plus petits éléments des paires
	splitPairs();
	std::cout << "Sorted vec before insert: ";
	printVector(_sorted_vec);
	std::cout << std::endl << "Insert vec before insert: ";
	printVector(_insert_vec);
	std::cout << std::endl;
// 5 - Insérer les plus petits éléments à leur place Insert sort + binary search
	_sorted_vec.insert(_sorted_vec.begin(), _insert_vec[0]);
	_insert_vec.erase(_insert_vec.begin());
	std::cout << "Sorted vec after insert: ";
	printVector(_sorted_vec);
	std::cout << std::endl << "Insert vec after insert: ";
	printVector(_insert_vec);
	std::cout << std::endl;

}

//==============================================================================
// Parsing and DataManagement Functions
//==============================================================================

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
			sortPair(tmp);
			_paired_vec.push_back(tmp);
			tmp.clear();
		}
	}
}

void PmergeMe::sortPair(std::vector<int> &vec)
{
	if (vec.size() == 2 && vec[0] > vec[1])
	{
		int tmp = vec[0];
		vec[0] = vec[1];
		vec[1] = tmp;
	}
}

void PmergeMe::splitPairs(void)
{
	for (size_t i = 0; i < _paired_vec.size(); i++)
	{
		if (_paired_vec[i].size() == 2)
			_sorted_vec.push_back(_paired_vec[i][1]);
		_insert_vec.push_back(_paired_vec[i][0]);
	}
}

//==============================================================================
// Merge Sort Functions
//==============================================================================

void PmergeMe::mergeSortVector(std::vector<std::vector<int> > &vec, size_t const left, size_t const right)
{
	if (left >= right)
		return ;
	int middle = (left + right) / 2;
	mergeSortVector(vec, left, middle);
	mergeSortVector(vec, middle + 1, right);
	mergeVector(vec, left, middle, right);
}

void PmergeMe::mergeVector(std::vector<std::vector<int> > &vec, size_t const left, size_t const middle, size_t const right)
{
	std::vector<std::vector<int> > left_vec;
	std::vector<std::vector<int> > right_vec;

	for (size_t i = left; i <= middle; i++)
		left_vec.push_back(vec[i]);
	for (size_t i = middle + 1; i <= right; i++)
		right_vec.push_back(vec[i]);

	for (size_t i = left; i <= right; i++)
	{
		if (left_vec.size() != 0 &&
			(right_vec.size() == 0 || right_vec[0].size() == 1 || left_vec[0][1] < right_vec[0][1]))
		{
			vec[i] = left_vec[0];
			left_vec.erase(left_vec.begin());
		}
		else
		{
			vec[i] = right_vec[0];
			right_vec.erase(right_vec.begin());
		}
	}
}

//==============================================================================
// Insert Sort Functions
//==============================================================================



//==============================================================================
// Utils Functions
//==============================================================================

void PmergeMe::printVector(std::vector<int> const &vec) const
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << " ";
	}
}

void PmergeMe::printPairedVector(std::vector<std::vector<int> > const &vec) const
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
