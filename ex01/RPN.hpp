/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:40:30 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 09:08:03 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<float> st;
	public:
		RPN();
		RPN(std::string arg);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &copy);
		~RPN();

		void	checkInput(std::string str);
		void	processInput(std::string str);
		float	operate(char c, float a, float b);
};



#endif