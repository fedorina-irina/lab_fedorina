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
	int x;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type number (" << min << " - " << max << "): ";
	} 
	return x;
}

Pipe InputPipe()
{
	Pipe p;
	cout << "Input pipe id, please: ";
	cin >> p.id;
	cout << "Input pipe lenght, please: ";
	cin >> p.lenght;
	cout << "Input pipe diametr, please: ";
	cin >> p.diametr;
	cout << "Indicate the state of the pipe (0 - pipe under repair ; 1 - pipe is working): ";
	cin >> p.status;
	return p;
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
	string change;
	cout << "Do you want to change pipe status? (yes / no) :\n";
	cin >> change;

	if (change == "yes")
			p.status = (!p.status);
}

void EditStation(CStation& cs)
{
	string change;
	cout << "Do you want to launch another workshop or to stop one workshop? (launch / stop) :\n";
	cin >> change;

	if (change == "launch")
		cs.workshop++;
	else
		cs.workshop--;
}

void PrintMenu()
{
	cout << "1. Input Pipe" << endl
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

int main()
{
	Pipe pipe;
	CStation cs;

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
			PrintPipe(pipe);
			PrintStation(cs);
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