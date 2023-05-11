/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:07:49 by mriant            #+#    #+#             */
/*   Updated: 2023/05/11 14:10:27 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "PmergeMe.hpp"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	PmergeMe pmerge;
	pmerge.sort(av[1]);
	return 0;
}