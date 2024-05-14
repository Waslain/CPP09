/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:58:32 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/14 16:17:39 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
// Vous devez créer un programme qui affiche la valeur d’une certaine quantité de bitcoins
// à une certaine date.

// Ce programme doit utiliser une base de données au format CSV qui représentera le
// prix du bitcoin au fil du temps. Cette base de données est fournie avec le sujet.

// Le programme prendra en entrée une deuxième base de données stockant les différents
// prix / dates à évaluer.

// Votre programme doit respecter ces règles:
// • Le nom du programme est btc.
// • Votre programme doit prendre un fichier en argument.
// • Chaque ligne de ce fichier doit utiliser le format suivant: "date | valeur".
// • Une date valide sera toujours au format "Année-Mois-Jour" (YYYY-MM-DD).
// • Une valeur valide doit être soit un nombre à virgule flottante (float), ou un entier positif, compris entre 0 et 1000.

// Votre programme va utiliser la valeur dans votre fichier input.
// Votre programme doit affichier sur la sortie standard le résultat de la valeur multipliée
// par le taux de change en fonction de la date indiquée dans votre base de données.
// Si la date utilisée en entrée n’existe pas dans votre BD, alors vous
// devez utiliser la date la plus proche contenue dans votre BD. Soyez
// attentifs à utilser la date précédente la plus proche, et non la
// suivante.
bool	isFloat(const std::string &str);
bool	isDateValid(const std::string &str);

int couldGetCsvData(std::map<std::string, float> & csvData)
{
	std::ifstream file("data.csv");
	if (!file.is_open())
	{
		std::cerr << "Failed to open data.csv" << std::endl;
		return 1;
	}
	std::string line;
	std::getline(file, line);
	if (line.compare("date,exchange_rate") != 0) {
		std::cerr << "Error: invalid csv format" << std::endl;
		return 1;
	}
	//loop to get lines
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string tmp;
		std::string date;
		float rate;

		getline(stream, date, ',');
		getline(stream, tmp, ',');
		if (isFloat(tmp))
			rate = std::strtof(tmp.c_str(), NULL);
		if (isDateValid(date))
		{
			csvData[date] = rate;
		}
		else
		{
			std::cerr << "Error: invalid date or rate" << std::endl;
			return 1;
		}
	}
	file.close();
	return 0;
}

int btc(std::string file_name, std::map<std::string, float> &csvData)
{
	std::ifstream file(file_name.c_str());
	if (!file.is_open())
	{
		std::cerr << "Failed to open " << file_name << std::endl;
		return 1;
	}
	std::string line;
	std::getline(file, line);
	if (line.compare("date | value") != 0)
	{
		std::cerr << "Error: invalid input format" << std::endl;
		return 1;
	}
	//loop to get lines
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string tmp;
		std::string date;
		float value;

		getline(stream, date, '|');
		getline(stream, tmp, '|');
		if (isFloat(tmp))
		{
			value = std::strtof(tmp.c_str(), NULL);
		}
		if (isDateValid(date))
		{
			std::map<std::string, float>::iterator it = csvData.find(date);
			if (it != csvData.end())
			{
				if (value < 0 || value > 21000000)
					std::cerr << "Error: invalid value -> " << value << std::endl;
				else
					std::cout << date << " => " << value << " = " << value * it->second << std::endl;
			}
			else
			{
				std::map<std::string, float>::iterator it = csvData.lower_bound(date);
				if (it == csvData.begin())
				{
					std::cerr << "Error: invalid date or value" << std::endl;
				}
				else
				{
					if (value < 0 || value > 21000000)
						std::cerr << "Error: invalid value -> " << value << std::endl;
					else
					{
						--it;
						std::cout << date << " => " << value << " = " << value * it->second << std::endl;
					}
				}
			}
		}
		else
		{
			std::cerr << "Error: invalid date -> " << date << std::endl;
		}
	}
	// for (std::map<std::string, float>::iterator it = csvData.begin(); it != csvData.end(); ++it)
	// {
	// 	std::cout << it->first << " | " << it->second << std::endl;
	// }
	file.close(); 
	return 0;
}

// std::stof(str) check si str peut etre converti en float;

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::map<std::string, float> csvData;
		if (couldGetCsvData(csvData) == 1 || csvData.empty())
			return 1;
		std::string file_name(av[1]);
		if (btc(file_name, csvData) == 1)
			return 1;
	}
	else
	{
		std::cerr << "Wrong arg number" << std::endl;
		return 1;
	}
	return 0;
}
//Check if date is valid
bool	isDateValid(const std::string &str)
{
	// if (str.find(' ') != std::string::npos || str.find('	') != std::string::npos)
	// {
	// 	std::cout << "HERE" << std::endl;
	// 	return (false);
	// }
		
	std::string tmp;
	std::istringstream stream(str);
	int	year;
	int	month;
	int	day;

	getline(stream, tmp, '-');
	year = atoi(tmp.c_str());
	getline(stream, tmp, '-');
	month = atoi(tmp.c_str());
	getline(stream, tmp, '-');
	day = atoi(tmp.c_str());
	if (year < 2009 || year > 2024 || month < 1 || month > 12 || day < 1 || day > 31)
		return (false);
	if(month == 2)
	{
		if (day > 29)
			return (false);
		else if (day > 28 && (year % 400 != 0 && (year % 100 == 0 || year % 4 != 0)))
			return (false);
	}
	if (year == 2009)
		if (month == 1 && day < 2)
			return (false);
	// std::cout << "DATEVALID : " << year << month << day << std::endl;
	return (true);
}

//Check if the string is a Float number
bool	isFloat(const std::string &str) {

	if (str.size() == 0 || str[0] == '.')
		return (false);
	// if (str.find(' ') != std::string::npos || str.find('	') != std::string::npos)
	// 	return (false);

	char* endPtr;
	std::strtof(str.c_str(), &endPtr);

	return (*endPtr == '\0' || std::isspace(*endPtr) != 0);
}