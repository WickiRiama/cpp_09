/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:03 by mriant            #+#    #+#             */
/*   Updated: 2023/05/16 11:30:50 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

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
		_vector_time = rhs._vector_time;
		_list_time = rhs._list_time;
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
// Sort
	sortVector();
	std::cout << "After:\t";
	printVector(_sorted_vec);
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _input_vec.size() << " elements with std::vector : " << _vector_time << " us" << std::endl;
}

void PmergeMe::sortVector(void)
{
	clock_t start = clock();
// 1 - Former paires et trier contenu
	setPairedVec();
// 3 - Trier les paires entres elle par plus grand élément > merge sort
	if (_paired_vec.size() > 0)
		mergeSortVector(_paired_vec, 0, _paired_vec.size() - 1);
// 4 - Extraire les plus petits éléments des paires
	splitPairs();
// 5 - Insérer le plus petit élément au début
	_sorted_vec.insert(_sorted_vec.begin(), _insert_vec[0]);
	// _insert_vec.erase(_insert_vec.begin());
// 6 - Insérer les plus petits éléments à leur place Insert sort + binary search
	insertSort();
	clock_t end = clock();
	_vector_time = static_cast<double>((end - start) * 1000000) / CLOCKS_PER_SEC;
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

void PmergeMe::insertSort(void)
{
	// generate Jacobsthal sequence
	std::vector<int> index_vec;
	jacobsthal(index_vec, _insert_vec.size());
	// insert with binary search
	for (size_t i = 1; i < index_vec.size(); i++)
	{
		std::vector<int>::iterator pos = lower_bound(_sorted_vec.begin(), _sorted_vec.end(), _insert_vec[index_vec[i]]);
		if (pos == _sorted_vec.end())
			_sorted_vec.push_back(_insert_vec[index_vec[i]]);
		else
			_sorted_vec.insert(pos, _insert_vec[index_vec[i]]);
	}
}

void PmergeMe::jacobsthal(std::vector<int> &index_vec, size_t n)
{
	std::vector<int> jacobsthal_vec;
	jacobsthal_vec.push_back(0);
	jacobsthal_vec.push_back(1);
	for (size_t i = 2; jacobsthal_vec.size() < 2 || jacobsthal_vec[i - 1] < static_cast<int>(n); i++)
		jacobsthal_vec.push_back(jacobsthal_vec[i - 1] + 2 * jacobsthal_vec[i - 2]);
	// std::cout << "Jacobsthal suit: ";
	// printVector(jacobsthal_vec);
	// std::cout << std::endl;

	for (size_t i = 0; i < jacobsthal_vec.size(); i++)
	{
		for (int j = jacobsthal_vec[i + 1]; j > jacobsthal_vec[i]; j--)
		{
			if (j - 1 < static_cast<int>(n))
				index_vec.push_back(j - 1);
		}
	}
	// std::cout << "Index sequence suit: ";
	// printVector(index_vec);
	// std::cout << std::endl;

}

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
