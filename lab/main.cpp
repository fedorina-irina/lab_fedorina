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

int main()
{
	
return 0;
}