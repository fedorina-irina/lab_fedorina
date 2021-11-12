#pragma once
#include <iostream>
#include <string>

class CStation
{
public:
	static int MaxIDcs;
	int idCStation;
	std::string nameCStation;
	int shopCStation;
	int workshopCStation;
	int koefCStation;

	CStation();

	friend std::ostream& operator << (std::ostream& out, const CStation& cs);
	friend std::istream& operator >> (std::istream& in, CStation& cs);
};

