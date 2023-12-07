/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:12:13 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 11:53:28 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>


class PmergeMe
{
	private:
		std::vector<int> vec;
		std::deque<int> que;
		time_t timers[4];
	public:
		PmergeMe();
		PmergeMe(char **arg);
		PmergeMe(const PmergeMe &copy);
		PmergeMe &operator=(const PmergeMe &copy);
		~PmergeMe();

		void setQue(char **arg);
		void setVec(char **arg);
		void checkInput(char **arg);
};

