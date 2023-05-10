/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:04:47 by mriant            #+#    #+#             */
/*   Updated: 2023/05/10 17:39:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>

#include "RPN.hpp"

int main(int ac, char** av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}

	RPN rpn;
	rpn.calculate(av[1]);
	return EXIT_SUCCESS;
}