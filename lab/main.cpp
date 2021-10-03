#include <iostream>

using namespace std;

struct Pipe
{
	int id;
	double lenght;
	double diametr;
	bool status;
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

void PrintPipe()
{
	cout << "id: " << p.id
		<< "lenght: " << p.lenght
		<< "diametr: " << p.diametr << endl;
}

int main()
{
	
return 0;
}