#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

using namespace std;

int CStation::MaxIDcs = 0;

int CStation::GetID() const
{
	return csID;
}

void CStation::SetID()
{
	csID = ++MaxIDcs;
}

void CStation:: EditStation(CStation& cs)
{
	cout << "Do you want to launch another workshop or to stop one workshop? (1 - launch / 0 - stop) :\n";
	if (GetCorrectNumber(0, 1) == 1)
	{
		if (cs.workshopCStation < cs.shopCStation)
			cs.workshopCStation++;
		else cout << "You can't do this";
	}

	else
	{
		if (cs.workshopCStation > 0)
			cs.workshopCStation--;
		else cout << "You can't do this";
	}
}

ostream& operator << (ostream& out, const CStation& cs)
{
	out << "\nCompressor Station's id: " << cs.csID
		 << "\nCompressor Station's name: " << cs.nameCStation
		<< "\nCompressor Station's shops: " << cs.shopCStation
		<< "\nCompressor Station's workshops: " << cs.workshopCStation
		<< "\nCompressor Station's efficiency indicator: " << cs.koefCStation 
		<< "\nCompressor Station's degree of outcome: " << cs.STishoda
		<< "\nCompressor Station's degree of income: " << cs.STzahoda << endl;
	return out;
}

istream& operator >> (istream& in, CStation& cs)
{
	cs.SetID();

	cout << "Input compressor station's name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, cs.nameCStation);

	cout << "How many shops at the compressor station? (1 - 10): ";
	cs.shopCStation = GetCorrectNumber(1, 10);

	cout << "How many workshops at the compressor station? ";
	cs.workshopCStation = GetCorrectNumber(0, cs.shopCStation);


	cout << "Input compressor station's efficiency indicator [%], please: ";
	cs.koefCStation = GetCorrectNumber(0, 100);

	cs.STishoda = 0;
	cs.STzahoda = 0;

	return in;
}

ofstream& operator << (ofstream& out, const CStation& cs)
{
	out << cs.GetID() << endl
		<< cs.nameCStation << endl
		<< cs.shopCStation << endl
		<< cs.workshopCStation << endl
		<< cs.koefCStation << endl
		<< cs.STishoda << endl
		<< cs.STzahoda << endl;
	return out;
}

ifstream& operator >> (ifstream& in, CStation& cs)
{
	in >> cs.csID;
	in >> cs.nameCStation;
	in >> cs.shopCStation;
	in >> cs.workshopCStation;
	in >> cs.koefCStation;
	in >> cs.STishoda;
	in >> cs.STzahoda;
	return in;
}