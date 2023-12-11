/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:12:15 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/11 10:33:23 by asolano-         ###   ########.fr       */
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

PmergeMe::PmergeMe(const char **arg)
{
	struct timeval tp;

	try
	{
		checkInput(arg);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		return ;
	}
	gettimeofday(&tp, NULL);
	timer[0] = tp.tv_sec * 1000000 + tp.tv_usec; //get current timestamp in microseconds
	setQue(arg);
	sortQue(this->que);
	gettimeofday(&tp, NULL);
	timer[1] = tp.tv_sec * 1000000 + tp.tv_usec;
	setVec(arg);
	sortVec(this->vec);
	gettimeofday(&tp, NULL);
	timer[2] = tp.tv_sec * 1000000 + tp.tv_usec;
	printData(arg);
}

void	PmergeMe::printData(const char **arg)
{
	//(void) arg;
	std::cout << "Before:  ";
	printArg(arg);
	std::cout << "After:  ";
	printQue();
	std::cout << "Time to process a range of " << que.size() << " elements: " << (timer[1] - timer[0]) << " us" << std::endl;
	std::cout << "Time to process a range of " << que.size() << " elements: " << (timer[2] - timer[1]) << " us" << std::endl;
}

void	PmergeMe::setQue(const char **arg)
{
	int i = 1;
	while (arg[i])
	{
		que.push_back(atoi(arg[i]));
		i++;
	}
}

void	PmergeMe::printArg(const char **arg)
{
	int i = 1;
	while (arg[i])
	{
		std::cout << atoi(arg[i]) << " ";
		i++;
	}
	std::cout << std::endl;
}

void	PmergeMe::setVec(const char **arg)
{
	int i = 1;
	while (arg[i])
	{
		vec.push_back(atoi(arg[i]));
		i++;
	}
}

void	PmergeMe::checkInput(const char **arg)
{
	int i = 1;
	int j = 0;
	while  (arg[i])
	{
		while (arg[i][j])
		{
			if (!isdigit(arg[i][j]))
				throw std::runtime_error("Error - wrong input");
			j++;
		}
		j = 0;
		i++;
	}
}

void	PmergeMe::printQue()
{
	unsigned long i = 0;
	while (i < que.size())
	{
		std::cout << que[i];
		if (i < que.size() - 1)
			std::cout << " ";
		i++;
	}
	std::cout << std::endl;
}

void	PmergeMe::printVec()
{
	int i = 0;
	while (vec[i])
	{
		std::cout << vec[i];
		if (vec[i + 1])
			std::cout << " ";
		i++;
	}
	std::cout << std::endl;
}

void PmergeMe::sortQue(std::deque<int> &que)
{
	std::deque<int> que1;
	std::deque<int> que2;
	int i = 0;
	int size = que.size();
	if (size >= 2)
	{
		while (i < size / 2)
		{
			que1.push_back(que.front());
			que.pop_front();
			i++;
		}
		while (i < size)
		{
			que2.push_back(que.front());
			que.pop_front();
			i++;
		}
		sortQue(que1);
		sortQue(que2);
		while (!que1.empty() || !que2.empty())
		{
			if (!que1.empty() && !que2.empty())
			{
				if (que1.front() < que2.front())
				{
					que.push_back(que1.front());
					que1.pop_front();
				}
				else
				{
					que.push_back(que2.front());
					que2.pop_front();
				}
			}
			else if (que1.empty())
			{
				que.push_back(que2.front());
				que2.pop_front();
			}
			else if (que2.empty())
			{
				que.push_back(que1.front());
				que1.pop_front();
			}
		}
	}
}

void PmergeMe::sortVec(std::vector<int> &vec)
{
	std::vector<int> vec1;
	std::vector<int> vec2;
	int i = 0;
	int size = vec.size();
	if (size >= 2)
	{
		while (i < size / 2)
		{
			vec1.push_back(vec.front());
			vec.erase(vec.begin());
			i++;
		}
		while (i < size)
		{
			vec2.push_back(vec.front());
			vec.erase(vec.begin());
			i++;
		}
		sortVec(vec1);
		sortVec(vec2);
		while (!vec1.empty() || !vec2.empty())
		{
			if (!vec1.empty() && !vec2.empty())
			{
				if (vec1.front() < vec2.front())
				{
					vec.push_back(vec1.front());
					vec1.erase(vec1.begin());
				}
				else
				{
					vec.push_back(vec2.front());
					vec2.erase(vec2.begin());
				}
			}
			else if (vec1.empty())
			{
				vec.push_back(vec2.front());
				vec2.erase(vec2.begin());
			}
			else if (vec2.empty())
			{
				vec.push_back(vec1.front());
				vec1.erase(vec1.begin());
			}
		}
	}
}

PmergeMe::~PmergeMe()
{
}