#include <iostream>

using namespace std;

struct Pipe
{
	int id;
	double lenght;
	double diametr;
	bool status;
};

struct CStation
{
	int id;
	string name;
	int shop;
	int workshop;
	double e;
};

Pipe InputPipe()
{
	Pipe p;
	p.id = 0;
	cout << "Input pipe lenght, please: ";
	cin >> p.lenght;
	cout << "Input pipe diametr, please: ";
	cin >> p.diametr;
	return p;
}

CStation InputStation()
{
	CStation cs;
	cs.id = 0;
	cout << "Input compressor station name, please: ";
	cin >> cs.name;
	cout << "How many shops at the compressor station? ";
	cin >> cs.shop;
	cout << "How many workshops at the compressor station? ";
	cin >> cs.workshop;
	cout << "Input compressor station efficiency indicator, please: ";
	cin >> cs.e;
	return cs;
}

void PrintPipe(Pipe p)
{
	cout << "id: " << p.id
		<< "\nlenght: " << p.lenght
		<< "\ndiametr: " << p.diametr << endl;
}

void PrintStation(CStation cs)
{
	cout << "id: " << cs.id
		<< "\nname: " << cs.name
		<< "\nshops: " << cs.shop 
		<< "\nworkshops: " << cs.workshop 
		<< "\nefficiency indicator: " << cs.e << endl;
}

void EditPipe(Pipe& p)
{

}

void PrintMenu()
{
	cout << "1. Input Pipe" << endl
		<< "2. Input Compressor Station" << endl
		<< "3. Print Objects" << endl
		<< "4. Edit Pipe" << endl
		<< "5. Edit Station" << endl
		<< "6. Save" << endl
		<< "7. Download" << endl
		<< "0. Exit" << endl;

}

int main()
{
	Pipe pipe;
	CStation cs;

		while (1)
		{
			PrintMenu();
			int i = 0;
			cin >> i;
			switch (i)
			{
			case 1:
			{
				pipe = InputPipe();
				break;
			}
			case 2:
			{
				cs = InputStation();
				break;
			}
			case 3:
			{
				PrintPipe(pipe);

				PrintStation(cs);
				break;
			}
			case 4:
			{

				break;
			}
			case 5:
			{

				break;
			}
			case 6:
			{

				break;
			}
			case 7:
			{

				break;
			}
			case 0:
			{

				break;
			}
			}
		}
	PrintPipe(pipe);

	PrintStation(cs);
	
	return 0;
}