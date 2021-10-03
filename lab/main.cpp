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