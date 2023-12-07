/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:44:16 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 09:02:59 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char const **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: wrong ammount of arguments" << std::endl;
		return 1;
	}
	RPN rpn(argv[1]);
}

