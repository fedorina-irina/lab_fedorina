#include "Pipe.h"
#include "Utils.h"

using namespace std;

int Pipe::MaxIDpipe = 0;

int Pipe::GetID() const
{
	return pID;
}

void Pipe::SetID()
{
	pID = ++MaxIDpipe;
}

void Pipe::EditPipe()
{
	statusPipe = (!statusPipe);
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "\nPipe's id: " << p.pID
		<< "\nPipe's name: " << p.namePipe
		<< "\nPipe's lenght: " << p.lenghtPipe
		<< "\nPipe's diametr: " << p.diametrPipe
		<< "\nPipe's status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
	return out;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.SetID();

	cout << "Input pipe's name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, p.namePipe);

	cout << "Input pipe's lenght (1 - 5000 m), please: " << endl;
	p.lenghtPipe = GetCorrectNumber(1, 5000);

	cout << "Input pipe's diametr (1 - 1420 mm), please: " << endl;
	p.diametrPipe = GetCorrectNumber(1, 1420);

	p.statusPipe = true;
	p.CSidOUT = 0;
	p.CSidIN = 0;

	return in;
}

ofstream& operator << (ofstream& out, const Pipe& p)
{
	out << p.GetID() << endl
		<< p.namePipe << endl
		<< p.lenghtPipe << endl
		<< p.diametrPipe << endl
		<< p.statusPipe << endl
		<< p.CSidOUT << endl
		<< p.CSidIN << endl;
	return out;
}

ifstream& operator >> (ifstream& in, Pipe& p)
{
	in >> p.pID;
	in >> p.namePipe;
	in >> p.lenghtPipe;
	in >> p.diametrPipe;
	in >> p.statusPipe;
	in >> p.CSidOUT;
	in >> p.CSidIN;
	return in;
}