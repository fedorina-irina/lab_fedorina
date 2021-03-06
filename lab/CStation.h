#pragma once
#include <iostream>
#include <fstream>
#include <string>

class CStation
{
	int csID;
public:
	static int MaxIDcs;
	std::string nameCStation;
	int shopCStation;
	int workshopCStation;
	int koefCStation;
	int STishoda = 0;
	int STzahoda = 0;

	int GetID() const;
	void SetID();
	static void EditStation(CStation& cs);

	friend std::ostream& operator << (std::ostream& out, const CStation& cs);
	friend std::istream& operator >> (std::istream& in, CStation& cs);
	friend std::ofstream& operator << (std::ofstream& out, const CStation& cs);
	friend std::ifstream& operator >> (std::ifstream& in, CStation& cs);
};

