#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "CStation.h"
#include "Utils.h"

using namespace std;

int pID = 1;
int csID = 1;

Pipe& SelectPipe(unordered_map<int, Pipe>& p)
{
	cout << "Enter pipe id: ";
	int id = GetCorrectNumber<uint64_t>(1, p.size());
	if (p.count(id) == 0)
		cout << "ERROR! There is no pipe with this id\n";
	else
		return p[id];
}

CStation& SelectCS(unordered_map<int, CStation>& cs)
{
	cout << "Enter compressor station id: ";
	int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) == 0)
		cout << "ERROR! There is no compressor station with this id\n";
	else
		return cs[id];
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
		<< "11. Packet Edit Pipe" << endl
		<< "0. Exit" << endl
		<< "Choose action: "<< endl;
}

void SavePipe(ofstream& fout, const Pipe& p)
{
	string object;
	object = "PIPE";
	fout << object << endl
		<< p.MaxIDpipe << endl
		<< p.pID << endl
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
		<< cs.csID << endl
		<< cs.nameCStation << endl
		<< cs.shopCStation << endl
		<< cs.workshopCStation << endl
		<< cs.koefCStation << endl;
}

Pipe LoadPipe(ifstream& fin)
{
	Pipe p;

	fin >> p.MaxIDpipe;
	fin >> p.pID;
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
	fin >> cs.csID;
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
vector<int>FindPipesByFilter(const unordered_map<int, Pipe>& pipeline,Filter1 <T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (auto& p : pipeline)
	{
		if (f(p.second,param))
			res.push_back(p.second.pID);
		i++;
	}

	if (res.empty())
		cout << "There is no pipe with this parameter" << endl;

	return res;
}

void DeletePipe(unordered_map<int, Pipe>& p)
{
	cout << "Delete [1] - one pipe; [2] - pipes based on parameter <status>: ";
	switch (GetCorrectNumber(1, 2))
	{
	case 1:
	{
		cout << "Enter pipe id: ";
		int id = GetCorrectNumber<uint64_t>(1, p.size());
		if (p.count(id) == 0)
			cout << "ERROR! There is no pipe with this id\n";
		p.erase(id);
		break;
	}
	case 2:
	{
		cout << "Delete pipes with status (1 - pipe is working ; 0 - pipe under repair):  " << endl;
		bool status = GetCorrectNumber(0, 1);
		for (int i : FindPipesByFilter(p, CheckByStatus, status))
			p.erase(i);
		break;
	}
	}
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
vector<int>FindCStationsByFilter(const unordered_map<int, CStation>& CSSistem, Filter2 <T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (auto& cs : CSSistem)
	{
		if (f(cs.second, param))
			res.push_back(cs.second.csID);
		i++;
	}

	if (res.empty())
		cout << "There is no compressor station with this parameter" << endl;

	return res;
}

void DeleteStation(unordered_map<int, CStation>& cs)
{
	cout << "Enter compressor station id: ";
	int id = GetCorrectNumber<uint64_t>(1, cs.size());
	if (cs.count(id) == 0)
		cout << "ERROR! There is no compressor station with this id\n";
	else
		cs.erase(id);
}

void PacketEditPipe(unordered_map<int, Pipe>& pipeline)
{
	cout << "Edit [1] - all pipes / [2] - some pipes: ";
	if (GetCorrectNumber(1, 2) == 1)
	{
		cout << "All pipes [1] - are working; [2] - under repair: ";
		if (GetCorrectNumber(1, 2) == 1)
		{
			for (auto& p : pipeline)
				p.second.statusPipe = 1;	
		}
		else
		{
			for (auto& p : pipeline)
				p.second.statusPipe = 0;
		}
	}
	else
	{
		vector <int> vectID;

		while (true)
		{

			cout << "Enter pipe's id to edit or 0 to complete: ";
			int i = GetCorrectNumber(0, Pipe::MaxIDpipe);
			if (i)
				{
				if (pipeline.count(i) == 0)
					cout << "ERROR! There is no pipe with this id\n";
				else
					vectID.push_back(i);
				}
			else
				break;
		}
			for (int i : vectID)
				pipeline[i].statusPipe = !pipeline[i].statusPipe;
	}
}

int main()
{
	unordered_map <int, Pipe> pipeline = {};
	unordered_map <int, CStation> CSSistem = {};

	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0,11))
		{
		case 1:
		{
			cin.clear();
			system("cls");
			Pipe p;
			cin >> p;
			pipeline.insert({ pID, p });
			break;
		}
		case 2:
		{
			cin.clear();
			system("cls");
			CStation cs;
			cin >> cs;
			CSSistem.insert({ csID, cs });
			//csID++;
			break;
		}
		case 3:
		{
			cin.clear();
			system("cls");
			if ((pipeline.size()!= 0) && (CSSistem.size() == 0))
				{
				for (auto& p : pipeline)
					cout << p.second << endl;
				}
			else if ((pipeline.size() == 0) && (CSSistem.size() != 0))
				{
				for (auto& cs : CSSistem)
					cout << cs.second << endl;
				}
			else if ((pipeline.size() != 0) && (CSSistem.size() != 0))
				{
				for (auto& p : pipeline)
						cout << p.second << endl;
				for (auto& cs : CSSistem)
					cout << cs.second << endl;
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
				Pipe:: EditPipe(SelectPipe(pipeline));
			}
			else cout << "Before editing pipe you should INPUT pipe" << endl;
			break;
		}
		case 5:
		{
			cin.clear();
			system("cls");
			if (CSSistem.size() > 0)
			{
				CStation:: EditStation(SelectCS(CSSistem));
			}
			else cout << "Before editing compressor station you should INPUT compressor station" << endl;
			break;
		}
		case 6:
		{
			cin.clear();
			system("cls");
			string object;
			ofstream fout;
			string fname;
			cout << "Enter file's name: ";
			cin.ignore(10000, '\n');
			getline(cin, fname);
			fout.open(fname + ".txt", ios::out);
			if (fout.is_open())
			{
				for (auto& p : pipeline)
					SavePipe(fout, p.second);
				for (auto& cs : CSSistem)
					SaveStation(fout, cs.second);
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
			string fname;
			cout << "Enter file's name: ";
			cin.ignore(10000, '\n');
			getline(cin, fname);
			fin.open(fname + ".txt", ios::in);
			if (fin.is_open())
			{
				while (!fin.eof())
				{
					getline(fin, object);
					if (object == "PIPE")
					{
						pipeline.insert({ pID, LoadPipe(fin) });
						pID++;
					}
					if (object == "COMPRESSOR STATION")
					{
						CSSistem.insert({ csID, LoadStation(fin) });
						csID++;
					}
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
			else cout << "ERROR! There is no entered pipe!" << endl;
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
			else cout << "ERROR! There is no entered compressor station!" << endl;
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
					break;
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
					break;
				}
				}
			}
			break;
		}
		case 11:
		{
			cin.clear();
			system("cls");
			PacketEditPipe(pipeline);
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