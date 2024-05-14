/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fduzant <fduzant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:38:38 by fduzant           #+#    #+#             */
/*   Updated: 2024/05/11 18:47:51 by fduzant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <climits>

/* *****************************MERGE INSERT********************************* */
const int k = 5;

template <typename T>
void insertionSort(T &container, int p, int q)
{
	for (int i = p; i < q; i++) {
		int tempVal = container[i + 1];
		int j = i + 1;

		while (j > p && container[j - 1] > tempVal)
		{
			container[j] = container[j - 1];
			j--;
		}
		container[j] = tempVal;
	}
}

template <typename T>
void merge(T &container, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	T leftSub(container.begin() + p, container.begin() + q + 1);
	T rightSub(container.begin() + q + 1, container.begin() + r + 1);

	int rightId = 0;
	int leftId = 0;

	for (int i = p; i <= r; i++)
	{
		if (rightId == n2)
		{
			container[i] = leftSub[leftId];
			leftId++;
		}
		else if (leftId == n1)
		{
			container[i] = rightSub[rightId];
			rightId++;
		}
		else if (rightSub[rightId] > leftSub[leftId])
		{
			container[i] = leftSub[leftId];
			leftId++;
		}
		else
		{
			container[i] = rightSub[rightId];
			rightId++;
		}
	}
}

template <typename T>
void sort(T &container, int p, int r, int k)
{
	if (r - p > k)
	{
		int q = (p + r) / 2;
		sort(container, p, q, k);
		sort(container, q + 1, r, k);
		merge(container, p, q, r);
	}
	else
	{
		insertionSort(container, p, r);
	}
}

/* *******************************DISPLAY************************************ */

template <typename T>
void printContainer(const T &container, const char name[])
{
	std::cout << name;
	for (size_t i = 0; i < container.size(); i++)
	{
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
}

void printElapsedTime(double time, int nb, const char name[])
{
	std::cout << "Time to sort " << nb << " elements with " << name << " : " << time << "us" << std::endl;
}

template <typename T>
double getSortTime(T &container)
{
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	sort(container, 0, container.size() - 1, k);
	clock_gettime(CLOCK_MONOTONIC, &end);

	long long elapsedNano = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);

	return (static_cast<double>(elapsedNano) / 1000);
}

/* *******************************PARSING************************************ */

void parseAndStoreNumbers(const char *str, std::vector<int> &nbVector, std::deque<int> &nbDeque)
{
	char *endptr;
	long nb = strtol(str, &endptr, 10);

	if (*endptr != '\0' || nb < 0 || nb > INT_MAX)
	{
		throw std::invalid_argument("Invalid number");
	}
	nbVector.push_back(static_cast<int>(nb));
	nbDeque.push_back(static_cast<int>(nb));
}

/* *******************************UTILS************************************** */
template <typename T>
void isSorted(const T &container, const char name[])
{
	T sortedCopy = container;
	std::sort(sortedCopy.begin(), sortedCopy.end());

	if (sortedCopy == container)
	{
		std::cout << name << " is sorted" << std::endl;
	}
	else
	{
		std::cout << name << " is not sorted" << std::endl;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: not enough args" << std::endl;
		return (1);
	}
	
	int nb = argc - 1;

	std::vector<int> nbVector;
	std::deque<int> nbDeque;

	try {
		for (int i  = 1; i < argc; ++i){
			parseAndStoreNumbers(argv[i], nbVector, nbDeque);
		}
	}
	catch (const std::invalid_argument &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (2);
	}

	printContainer(nbDeque, "Before: ");

	double vectorTime = getSortTime(nbVector);
	double dequeTime = getSortTime(nbDeque);

	printContainer(nbVector, "After: ");

	isSorted(nbVector, "vector");
	isSorted(nbDeque, "deque");

	printElapsedTime(vectorTime, nb, "vector");
	printElapsedTime(dequeTime, nb, "deque");

	return (0);

}