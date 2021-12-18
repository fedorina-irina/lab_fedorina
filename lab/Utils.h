#pragma once
#include <iostream>
#include <unordered_map>


template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail() || x < min || x > max || (x - int(x)) != 0 || (char(std::cin.peek()) == '.') || (char(std::cin.peek()) == ','))
	{

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "ERROR! Type number (" << min << " - " << max << "): ";
	}
	return x;
}

template <typename T>

int Proverka(std::unordered_map<int, T>& map ,std::string textIN, std::string textError, int min, int max, int NEravno)
{
	int x;
	std::cout << textIN;
	while ((std::cin >> x).fail() || x < min || x > max || x == NEravno)
	{

		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << textError << "\n";
		if (map.count(x) == 0)
			std::cout << "ERROR! There is no object with this id\n";
	}

	return x;
}