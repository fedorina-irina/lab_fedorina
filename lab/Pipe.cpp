#include "Pipe.h"
#include "Utils.h"

using namespace std;

int Pipe::MaxIDpipe = 0;

Pipe::Pipe()
{
	idPipe = ++MaxIDpipe;
	statusPipe = 1;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "\nPipe MaxID: " << Pipe::MaxIDpipe
		<< "\nPipe id: " << p.idPipe
		<< "\nPipe name: " << p.namePipe
		<< "\nPipe lenght: " << p.lenghtPipe
		<< "\nPipe diametr: " << p.diametrPipe
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
	return out;
}

istream& operator >> (istream& in, Pipe& p)
{
	cout << "Input pipe name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, p.namePipe);

	cout << "Input pipe lenght (1 - 5000 m), please: " << endl;
	p.lenghtPipe = GetCorrectNumber(1, 5000);

	cout << "Input pipe diametr (1 - 1420 mm), please: " << endl;
	p.diametrPipe = GetCorrectNumber(1, 1420);

	return in;
}
