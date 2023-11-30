/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:17:41 by asolano-          #+#    #+#             */
/*   Updated: 2023/11/30 11:46:34 by asolano-         ###   ########.fr       */
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

int	BitcoinExchange::parseFile(std::string infile)
{
	std::ifstream db_file(infile);
	std::string	line = "";
	std::string holder = "";
	std::tm	date{};
	double	rate;

	if (!db_file.is_open())
		return this->printError(0, "couldn't open database file");
	while (getline(db_file, line))
	{
		if (!checkInput(line))
			std::cerr << "Error - wrong input" << std::endl;
		else if (line.find_first_of(",") != line.npos || line.find_first_of(",") == line.find_last_of(","))
		{
			holder = line.substr(0, line.find_first_of(","));

			date.tm_year = atoi(line.substr(0,4).c_str()) - 1900;
			date.tm_mon = atoi(line.substr(6,2).c_str()) - 1;
			date.tm_mday = atoi(line.substr(8,2).c_str());
			date.tm_isdst = 0;
			date.tm_hour = 0;
			date.tm_min = 0;
			date.tm_sec = 0;
			rate = static_cast<float>(atof(line.substr(11).c_str()));
			this->db.insert(std::pair<time_t, double>(mktime(&date), rate));
		}
	}
}

int	BitcoinExchange::checkInput(std::string line) const
{
	int	i = 0;
	int	sign = 0;

	while (std::isdigit(line[i]))
		i++;
	if (i != 4)
		return (printError(1, line));
	if (line[i] != '-')
		return (this->printError(1, line));
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (i != 7)
		return (this->printError(1, line));
	if (line[i] != '-')
		return (this->printError(1, line));
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (i != 10)
		return (this->printError(1, line));
	if (line[i] != ' ')
		return (this->printError(1, line));
	i++;
	if (line[i] != '|')
		return (this->printError(1, line));
	i++;
	if (line[i] != ' ')
		return (this->printError(1, line));
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] == '-')
		sign = 1;
	i++;
	if (line.substr(i + sign).find_first_not_of("0123456789.") != std::string::npos || (line.substr(i + sign).find_first_of(".") != std::string::npos && (line.substr(i + sign).find_first_of(".") != line.substr(i + sign).find_last_of("."))))
		return (this->printError(1, line));
	return 0;
}

int	printError(int i, std::string s) const
{
	switch(i)
	{
		case 0:
			std::cout << "Error: " << s << std::endl;
			break;
		case 1:
			std::cout << "Error: bad input =>" << s << std::endl;
			break;
			
	}
	return 1;
}

/* if (line.find_first_of(" | ") != line.npos || line.find_first_of(" | ") == line.find_last_of(" | "))
		{
			date = line.substr(0, line.find_first_of(" | "));
			std::cout << date << std::endl;
		} */