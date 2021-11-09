#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;
int kol_p = 0;
int kol_cs = 0;

struct Pipe
{
	int idPipe = 0;
	int lenghtPipe;
	int diametrPipe;
	bool statusPipe = 1;
};

struct CStation
{
	int idCStation = 0;
	string nameCStation;
	int shopCStation;
	int workshopCStation;
	int koefCStation;
};

template <typename T>

T GetCorrectNumber(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x < min || x > max || (x - int(x)) != 0 || (char(cin.peek()) == '.') || (char(cin.peek()) == ','))
	{

		cin.clear();
		cin.ignore(10000, '\n');
		cout << "ERROR! Type number (" << min << " - " << max << "): ";
	} 
	return x;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.idPipe = kol_p;

	cout << "Input pipe lenght (1 - 5000 m), please: " << endl;
	p.lenghtPipe = GetCorrectNumber(1,5000);
	
	cout << "Input pipe diametr (1 - 1420 mm), please: " << endl;
	p.diametrPipe = GetCorrectNumber(1,1420);

	return in;
}

istream& operator >> (istream& in, CStation& cs)
{
	cs.idCStation = kol_cs;

	cout << "Input compressor station name, please: ";
	cin.ignore(10000, '\n');
	getline(cin, cs.nameCStation);
	
	cout << "How many shops at the compressor station? (1 - 10): ";
	cs.shopCStation = GetCorrectNumber(1,10);
	
	cout << "How many workshops at the compressor station? ";
	cs.workshopCStation = GetCorrectNumber(0, cs.shopCStation);

	
	cout << "Input compressor station efficiency indicator [%], please: ";
	cs.koefCStation = GetCorrectNumber(0,100);

	return in;
}

Pipe& SelectPipe(vector<Pipe>& p)
{
	cout << "Enter pipe id: ";
	unsigned int index = GetCorrectNumber<uint64_t>(1, p.size());
	return p[index - 1];
}

CStation& SelectCS(vector<CStation>& cs)
{
	cout << "Enter compressor station id: ";
	unsigned int index = GetCorrectNumber<uint64_t>(1, cs.size());
	return cs[index - 1];
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

void DeletePipe(vector<Pipe>& p)
{
	cout << "Enter pipe id: ";
	int index = GetCorrectNumber<uint64_t>(1, p.size());
	auto i = p.cbegin();
	p.erase(i + index - 1); 
}

void DeleteStation(vector<CStation>& cs)
{
	cout << "Enter compressor station id: ";
	auto index = GetCorrectNumber<uint64_t>(1, cs.size());
	auto i = cs.cbegin();
	cs.erase(i + index - 1);
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
		<< "8. Delete Pipe" << endl
		<< "9. Delete Compressor Station" << endl
		<< "10. Search" << endl
		<< "0. Exit" << endl
		<< "Choose action: "<< endl;
}

void SavePipe(ofstream& fout, const Pipe& p)
{
	string object;
	object = "PIPE";
	fout << object << endl
		<< p.idPipe << endl
		<< p.lenghtPipe << endl
		<< p.diametrPipe << endl
		<< p.statusPipe << endl;
}

void SaveStation(ofstream& fout, const CStation& cs)
{
	string object;
	object = "COMPRESSOR STATION";
	fout << object << endl
		<< cs.idCStation << endl
		<< cs.nameCStation << endl
		<< cs.shopCStation << endl
		<< cs.workshopCStation << endl
		<< cs.koefCStation << endl;
}

Pipe LoadPipe(ifstream& fin)
{
	Pipe p;

	fin >> p.idPipe;
	fin >> p.lenghtPipe;
	fin >> p.diametrPipe;
	fin >> p.statusPipe;

	return p;
}

CStation LoadStation(ifstream& fin)
{
	CStation cs;

	fin >> cs.idCStation;
	fin.ignore(10000, '\n');
	getline(fin, cs.nameCStation);
	fin >> cs.shopCStation;
	fin >> cs.workshopCStation;
	fin >> cs.koefCStation;

	return cs;
}

vector<int>FindPipesByStatus(const vector<Pipe>& pipeline)
{
	cout << "Find pipes with status (1 - pipe is working ; 0 - pipe under repair):  " << endl;
	bool statusPipe = GetCorrectNumber(0, 1);
	vector<int>res;
	int i = 0;
	for (auto& p : pipeline)
	{
		if (p.statusPipe == statusPipe)
			res.push_back(i);
		i++;
	}
	return res;
}

int main()
{
	vector <Pipe> pipeline;
	vector <CStation> CSSistem;

	string object;

	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0,10))
		{
		case 1:
		{
			cin.clear();
			system("cls");
			Pipe p;
			kol_p++;
			cin >> p;
			pipeline.push_back(p);
			break;
		}
		case 2:
		{
			cin.clear();
			system("cls");
			CStation cs;
			kol_cs++;
			cin >> cs;
			CSSistem.push_back(cs);
			break;
		}
		case 3:
		{
			cin.clear();
			system("cls");
			if ((pipeline.size()!= 0) && (CSSistem.size() == 0))
				{
				for (auto& p : pipeline)
					cout << p << endl;
				}
			else if ((pipeline.size() == 0) && (CSSistem.size() != 0))
				{
				for (auto& cs : CSSistem)
					cout << cs << endl;
				}
			else if ((pipeline.size() != 0) && (CSSistem.size() != 0))
				{
				for (auto& p : pipeline)
						cout << p << endl;
				for (auto& cs : CSSistem)
					cout << cs << endl;
				}
			else cout << "Input objects" << endl;
			break;
		}
		case 4:
		{
			cin.clear();
			system("cls");
			if (pipeline.size() > 0)
			{
				EditPipe(SelectPipe(pipeline));
			}
			else cout << "Input pipe" << endl;
			break;
		}
		case 5:
		{
			cin.clear();
			system("cls");
			if (CSSistem.size() > 0)
			{
				EditStation(SelectCS(CSSistem));
			}
			else cout << "Input compressor station" << endl;
			break;
		}
		case 6:
		{
			cin.clear();
			system("cls");
			ofstream fout;
			fout.open("file.txt", ios::out);
			if (fout.is_open())
			{
				for (Pipe& p : pipeline)
					SavePipe(fout, p);
				for (CStation& cs : CSSistem)
					SaveStation(fout, cs);
				break;
			}
			else
				cout << "ERROR!" << endl;
			break;
		}
		case 7:
		{
			cin.clear();
			system("cls");
			string object;
			ifstream fin;
			fin.open("file.txt", ios::in);
			if (fin.is_open())
			{
				while (!fin.eof())
				{
					getline(fin, object);
					if (object == "PIPE")
						pipeline.push_back(LoadPipe(fin));
					if (object == "COMPRESSOR STATION")
						CSSistem.push_back(LoadStation(fin));
				}
				break;
			}
			else
				cout << "ERROR!" << endl;
			break;
		}
		case 8:
		{
			cin.clear();
			system("cls");
			if (pipeline.size() > 0)
			{
				DeletePipe(pipeline);
			}
			else cout << "Input pipe" << endl;
			break;
		}
		case 9:
		{
			cin.clear();
			system("cls");
			if (CSSistem.size() > 0)
			{
				DeleteStation(CSSistem);
			}
			else cout << "Input compressor station" << endl;
			break;
		}
		case 10:
		{
			cin.clear();
			system("cls");
			for (int i : FindPipesByStatus(pipeline))
				cout << pipeline[i];
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