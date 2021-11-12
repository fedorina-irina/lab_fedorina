#pragma once
#include <iostream>


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