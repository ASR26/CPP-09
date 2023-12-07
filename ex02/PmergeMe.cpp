/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:12:15 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 11:56:17 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	vec = copy.vec;
	que = copy.que;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
	vec = copy.vec;
	que = copy.que;
	return *this;
}

PmergeMe::PmergeMe(char **arg)
{
	timers[0]
	try
	{
		checkInput(arg);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	setQue(arg);

}

void	PmergeMe::setQue(char **arg)
{
	int i = 1;
	while (arg[i])
	{
		que.push_back(atoi(arg[i]));
		i++;
	}
}

void	PmergeMe::setVec(char **arg)
{
	int i = 1;
	while (arg[i])
	{
		vec.push_back(atoi(arg[i]));
		i++;
	}
}


void	PmergeMe::checkInput(char **arg)
{
	int i = 1;
	int j = 0;
	while  (arg[i])
	{
		while (arg[i][j])
		{
			if (!isdigit(arg[i][j]))
				throw std::runtime_error("Error - wrong input");
			if (j > 0)
				throw std::runtime_error("Error - wrong input");
			j++;
		}
		j = 0;
		i++;
	}
}

PmergeMe::~PmergeMe()
{
}