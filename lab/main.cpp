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
	cout << "1. �������� �����" << endl
		<< "2. �������� ��" << endl
		<< "3. �������� ���� ��������" << endl
		<< "4. ������������� �����" << endl
		<< "5. ������������� ��" << endl
		<< "6. ���������" << endl
		<< "7. ���������" << endl
		<< "0. �����" << endl;

}

int main()
{	
	Pipe pipe = InputPipe();
	PrintPipe(pipe);
	
	CStation cs = InputStation();
	PrintStation(cs);
	
	return 0;
}