/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:12:34 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/11 08:32:08 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char const **argv)
{
	if (argc < 2)
	{
		std::cout << "Error - wrong number of arguments" << std::endl;
		return -1;
	}
	PmergeMe a(argv);
	return 0;
}
