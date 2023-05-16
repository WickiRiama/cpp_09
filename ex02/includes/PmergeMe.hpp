/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:08:42 by mriant            #+#    #+#             */
/*   Updated: 2023/05/16 14:01:34 by mriant           ###   ########.fr       */
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
	std::list<int> _input_list;
	std::list<std::list<int> > _paired_list;
	std::list<int> _sorted_list;
	std::list<int> _insert_list;
	double _vector_time;
	double _list_time;

	bool parseInput(char **input);
	void setPairedVec(void);
	void setPairedList(void);
	void sortPair(std::vector<int> &vec);
	void sortPair(std::list<int> &list);
	void splitPairsVec(void);
	void splitPairsList(void);
	void sortVector(void);
	void sortList(void);
	void mergeSort(std::vector<std::vector<int> > &vec, size_t const left, size_t const right);
	void mergeSort(std::list<std::list<int> > &list, size_t const left, size_t const right);
	void merge(std::vector<std::vector<int> > &vec, size_t const left, size_t const middle, size_t const right);
	void merge(std::list<std::list<int> > &list, size_t const left, size_t const middle, size_t const right);
	void insertSortVec(void);
	void insertSortList(void);
	void jacobsthal(std::vector<int> &jacobsthal_vec, size_t n);
	void jacobsthal(std::list<int> &index_list, size_t n);
	void printVector(std::vector<int> const &vec) const;
	void printList(std::list<int> const &list) const;
	void printPairedVector(std::vector<std::vector<int> > const &vec) const;
	int getElement(std::list<int> const &list, size_t n);

};

#endif