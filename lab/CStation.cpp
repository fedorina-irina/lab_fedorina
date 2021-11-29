#include "CStation.h"
#include "Utils.h"
#include <iostream>

using namespace std;

int CStation::MaxIDcs = 0;

CStation::CStation()
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
	out << "\nCompressor Station MaxID: " << CStation::MaxIDcs
		<< "\nCompressor Station id: " << cs.csID
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