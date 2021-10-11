#include <iostream>
#include <fstream>

using namespace std;

struct Pipe
{
	int id;
	double lenght;
	double diametr;
	int status;
};

struct CStation
{
	int id;
	string name;
	int shop;
	int workshop;
	double e;
};

int GetCorrectNumber(int min, int max)
{
	double x;
	while ((cin >> x).fail() || x < min || x > max || (x - int(x)) != 0 )
	{

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "ERROR! Type number (" << min << " - " << max << "): ";
	} 
	return int(x);
}

//Pipe InputPipe()
//{
//	Pipe p;
//	cout << "Input pipe id, please: ";
//	cin >> p.id;
//	cout << "Input pipe lenght, please: ";
//	cin >> p.lenght;
//	cout << "Input pipe diametr, please: ";
//	cin >> p.diametr;
//	cout << "Indicate the state of the pipe (0 - pipe under repair ; 1 - pipe is working): ";
//	p.status = GetCorrectNumber(0, 1);
//	return p;
//}

istream& operator >> (istream& in, Pipe& p)
{
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input pipe id, please: ";
		cin >> p.id;
	} while (cin.fail() || (p.id < 0));

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input pipe lenght, please: ";
		cin >> p.lenght;
	} while (cin.fail() || (p.lenght < 0));

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input pipe diametr, please: ";
		cin >> p.diametr;
	} while (cin.fail() || (p.diametr < 0));

	cout << "Indicate the state of the pipe (0 - pipe under repair ; 1 - pipe is working): ";
	p.status = GetCorrectNumber(0, 1);

	return in;
}

CStation InputStation()
{
	CStation cs;
	cout << "Input compressor station id, please: ";
	cin >> cs.id;
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

istream& operator >> (istream& in, CStation& cs)
{
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input compressor station id, please: ";
		cin >> cs.id;
	} while (cin.fail() || (cs.id < 0));

	cout << "Input compressor station name, please: ";
	cin >> cs.name;

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "How many shops at the compressor station? ";
		cin >> cs.shop;
	} while (cin.fail() || (cs.shop < 0));
	
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "How many workshops at the compressor station? ";
		cin >> cs.workshop;
	} while (cin.fail() || (cs.workshop < 0) || (cs.workshop > cs.shop));

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input compressor station efficiency indicator, please: ";
		cin >> cs.e;
	} while (cin.fail() || (cs.e < 0));

	return in;
}

void PrintPipe(Pipe p)
{
	cout << "Pipe id: " << p.id
		<< "\nPipe lenght: " << p.lenght
		<< "\nPipe diametr: " << p.diametr
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " <<  p.status << endl;
}

void PrintStation(CStation cs)
{
	cout << "\nCompressor Station id: " << cs.id
		<< "\nCompressor Station name: " << cs.name
		<< "\nCompressor Station shops: " << cs.shop 
		<< "\nCompressor Station workshops: " << cs.workshop 
		<< "\nCompressor Station efficiency indicator: " << cs.e << endl;
}

void EditPipe(Pipe& p)
{
	cout << "Do you want to change pipe status? (1 - yes ; 0 - no) :\n";

	if (GetCorrectNumber(0, 1) == 1)
	{
		if (p.status == 1)
			p.status = 0;
		else
			p.status = 1;
	}
}

void EditStation(CStation& cs)
{
	cout << "Do you want to launch another workshop or to stop one workshop? (1 - launch / 0 - stop) :\n";

	if (GetCorrectNumber(0, 1) == 1)
		cs.workshop++;
	else
		cs.workshop--;
}

void PrintMenu()
{
	cout << "\n***MENU***" << endl
		<< "1. Input Pipe" << endl
		<< "2. Input Compressor Station" << endl
		<< "3. Print Objects" << endl
		<< "4. Edit Pipe" << endl
		<< "5. Edit Station" << endl
		<< "6. Save" << endl
		<< "7. Download" << endl
		<< "0. Exit" << endl
		<< "Choose action: "<< endl;
}

void SavePipe(Pipe p)
{
	ofstream fout;
	fout.open("pipe.txt", ios::out);
	if (fout.is_open())
	{
		fout << p.id << endl
			<< p.lenght << endl
			<< p.diametr << endl
			<< p.status << endl;
		fout.close();
	}
}

void SaveStation(CStation cs)
{
	ofstream fout;
	fout.open("station.txt", ios::out);
	if (fout.is_open())
	{
		fout << cs.id << endl
			<< cs.name << endl
			<< cs.shop << endl
			<< cs.workshop << endl
			<< cs.e << endl;
		fout.close();
	}
}

Pipe LoadPipe()
{
	Pipe p;
	ifstream fin;
	fin.open("pipe.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.id;
		fin >> p.lenght;
		fin >> p.diametr;
		fin >> p.status;
	}
	fin.close();
	return p;
}

CStation LoadStation()
{
	CStation cs;
	ifstream fin;
	fin.open("station.txt", ios::in);
	if (fin.is_open())
	{
		fin >> cs.id;
		fin >> cs.name;
		fin >> cs.shop;
		fin >> cs.workshop;
		fin >> cs.e;
	}
	fin.close();
	return cs;
}

bool IsPipeValid(const Pipe& pipe)
{
	return pipe.id > 0;
}

bool IsCSValid(const CStation& cs)
{
	return cs.id > 0;
}

int main()
{
	Pipe pipe = {};
	CStation cs = {};
	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0,7))
		{
		case 1:
		{
			system("cls");
			pipe = InputPipe();
			break;
		}
		case 2:
		{
			system("cls");
			cs = InputStation();
			break;
		}
		case 3:
		{
			system("cls");
			if (IsPipeValid(pipe) && IsCSValid(cs))
				{
					PrintPipe(pipe);
					PrintStation(cs);
				}
			else cout << "Input pipe and Compressor station" << endl;
			break;
		}
		case 4:
		{
			system("cls");
			EditPipe(pipe);
			break;
		}
		case 5:
		{
			system("cls");
			EditStation(cs);
			break;
		}
		case 6:
		{
			system("cls");
			SavePipe(pipe);
			SaveStation(cs);
			break;
		}
		case 7:
		{
			system("cls");
			PrintPipe(LoadPipe());
			PrintStation(LoadStation());
			break;
		}
		case 0:
		{
			return 0;
		}


		}
	}
	
	return 0;
}