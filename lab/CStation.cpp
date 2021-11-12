#include "CStation.h"
#include "Utils.h"
#include <iostream>

using namespace std;

int CStation::MaxIDcs = 0;

CStation::CStation()
{
	idCStation = ++MaxIDcs;
}

ostream& operator << (ostream& out, const CStation& cs)
{
	out << "\nCompressor Station id: " << cs.idCStation
		<< "\nCompressor Station name: " << cs.nameCStation
		<< "\nCompressor Station shops: " << cs.shopCStation
		<< "\nCompressor Station workshops: " << cs.workshopCStation
		<< "\nCompressor Station efficiency indicator: " << cs.koefCStation << endl;
	return out;
}

istream& operator >> (istream& in, CStation& cs)
{
	cout << "Input compressor station name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, cs.nameCStation);

	cout << "How many shops at the compressor station? (1 - 10): ";
	cs.shopCStation = GetCorrectNumber(1, 10);

	cout << "How many workshops at the compressor station? ";
	cs.workshopCStation = GetCorrectNumber(0, cs.shopCStation);


	cout << "Input compressor station efficiency indicator [%], please: ";
	cs.koefCStation = GetCorrectNumber(0, 100);

	return in;
}