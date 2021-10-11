#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Indicate the state of the pipe (0 - pipe under repair ; 1 - pipe is working): ";
		cin >> p.status;
	} while (cin.fail() || (p.status != 0) && (p.status != 1));

	return in;
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

	cin.ignore(10000, '\n');
	cout << "Input compressor station name, please: ";
	string(cs.name);
	getline(cin, cs.name);

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

void Print(Pipe p, CStation cs)
{
	cout << "Pipe id: " << p.id
		<< "\nPipe lenght: " << p.lenght
		<< "\nPipe diametr: " << p.diametr
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.status
		<< "\nCompressor Station id: " << cs.id << endl;
	cin.ignore(10000, '\n');
	cout << "\nCompressor Station name: " << cs.name
		<< "\nCompressor Station shops: " << cs.shop
		<< "\nCompressor Station workshops: " << cs.workshop
		<< "\nCompressor Station efficiency indicator: " << cs.e << endl;
}

ostream& operator << (ostream& out, Pipe& p)
{
	out << "Pipe id: " << p.id
		<< "\nPipe lenght: " << p.lenght
		<< "\nPipe diametr: " << p.diametr
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.status << endl;
	return out;
}

ostream& operator << (ostream& out, const CStation& cs)
{
	out << "\nCompressor Station id: " << cs.id
		<< "\nCompressor Station name: " << cs.name
		<< "\nCompressor Station shops: " << cs.shop 
		<< "\nCompressor Station workshops: " << cs.workshop 
		<< "\nCompressor Station efficiency indicator: " << cs.e << endl;
	return out;
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
		{
		if (cs.workshop < cs.shop)
			cs.workshop++;
		else cout << "You can't do this";
		}
		
	else
	{
		if (cs.workshop > 0)
			cs.workshop--;
		else cout << "You can't do this";
	}
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

void Save(Pipe p, CStation cs)
{
	ofstream fout;
	fout.open("file.txt", ios::out);
	if (fout.is_open())
	{
		fout << p.id << endl
			<< p.lenght << endl
			<< p.diametr << endl
			<< p.status << endl
			<< cs.id << endl
			<< cs.name << endl
			<< cs.shop << endl
			<< cs.workshop << endl
			<< cs.e << endl;
		fout.close();
	}
}

void Load(Pipe p, CStation cs)
{
	ifstream fin;
	fin.open("file.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.id;
		fin >> p.lenght;
		fin >> p.diametr;
		fin >> p.status;
		fin >> cs.id;
		fin.ignore(10000, '\n');
		string(cs.name);
		getline(fin, cs.name);
		fin >> cs.shop;
		fin >> cs.workshop;
		fin >> cs.e;
	}
	fin.close();
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
			cin >> pipe;
			break;
		}
		case 2:
		{
			system("cls");
			cin >> cs;
			break;
		}
		case 3:
		{
			system("cls");
			if (IsPipeValid(pipe) && IsCSValid(cs))
				{
					cout << pipe;
					cout << cs;
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
			Save(pipe, cs);
			break;
		}
		case 7:
		{
			system("cls");
			Load(pipe, cs);
			Print(pipe, cs);
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