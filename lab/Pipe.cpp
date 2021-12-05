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

//Pipe::Pipe()
//{
//	pID = ++MaxIDpipe;
//}

void Pipe::EditPipe(Pipe& p)
{
	p.statusPipe = (!p.statusPipe);
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "\nPipe id: " << p.pID
		<< "\nPipe name: " << p.namePipe
		<< "\nPipe lenght: " << p.lenghtPipe
		<< "\nPipe diametr: " << p.diametrPipe
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
	return out;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.SetID();

	cout << "Input pipe name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, p.namePipe);

	cout << "Input pipe lenght (1 - 5000 m), please: " << endl;
	p.lenghtPipe = GetCorrectNumber(1, 5000);

	cout << "Input pipe diametr (1 - 1420 mm), please: " << endl;
	p.diametrPipe = GetCorrectNumber(1, 1420);

	p.statusPipe = true;

	return in;
}

ofstream& operator << (ofstream& out, const Pipe& p)
{
	out << p.GetID() << endl
		<< p.namePipe << endl
		<< p.lenghtPipe << endl
		<< p.diametrPipe << endl
		<< p.statusPipe << endl;
	return out;
}

ifstream& operator >> (ifstream& in, Pipe& p)
{
	in >> p.pID;
	in >> p.namePipe;
	in >> p.lenghtPipe;
	in >> p.diametrPipe;
	in >> p.statusPipe;
	return in;
}