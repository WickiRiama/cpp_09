/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:04:02 by mriant            #+#    #+#             */
/*   Updated: 2023/05/10 17:45:54 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>

#include "RPN.hpp"

//==============================================================================
// Constructors and Destructor
//==============================================================================

RPN::RPN(void)
{
}

RPN::RPN(RPN const &src)
{
	*this = src;
}

RPN::~RPN(void)
{
}

//==============================================================================
// Operators
//==============================================================================

RPN &RPN::operator=(RPN const &rhs)
{
	if (&rhs != this)
	{
		_pile = rhs._pile;
	}
	return *this;
}

//==============================================================================
// Functions
//==============================================================================

void RPN::calculate(std::string operations)
{
	char operator_sign[] = {'+', '-', '*', '/'};
	size_t nb_operators = sizeof(operator_sign) / sizeof(operator_sign[0]);
	bool (RPN::*f[])(void) = {
		&RPN::plus,
		&RPN::minus,
		&RPN::times,
		&RPN::divide};
	if (operations.size() == 0)
	{
		std::cout << "Error" << std::endl;
		return;
	}
	for (size_t i = 0; i < operations.size(); i++)
	{
		if (operations[i] >= '0' && operations[i] <= '9')
			_pile.push(operations[i] - '0');
		else
		{
			size_t j = 0;
			while (j < nb_operators)
			{
				if (operations[i] == operator_sign[j])
				{
					if ((this->*f[j])())
						return ;
					else
						break;
				}
				j++;
			}
			if (j == nb_operators && operations[i] != ' ')
			{
				std::cout << "Error" << std::endl;
				return ;
			}
		}
	}
	printPile();
}

int RPN::getOperande(void)
{
	int operande = _pile.top();
	_pile.pop();
	return operande;
}


bool RPN::plus(void)
{
	if (_pile.size() < 2)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	int second_op = getOperande();
	int first_op = getOperande();
	int result = first_op + second_op;
	_pile.push(result);
	return EXIT_SUCCESS;
}

bool RPN::minus(void)
{
	if (_pile.size() < 2)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	int second_op = getOperande();
	int first_op = getOperande();
	int result = first_op - second_op;
	_pile.push(result);
	return EXIT_SUCCESS;
}

bool RPN::times(void)
{
	if (_pile.size() < 2)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	int second_op = getOperande();
	int first_op = getOperande();
	int result = first_op * second_op;
	_pile.push(result);
	return EXIT_SUCCESS;
}

bool RPN::divide(void)
{
	if (_pile.size() < 2)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	int second_op = getOperande();
	if (second_op == 0)
	{
		std::cout << "Error" << std::endl;
		return EXIT_FAILURE;
	}
	int first_op = getOperande();
	int result = first_op / second_op;
	_pile.push(result);
	return EXIT_SUCCESS;
}

void RPN::printPile(void)
{
	int pile_size = _pile.size();
	for (int i = 0; i < pile_size; i++)
	{
		std::cout << _pile.top();
		_pile.pop();
		if (i < pile_size - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}
