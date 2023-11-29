/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:17:41 by asolano-          #+#    #+#             */
/*   Updated: 2023/11/29 11:56:52 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange:: BitcoinExchange()
{
}

BitcoinExchange:: BitcoinExchange(std::string infile)
{
	this->parseFile(infile);
}

BitcoinExchange::~ BitcoinExchange()
{
}

void	BitcoinExchange::parseFile(std::string infile)
{
	std::ifstream db_file(infile);
	std::string	line = "";
	std::string holder = "";
	std::tm	date;
	//double	rate;

	if (!db_file.is_open())
	{
		std::cerr << "Error couldn't open database file" << std::endl;
		return ;
	}
	while (getline(db_file, line))
	{
		if (!checkInput(line))
		{
			std::cerr << "Error - wrong input" << std::endl;
			break;
		}
		if (line.find_first_of(",") != line.npos || line.find_first_of(",") == line.find_last_of(","))
		{
			holder = line.substr(0, line.find_first_of(","));
			std::stringstream<char> stream(holder);
			//ss >> std::get_time(&date, "%Y-%m-%d");
			std::cout << date << std::endl;
		}
	}
}

int	BitcoinExchange::checkInput(std::string line)
{
	int	i = 0;
	int	sign = 0;

	while (std::isdigit(line[i]))
		i++;
	if (i != 4)
		return -1;
	if (line[i] != '-')
		return -1;
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (i != 7)
		return -1;
	if (line[i] != '-')
		return -1;
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (i != 10)
		return -1;
	if (line[i] != ' ')
		return -1;
	i++;
	if (line[i] != '|')
		return -1;
	i++;
	if (line[i] != ' ')
		return -1;
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] == '-')
		sign = 1;
	i++;
	
}

/* if (line.find_first_of(" | ") != line.npos || line.find_first_of(" | ") == line.find_last_of(" | "))
		{
			date = line.substr(0, line.find_first_of(" | "));
			std::cout << date << std::endl;
		} */