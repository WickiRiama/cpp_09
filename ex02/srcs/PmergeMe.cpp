/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:33:03 by mriant            #+#    #+#             */
/*   Updated: 2023/05/16 16:43:59 by mriant           ###   ########.fr       */
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
		_input_list = rhs._input_list;
		_paired_list = rhs._paired_list;
		_sorted_list = rhs._sorted_list;
		_insert_list = rhs._insert_list;
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
// Sort Vector
	sortVector();
	std::cout << "After:\t";
	printVector(_sorted_vec);
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _input_vec.size() << " elements with std::vector : " << _vector_time << " us" << std::endl;
//Sort List
	// std::cout << "Before:\t";
	// printList(_input_list);
	// std::cout << std::endl;
	sortList();
	// std::cout << "After:\t";
	// printList(_sorted_list);
	// std::cout << std::endl;
	std::cout << "Time to process a range of " << _input_list.size() << " elements with std::list : " << _list_time << " us" << std::endl;
}

void PmergeMe::sortVector(void)
{
	clock_t start = clock();
// 1 - Former paires et trier contenu
	setPairedVec();
// 3 - Trier les paires entres elle par plus grand élément > merge sort
	if (_paired_vec.size() > 0)
		mergeSort(_paired_vec, 0, _paired_vec.size() - 1);
// 4 - Extraire les plus petits éléments des paires
	splitPairsVec();
// 5 - Insérer le plus petit élément au début
	_sorted_vec.insert(_sorted_vec.begin(), _insert_vec[0]);
// 6 - Insérer les plus petits éléments à leur place Insert sort + binary search
	if (_insert_vec.size() > 1)
		insertSortVec();
	clock_t end = clock();
	_vector_time = static_cast<double>((end - start) * 1000000) / CLOCKS_PER_SEC;
}

void PmergeMe::sortList(void)
{
	clock_t start = clock();
// 1 - Former paires et trier contenu
	setPairedList();
// 3 - Trier les paires entres elle par plus grand élément > merge sort
	if (_paired_list.size() > 0)
		mergeSort(_paired_list, 0, _paired_list.size() - 1);
// 4 - Extraire les plus petits éléments des paires
	splitPairsList();
// 5 - Insérer le plus petit élément au début
	_sorted_list.insert(_sorted_list.begin(), _insert_list.front());
// 6 - Insérer les plus petits éléments à leur place Insert sort + binary search
	if (_insert_list.size() > 1)
		insertSortList();
	clock_t end = clock();
	_list_time = static_cast<double>((end - start) * 1000000) / CLOCKS_PER_SEC;
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
		_input_list.push_back(tmp);
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

void PmergeMe::setPairedList(void)
{
	std::list<int> tmp;
	
	if (_input_list.size() < 1)
	{
		_paired_list.clear();
		return;
	}
	size_t i = 0;
	for (std::list<int>::iterator it = _input_list.begin();
		 it != _input_list.end(); it++)
	{
		tmp.push_back(*it);
		if (i % 2 == 1 || i == _input_list.size() - 1)
		{
			sortPair(tmp);
			_paired_list.push_back(tmp);
			tmp.clear();
		}
		i++;
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

void PmergeMe::sortPair(std::list<int> &list)
{
	if (list.size() == 2 && list.front() > list.back())
	{
		int tmp = list.front();
		list.front() = list.back();
		list.back() = tmp;
	}
}

void PmergeMe::splitPairsVec(void)
{
	for (size_t i = 0; i < _paired_vec.size(); i++)
	{
		if (_paired_vec[i].size() == 2)
			_sorted_vec.push_back(_paired_vec[i][1]);
		_insert_vec.push_back(_paired_vec[i][0]);
	}
}

void PmergeMe::splitPairsList(void)
{
	for (std::list<std::list<int> >::iterator it = _paired_list.begin();
		 it != _paired_list.end(); it++)
	{
		if ((*it).size() == 2)
			_sorted_list.push_back((*it).back());
		_insert_list.push_back((*it).front());
	}
}

//==============================================================================
// Merge Sort Functions
//==============================================================================

void PmergeMe::mergeSort(std::vector<std::vector<int> > &vec, size_t const left, size_t const right)
{
	if (left >= right)
		return ;
	int middle = (left + right) / 2;
	mergeSort(vec, left, middle);
	mergeSort(vec, middle + 1, right);
	merge(vec, left, middle, right);
}

void PmergeMe::mergeSort(std::list<std::list<int> > &list, size_t const left, size_t const right)
{
	if (left >= right)
		return ;
	int middle = (left + right) / 2;
	mergeSort(list, left, middle);
	mergeSort(list, middle + 1, right);
	merge(list, left, middle, right);
}

void PmergeMe::merge(std::vector<std::vector<int> > &vec, size_t const left, size_t const middle, size_t const right)
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

void PmergeMe::merge(std::list<std::list<int> > &list, size_t const left, size_t const middle, size_t const right)
{
	std::list<std::list<int> > left_list;
	std::list<std::list<int> > right_list;
	std::list<std::list<int> >::iterator it = list.begin();
	std::list<std::list<int> >::iterator it_left;
	std::list<std::list<int> >::iterator it_right;

	for (size_t i = 1; i <= left; i++)
		it++;
	it_left = it;
	for (size_t i = left; i <= middle; i++)
	{
		left_list.push_back(*it);
		it++;
	}
	for (size_t i = middle + 1; i <= right; i++)
	{
		right_list.push_back(*it);
		it++;
	}
	it_right = it;

	for (it = it_left; it != it_right; it++)
	{
		if (left_list.size() != 0 &&
			(right_list.size() == 0 
			 || right_list.front().size() == 1 
			 || left_list.front().back() < right_list.front().back()))
		{
			*it = left_list.front();
			left_list.pop_front();
		}
		else
		{
			*it = right_list.front();
			right_list.pop_front();
		}
	}
}

//==============================================================================
// Insert Sort Functions
//==============================================================================

void PmergeMe::insertSortVec(void)
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

void PmergeMe::insertSortList(void)
{
	// generate Jacobsthal sequence
	std::list<int> index_list;
	jacobsthal(index_list, _insert_list.size());
	// insert with binary search
	for (size_t i = 1; i < index_list.size(); i++)
	{
		std::list<int>::iterator pos = lower_bound(_sorted_list.begin(), _sorted_list.end(), getElement(_insert_list, getElement(index_list, i)));
		if (pos == _sorted_list.end())
			_sorted_list.push_back(getElement(_insert_list, getElement(index_list, i)));
		else
			_sorted_list.insert(pos, getElement(_insert_list, getElement(index_list, i)));
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

	for (size_t i = 0; i < jacobsthal_vec.size() - 1; i++)
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

void PmergeMe::jacobsthal(std::list<int> &index_list, size_t n)
{
	std::list<int> jacobsthal_list;
	jacobsthal_list.push_back(0);
	jacobsthal_list.push_back(1);
	for (size_t i = 2; jacobsthal_list.size() < 2 || getElement(jacobsthal_list, i - 1) < static_cast<int>(n); i++)
		jacobsthal_list.push_back(getElement(jacobsthal_list, i - 1) + 2 * getElement(jacobsthal_list, i - 2));
	// std::cout << "Jacobsthal suit: ";
	// printVector(jacobsthal_vec);
	// std::cout << std::endl;

	for (size_t i = 0; i < jacobsthal_list.size() - 1; i++)
	{
		for (int j = getElement(jacobsthal_list, i + 1); j > getElement(jacobsthal_list, i); j--)
		{
			if (j - 1 < static_cast<int>(n))
				index_list.push_back(j - 1);
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
	for (size_t i = 0; i < vec.size() && i < 4; i++)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << " ";
	}
	if (vec.size() > 4)
		std::cout << "[...]";
}

void PmergeMe::printList(std::list<int> const &list) const
{
	std::list<int>::const_iterator it = list.begin();
	for (size_t i = 0; i < list.size() && i < 4; i++)
	{
		std::cout << *it;
		it++;
		if (i < list.size() - 1)
			std::cout << " ";
	}
	if (list.size() > 4)
		std::cout << "[...]";
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

int PmergeMe::getElement(std::list<int> const &list, size_t n)
{
	if (n > list.size())
	{
		std::cout << "Error: List has less than " << n << " elements" << std::endl;
		return -1;
	}
	std::list<int>::const_iterator it = list.begin();
	for (size_t i = 0; i < n; i++)
	{
		it++;
	}
	return *it;
}