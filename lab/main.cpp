#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Pipe.h"
#include "CStation.h"
#include "Utils.h"

using namespace std;

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
		<< p.MaxIDpipe << endl
		<< p.idPipe << endl
		<< p.namePipe << endl
		<< p.lenghtPipe << endl
		<< p.diametrPipe << endl
		<< p.statusPipe << endl;
}

void SaveStation(ofstream& fout, const CStation& cs)
{
	string object;
	object = "COMPRESSOR STATION";
	fout << object << endl
		<< cs.MaxIDcs << endl
		<< cs.idCStation << endl
		<< cs.nameCStation << endl
		<< cs.shopCStation << endl
		<< cs.workshopCStation << endl
		<< cs.koefCStation << endl;
}

Pipe LoadPipe(ifstream& fin)
{
	Pipe p;

	fin >> p.MaxIDpipe;
	fin >> p.idPipe;
	fin.ignore(10000, '\n');
	getline(fin, p.namePipe);
	fin >> p.lenghtPipe;
	fin >> p.diametrPipe;
	fin >> p.statusPipe;

	return p;
}

CStation LoadStation(ifstream& fin)
{
	CStation cs;

	fin >> cs.MaxIDcs;
	fin >> cs.idCStation;
	fin.ignore(10000, '\n');
	getline(fin, cs.nameCStation);
	fin >> cs.shopCStation;
	fin >> cs.workshopCStation;
	fin >> cs.koefCStation;

	return cs;
}

template<typename T>
using Filter1 = bool(*)(const Pipe& p, T param);

bool CheckByPName(const Pipe& p, string param)
{
	return p.namePipe == param;
}

bool CheckByStatus(const Pipe& p, bool param)
{
	return p.statusPipe == param;
}

bool CheckByLenght(const Pipe& p, int param)
{
	return p.lenghtPipe >= param;
}

bool CheckByDiametr(const Pipe& p, int param)
{
	return p.diametrPipe >= param;
}

template<typename T>
vector<int>FindPipesByFilter(const vector<Pipe>& pipeline,Filter1 <T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (auto& p : pipeline)
	{
		if (f(p,param))
			res.push_back(i);
		i++;
	}
	return res;
}

template<typename T>
using Filter2 = bool(*)(const CStation& cs, T param);

bool CheckByCSName(const CStation& cs, string param)
{
	return cs.nameCStation == param;
}

bool CheckByPercent(const CStation& cs, double param)
{
	double percent = ((double)cs.shopCStation - (double)cs.workshopCStation) / cs.shopCStation * 100;
	return percent >= param;
}

template<typename T>
vector<int>FindCStationsByFilter(const vector<CStation>& CSSistem, Filter2 <T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (auto& cs : CSSistem)
	{
		if (f(cs, param))
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
			/*kol_p++;*/
			cin >> p;
			pipeline.push_back(p);
			break;
		}
		case 2:
		{
			cin.clear();
			system("cls");
			CStation cs;
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
			cout << "Find pipes or compressor stations by filter (1 - pipes ; 2 - compressor stations):  " << endl;
			if (GetCorrectNumber(1, 2) == 1)
			{
				cout << "Find pipes by filter (1 - name ; 2 - status ; 3 - lenght ; 4 - diametr):  " << endl;
				switch (GetCorrectNumber(1, 4))
				{
				case 1:
				{
					string pname;
					cout << "Find pipe with name:  " << endl;
					cin.ignore(10000, '\n');
					getline(cin, pname);
					for (int i : FindPipesByFilter(pipeline, CheckByPName, pname))
						cout << pipeline[i];
					break;
				}
				case 2:
				{
					cout << "Find pipes with status (1 - pipe is working ; 0 - pipe under repair):  " << endl;
					bool status = GetCorrectNumber(0, 1);
					for (int i : FindPipesByFilter(pipeline, CheckByStatus, status))
						cout << pipeline[i];
					break;
				}
				case 3:
				{
					cout << "Find a pipes whose length is greater than or equal to (1 - 5000 m):  " << endl;
					int lenght = GetCorrectNumber(1, 5000);
					for (int i : FindPipesByFilter(pipeline, CheckByLenght, lenght))
						cout << pipeline[i];
					break;
				}
				case 4:
				{
					cout << "Find a pipes whose diametr is greater than or equal to (1 - 1420 mm):  " << endl;
					int diametr = GetCorrectNumber(1, 1420);
					for (int i : FindPipesByFilter(pipeline, CheckByDiametr, diametr))
						cout << pipeline[i];
					break;
				}
				}
				
			}
			else
			{
				cout << "Find compressor stations by filter (1 - name ; 2 - percent):  " << endl;
				switch (GetCorrectNumber(1, 3))
				{
				case 1:
				{
					string csname;
					cout << "Find compressor stations with name:  " << endl;
					cin.ignore(10000, '\n');
					getline(cin, csname);
					for (int i : FindCStationsByFilter(CSSistem, CheckByCSName, csname))
						cout << CSSistem[i];
				}
				case 2:
				{
					double percent;
					cout << "Find compressor stations with percent of unused shops (0 - 100 %):  " << endl;
					cin >> percent;
					while (percent < 0.0 || percent > 100.0)
					{
						cin.clear();
						cin.ignore(10000, '\n');
						cout << "ERROR! Type number (0 - 100): ";
					}

					for (int i : FindCStationsByFilter(CSSistem, CheckByPercent, percent))
						cout << CSSistem[i];
				}
				}
			}
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