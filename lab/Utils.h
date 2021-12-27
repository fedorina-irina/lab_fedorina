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


//int CheckPipe(std::unordered_map<int, Pipe>& pipeline, std::string textIN, std::string textError1, std::string textError2)
//{
//	int x;
//	std::cout << textIN;
//	while (pipeline.count(x) == 0 || pipeline[x].CSidIN == 0)
//	{
//		std::cin.clear();
//		std::cin.ignore(10000, '\n');
//		if (pipeline.count(x) == 0)
//			std::cout << textError1 << "\n";
//		if (pipeline[x].CSidIN == 0)
//			std::cout << textError2 <<"\n";
//	}
//
//	return x;
//}

//int CheckCS(unordered_map<int, CStation>& CSSistem, string textIN, string textError1, string textError2)
//{
//	int x;
//	std::cout << textIN;
//	while (CSSistem.count(x) == 0 || (CSSistem[x].STishoda == 0 && CSSistem[x].STzahoda == 0))
//	{
//		std::cin.clear();
//		std::cin.ignore(10000, '\n');
//		if (CSSistem.count(x) == 0)
//			std::cout << textError1 << "\n";
//		if (CSSistem[x].STishoda == 0 && CSSistem[x].STzahoda == 0)
//			std::cout << textError2 << "\n";
//	}
//
//	return x;
//}