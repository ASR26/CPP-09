/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:17:41 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/07 09:59:59 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string infile)
{

	this->parseDatabase();
	this->parseFile(infile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	db = copy.db;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	db = copy.db;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

int	BitcoinExchange::parseDatabase()
{
	std::ifstream db_file("data.csv");
	std::string	line = "";
	std::tm	date;
	int	i = 0;
	double	rate;

	if (!db_file.is_open())
		return this->printError(4,"");
	while (getline(db_file, line))
	{
		if (i != 0 && checkDatabase(line))
			;
		else if ((line.find_first_of(",") != line.npos || line.find_first_of(",") == line.find_last_of(",")) && i != 0)
		{
			date.tm_year = atoi(line.substr(0,4).c_str()) - 1900;
			date.tm_mon = atoi(line.substr(5,2).c_str()) - 1;
			date.tm_mday = atoi(line.substr(8,2).c_str());
			date.tm_isdst = 0;
			date.tm_hour = 0;
			date.tm_min = 0;
			date.tm_sec = 0;
			rate = static_cast<float>(atof(line.substr(11).c_str()));
			this->db.insert(std::pair<time_t, double>(mktime(&date), rate));
		}
		i++;
	}
	return 0;
}

int	BitcoinExchange::checkDate(std::tm date)
{
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (date.tm_mon + 1 < 1 || date.tm_mon + 1 > 12)
		return (this->printError(5, "month"));
	if (date.tm_mday < 1 || date.tm_mday > days[date.tm_mon])
		return (this->printError(5, "day"));
	return 0;
}

int	BitcoinExchange::checkRate(double rate)
{
	if (rate < 0)
		return (this->printError(0,""));
	else if (rate > 2147483647)
		return (this->printError(2,""));
	return 0;
}

int	BitcoinExchange::parseFile(std::string infile)
{
	std::ifstream db_file(infile);
	std::string	line = "";
	std::tm	date;
	int	i = 0;
	double	rate;

	if (!db_file.is_open())
		return this->printError(4,"");
	while (getline(db_file, line))
	{
		if (i != 0 && checkInput(line))
			;
		else if ((line.find_first_of(",") != line.npos || line.find_first_of(",") == line.find_last_of(",")) && i > 0)
		{
			date.tm_year = atoi(line.substr(0,4).c_str()) - 1900;
			date.tm_mon = atoi(line.substr(5,2).c_str()) - 1;
			date.tm_mday = atoi(line.substr(8,2).c_str());
			date.tm_isdst = 0;
			date.tm_hour = 0;
			date.tm_min = 0;
			date.tm_sec = 0;
			rate = static_cast<float>(atof(line.substr(13).c_str()));
			if (rate > 1000)
				this->printError(2,"");
			else if (rate < 0)
				this->printError(0,"");
			else if (!this->checkDate(date) && !this->checkRate(rate))
				printOutput(date, rate);
		}
		i++;
	}
	return 0;
}

void	BitcoinExchange::printOutput(std::tm date, double rate)
{
	std::map<time_t, double>::iterator	it = db.begin();
	time_t time = mktime(&date);
	if (time < it->first)
	{
		this->printError(6,"");
		return ;
	}
	while (time >= it->first)
		it++;
	if (it != db.begin())
		it--;
	std::cout << date.tm_year + 1900 << "-";
	if (date.tm_mon + 1 < 10)
		std::cout << "0";
	std::cout << date.tm_mon + 1 << "-";
	if (date.tm_mday < 10)
		std::cout << "0";
	std::cout << date.tm_mday << " => " << rate << " = " << rate * it->second << std::endl;
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
	{	
		sign = 1;
		i++;
	}
	if (line.substr(i + sign).find_first_not_of("0123456789.") != std::string::npos || 
	 (line.substr(i + sign).find_first_of(".") != std::string::npos && (line.substr(i + sign).find_first_of(".") != line.substr(i + sign).find_last_of("."))))
		return (this->printError(1, line));
	return 0;
}

int	BitcoinExchange::checkDatabase(std::string line) const
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
	if (line[i] != ',')
		return (this->printError(1, line));
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] == '-')
	{
		sign = 1;
		i++;
	}
	if (line.substr(i + sign).find_first_not_of("0123456789.") != std::string::npos || 
	 (line.substr(i + sign).find_first_of(".") != std::string::npos && (line.substr(i + sign).find_first_of(".") != line.substr(i + sign).find_last_of("."))))
		return (this->printError(1, line));
	return 0;
}

int	BitcoinExchange::printError(int i, std::string s) const
{
	switch(i)
	{
		case 0:
			std::cout << "Error: not a positive number" << std::endl;
			break;
		case 1:
			std::cout << "Error: bad input => " << s << std::endl;
			break;
		case 2:
			std::cout << "Error: too large number" << std::endl;
			break;
		case 3:
			std::cout << "Error: couldn't open file" << std::endl;
			break;
		case 4:
			std::cout << "Error: couldn't open database file" << std::endl;
			break;
		case 5:
			std::cout << "Error: wrong " << s << std::endl;
			break;
		case 6:
			std::cout << "Error: no information on this date " << std::endl;
			break;
	}
	return 1;
}

