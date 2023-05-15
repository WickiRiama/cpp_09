/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:08:42 by mriant            #+#    #+#             */
/*   Updated: 2023/05/15 11:15:55 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>

class PmergeMe
{
public:
	PmergeMe(void);
	PmergeMe(PmergeMe const &src);
	~PmergeMe(void);

	PmergeMe &operator=(PmergeMe const &rhs);

	void sort(char **input);

private:
	std::vector<int> _input_vec;
	std::vector<std::vector<int> > _paired_vec;
	std::vector<int> _sorted_vec;
	std::vector<int> _insert_vec;

	bool parseInput(char **input);
	void setPairedVec(void);
	void sortPair(std::vector<int> &vec);
	void splitPairs(void);
	void mergeSortVector(std::vector<std::vector<int> > &vec, size_t const left, size_t const right);
	void mergeVector(std::vector<std::vector<int> > &vec, size_t const left, size_t const middle, size_t const right);
	void insertSort(void);
	void jacobsthal(std::vector<int> &jacobsthal_vec, size_t n);
	void printVector(std::vector<int> const &vec) const;
	void printPairedVector(std::vector<std::vector<int> > const &vec) const;
};

#endif