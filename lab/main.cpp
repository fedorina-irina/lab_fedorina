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

template <typename T>

T GetCorrectNumber(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x < min || x > max || (x - int(x)) != 0 )
	{

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "ERROR! Type number (" << min << " - " << max << "): ";
	} 
	return x;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.idPipe++;

	cout << "Input pipe lenght [m], please: " << endl;
	p.lenghtPipe = GetCorrectNumber(0,12);
	
	cout << "Input pipe diametr [mm], please: " << endl;
	p.diametrPipe = GetCorrectNumber(0,1420);

	return in;
}

istream& operator >> (istream& in, CStation& cs)
{
	cs.idCStation++;

	cout << "Input compressor station name, please: ";
	do
	{
		getline(cin, cs.nameCStation);	
	} while (cs.nameCStation.length() == 0);
	
	cout << "How many shops at the compressor station? (1 - 10)";
	cs.shopCStation = GetCorrectNumber(1,10);
	
	cout << "How many workshops at the compressor station? (1 - 10)";
	cs.workshopCStation = GetCorrectNumber(1,10);

	
	cout << "Input compressor station efficiency indicator [%], please: ";
	cs.koefCStation = GetCorrectNumber(0,100);

	return in;
}

void Print(Pipe p, CStation cs)
{
	if (p.idPipe > 0 && cs.idCStation == 0)
	{
		cout << "\nPipe id: " << p.idPipe << endl;
		cout << "Pipe lenght: " << p.lenghtPipe << endl;
		cout << "Pipe diametr: " << p.diametrPipe << endl;
		cout << "Pipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
	}
	else
		if (p.idPipe == 0 && cs.idCStation > 0)
		{
			cout << "Compressor Station id: " << cs.idCStation << endl;
			cin.ignore(10000, '\n');
			cout << "Compressor Station name: " << cs.nameCStation << endl;
			cout << "Compressor Station shops: " << cs.shopCStation << endl;
			cout << "Compressor Station workshops: " << cs.workshopCStation << endl;
			cout << "Compressor Station efficiency indicator: " << cs.koefCStation << endl;
		}
		else
			if (p.idPipe > 0 && cs.idCStation > 0)
			{
				cout << "\nPipe id: " << p.idPipe << endl;
				cout << "Pipe lenght: " << p.lenghtPipe << endl;
				cout << "Pipe diametr: " << p.diametrPipe << endl;
				cout << "Pipe status (1 - pipe is working ; 0 - pipe under repair): " << p.statusPipe << endl;
				cout << "Compressor Station id: " << cs.idCStation << endl;
				cin.ignore(10000, '\n');
				cout << "Compressor Station name: " << cs.nameCStation << endl;
				cout << "Compressor Station shops: " << cs.shopCStation << endl;
				cout << "Compressor Station workshops: " << cs.workshopCStation << endl;
				cout << "Compressor Station efficiency indicator: " << cs.koefCStation << endl;
			}
			else
				cout << "You should input objects" << endl;
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
		if (p.idPipe > 0 && cs.idCStation == 0)
		{
			fout << p.idPipe << endl
				<< p.lenghtPipe << endl
				<< p.diametrPipe << endl
				<< p.statusPipe << endl;
		}
		else if (p.idPipe == 0 && cs.idCStation > 0)
		{
			fout << cs.idCStation << endl
				<< cs.nameCStation << endl
				<< cs.shopCStation << endl
				<< cs.workshopCStation << endl
				<< cs.koefCStation << endl;
		}
		else if (p.idPipe > 0 && cs.idCStation > 0)
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
		}
		else cout << "File is empty. Input objects" << endl;
		fout.close();
	}
}

void Load(Pipe p, CStation cs)
{
	ifstream fin;
	fin.open("file.txt", ios::in);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> p.idPipe;
			fin >> p.lenghtPipe;
			fin >> p.diametrPipe;
			fin >> p.statusPipe;
			fin >> cs.idCStation;
			fin.ignore(10000, '\n');
			getline(fin, cs.nameCStation);
			fin >> cs.shopCStation;
			fin >> cs.workshopCStation;
			fin >> cs.koefCStation;
		}
	}
	else cout << "ERROR!" << endl;
	fin.close();
}

int main()
{
	Pipe p;
	CStation cs;

	p.idPipe = 0;
	p.statusPipe = 1;
	cs.idCStation = 0;

	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0,7))
		{
		case 1:
		{
			cin.clear();
			system("cls");
			cin >> p;
			break;
		}
		case 2:
		{
			cin.clear();
			system("cls");
			cin >> cs;
			break;
		}
		case 3:
		{
			cin.clear();
			system("cls");
			if ((p.idPipe != 0) && (cs.idCStation == 0))
					cout << p;
			else if ((p.idPipe == 0) && (cs.idCStation != 0))
					cout << cs;
			else if ((p.idPipe != 0) && (cs.idCStation != 0))
			{
				cout << p;
				cout << cs;
			}
			else cout << "Input objects" << endl;
			break;
		}
		case 4:
		{
			cin.clear();
			system("cls");
			if (p.idPipe > 0)
			{
				EditPipe(p);
			}
			else cout << "Input pipe" << endl;
			break;
		}
		case 5:
		{
			cin.clear();
			system("cls");
			if (cs.idCStation > 0)
			{
				EditStation(cs);
			}
			else cout << "Input compressor station" << endl;
			break;
		}
		case 6:
		{
			cin.clear();
			system("cls");
			Save(p, cs);
			break;
		}
		case 7:
		{
			cin.clear();
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