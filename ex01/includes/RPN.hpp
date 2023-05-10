/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:00:45 by mriant            #+#    #+#             */
/*   Updated: 2023/05/10 17:19:51 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
	public:
		RPN(void);
		RPN(RPN const &src);
		~RPN(void);

		RPN &operator=(RPN const &rhs);
	
		void calculate(std::string operations);

	private:

		std::stack<int> _pile;

		bool plus(void);
		bool minus(void);
		bool times(void);
		bool divide(void);
		int getOperande(void);
		void printPile(void);

};

#endif