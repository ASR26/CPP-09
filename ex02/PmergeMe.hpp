/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:12:13 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/11 10:16:29 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>

class PmergeMe
{
	private:
		std::vector<int> vec;
		std::deque<int> que;
		unsigned long timer[3];
	public:
		PmergeMe();
		PmergeMe(const char **arg);
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &copy);
		~PmergeMe();

		void setQue(const char **arg);
		void setVec(const char **arg);
		void checkInput(const char **arg);
		void printQue();
		void printVec();
		void sortQue(std::deque<int> &que);
		void sortVec(std::vector<int> &vec);
		void printData(const char **arg);
		void printArg(const char **arg);
};

