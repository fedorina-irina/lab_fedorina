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
	cin >> cs.workshop;
	return cs;
}

void PrintPipe(Pipe p)
{
	cout << "id: " << p.id
		<< "\nlenght: " << p.lenght
		<< "\ndiametr: " << p.diametr << endl;
}

void EditPipe(Pipe& p)
{

}

int main()
{	

	Pipe pipe = InputPipe();
	PrintPipe(pipe);
	return 0;
}