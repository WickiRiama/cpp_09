/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:08:42 by mriant            #+#    #+#             */
/*   Updated: 2023/05/11 13:39:23 by mriant           ###   ########.fr       */
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

	void sort(std::string input);

private:
	std::vector<int> _input_vec;
};

#endif