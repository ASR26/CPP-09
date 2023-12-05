/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolano- <asolano-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:17:45 by asolano-          #+#    #+#             */
/*   Updated: 2023/12/05 09:22:39 by asolano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <map>
class  BitcoinExchange
{
	private:
		std::map<time_t, double> db;
	public:
		BitcoinExchange();
		BitcoinExchange(std::string infile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);
		~BitcoinExchange();
		
		int parseFile(std::string infile);
		int parseDatabase();
		int	checkDate(std::tm date);
		int	checkRate(double rate);
		int checkInput(std::string line) const;
		int checkDatabase(std::string line) const;
		int printError(int i, std::string s) const;
		void printOutput(std::tm date, double rate);
};


#endif