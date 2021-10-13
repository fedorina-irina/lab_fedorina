#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct Pipe
{
	int idPipe;
	double lenghtPipe;
	int diametrPipe;
	bool statusPipe;
};

struct CStation
{
	int idCStation;
	string nameCStation;
	int shopCStation;
	int workshopCStation;
	int koefCStation;
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
		cout << "Input pipe lenght, please: ";
		cin >> p.lenghtPipe;
	} while (cin.fail() || (p.lenghtPipe < 0));

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input pipe diametr, please: ";
		cin >> p.diametrPipe;
	} while (cin.fail() || (p.diametrPipe < 0) || (p.diametrPipe > 1420));

	return in;
}

istream& operator >> (istream& in, CStation& cs)
{
	cout << "Input compressor station name, please: ";
	while (true)
	{
		cin.ignore(10000, '\n');
		getline(cin, cs.nameCStation);
		if (cs.nameCStation.empty())
		{
			cin.clear();
			system("cls");
			cout << "Don't input empty name" << endl;
		}
		else break;
		
	}
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "How many shops at the compressor station? ";
		cin >> cs.shopCStation;
	} while (cin.fail() || (cs.shopCStation < 0));
	
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "How many workshops at the compressor station? ";
		cin >> cs.workshopCStation;
	} while (cin.fail() || (cs.workshopCStation < 0) || (cs.workshopCStation > cs.shopCStation));

	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Input compressor station efficiency indicator, please: ";
		cin >> cs.koefCStation;
	} while (cin.fail() || (cs.koefCStation < 0) || (cs.koefCStation > 100));

	return in;
}

void Print(Pipe p, CStation cs)
{
	cout << "Pipe id: " << p.idPipe
		<< "\nPipe lenght: " << p.lenghtPipe
		<< "\nPipe diametr: " << p.diametrPipe
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe
		<< "\nCompressor Station id: " << cs.idCStation << endl;
	cin.ignore(10000, '\n');
	cout << "\nCompressor Station name: " << cs.nameCStation
		<< "\nCompressor Station shops: " << cs.shopCStation
		<< "\nCompressor Station workshops: " << cs.workshopCStation
		<< "\nCompressor Station efficiency indicator: " << cs.koefCStation << endl;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "Pipe id: " << p.idPipe
		<< "\nPipe lenght: " << p.lenghtPipe
		<< "\nPipe diametr: " << p.diametrPipe
		<< "\nPipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
	return out;
}

ostream& operator << (ostream& out, const CStation& cs)
{
	out << "\nCompressor Station id: " << cs.idCStation
		<< "\nCompressor Station name: " << cs.nameCStation
		<< "\nCompressor Station shops: " << cs.shopCStation
		<< "\nCompressor Station workshops: " << cs.workshopCStation
		<< "\nCompressor Station efficiency indicator: " << cs.koefCStation << endl;
	return out;
}

void EditPipe(Pipe& p)
{
	cout << "Do you want to change pipe status? (1 - yes ; 0 - no) :\n";

	if (GetCorrectNumber(0, 1) == 1)
		p.statusPipe = (!p.statusPipe);
}

void EditStation(CStation& cs)
{
	cout << "Do you want to launch another workshop or to stop one workshop? (1 - launch / 0 - stop) :\n";
	if (GetCorrectNumber(0, 1) == 1)
		{
		if (cs.workshopCStation < cs.shopCStation)
			cs.workshopCStation++;
		else cout << "You can't do this";
		}
		
	else
	{
		if (cs.workshopCStation > 0)
			cs.workshopCStation--;
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
		<< "7. Load" << endl
		<< "0. Exit" << endl
		<< "Choose action: "<< endl;
}

void Save(Pipe p, CStation cs)
{
	ofstream fout;
	fout.open("file.txt", ios::out);
	if (fout.is_open())
	{
		fout << p.idPipe << endl
			<< p.lenghtPipe << endl
			<< p.diametrPipe << endl
			<< p.statusPipe << endl
			<< cs.idCStation << endl
			<< cs.nameCStation << endl
			<< cs.shopCStation << endl
			<< cs.workshopCStation << endl
			<< cs.koefCStation << endl;
		fout.close();
	}
}

void Load(Pipe p, CStation cs)
{
	ifstream fin;
	fin.open("file.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.idPipe;
		fin >> p.lenghtPipe;
		fin >> p.diametrPipe;
		fin >> p.statusPipe;
		fin >> cs.idCStation;
		fin.ignore(10000, '\n');
		string(cs.nameCStation);
		getline(fin, cs.nameCStation);
		fin >> cs.shopCStation;
		fin >> cs.workshopCStation;
		fin >> cs.koefCStation;
	}
	fin.close();
}

int main()
{
	Pipe p = {};
	CStation cs = {};

	p.idPipe = 1;
	p.statusPipe = 1;
	cs.idCStation = 1;

	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0,7))
		{
		case 1:
		{
			system("cls");
			cin >> p;
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
			if ((p.lenghtPipe != 0) && (cs.shopCStation == 0))
						cout << p;
			else if ((p.lenghtPipe == 0) && (cs.shopCStation != 0))
					cout << cs;
			else if ((p.lenghtPipe != 0) && (cs.shopCStation != 0))
			{
				cout << p;
				cout << cs;
			}
			else cout << "Input pipe and Compressor station" << endl;
			break;
		}
		case 4:
		{
			system("cls");
			EditPipe(p);
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
			Save(p, cs);
			break;
		}
		case 7:
		{
			system("cls");
			Load(p, cs);
			Print(p, cs);
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