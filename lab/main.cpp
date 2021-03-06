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

Pipe& SelectPipe(unordered_map<int, Pipe>& p)
{
	cout << "Enter pipe id: ";
	int id = GetCorrectNumber<uint64_t>(1, Pipe::MaxIDpipe);
	if (p.count(id) == 0)
		cout << "ERROR! There is no pipe with this id\n";
	else
		return p[id];
}

CStation& SelectCS(unordered_map<int, CStation>& cs)
{
	cout << "Enter compressor station id: ";
	int id = GetCorrectNumber<uint64_t>(1, CStation::MaxIDcs);
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
		<< "8. Delete Pipe or some pipes" << endl
		<< "9. Delete Compressor Station" << endl
		<< "10. Search" << endl
		<< "11. Packet Edit Pipe" << endl
		<< "12. Gaz Transtort System" << endl
		<< "0. Exit" << endl
		<< "Choose action: "<< endl;
}

void Load(ifstream& fin, unordered_map<int, Pipe>& pipeline, unordered_map<int, CStation>& CSSistem)
{
	Pipe p;
	CStation cs;
	int i = 0;
	int kol_p;
	fin >> kol_p;
	for (int k = 1; k <= kol_p; k++)
	{
		fin >> p;
		for (auto& [pID, pipe] : pipeline)
		{
			if (p.GetID() == pID)
			{
				i++;
			}
		}
		if (i == 0)
		{
			p.MaxIDpipe++;
			pipeline.emplace(p.GetID(), p);
		}
		else
		{
			i = 0;
		}
	}

	int j = 0;
	int kol_cs;
	fin >> kol_cs;
	while (kol_cs != 0)
	{
		fin >> cs;
		for (auto& [csID, station] : CSSistem)
		{
			if (cs.GetID() == csID)
				j++;
		}
		if (j == 0)
		{
			cs.MaxIDcs++; 
			CSSistem.emplace(cs.GetID(), cs);
		}
		else
			j = 0;
		--kol_cs;
	}
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
			res.push_back(p.first);
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
		int id = GetCorrectNumber<uint64_t>(1, Pipe::MaxIDpipe);
		if (p.count(id) == 0)
			cout << "ERROR! There is no pipe with this id\n";
		else if (p[id].CSidIN != 0)
			cout << "ERROR! This pipe is working!";
		else p.erase(id);
		break;
	}
	case 2:
	{
		cout << "Delete pipes with status (1 - pipe is working ; 0 - pipe under repair):  " << endl;
		bool status = GetCorrectNumber(0, 1);
		vector <int> vectID = FindPipesByFilter(p, CheckByStatus, status);
		for (auto& pID : vectID)
			cout << pID << p[pID] << endl;

		if (vectID.empty())
		{
			break;
		}
		else
		{
			cout << "Delete [1] - all of this pipes / [2] - some pipes: ";
			if (GetCorrectNumber(1, 2) == 1)
			{
				for (auto& pID : vectID)
					p.erase(pID);
			}
			else
			{
				while (true)
				{
					int i = 0;
					int id;
					cout << "Enter pipe's id to delete or 0 to complete: ";
					cin >> id;
					if (id)
					{
						for (auto& pID : vectID)
						{
							if (id == pID)
							{
								i++;
							}
						}
						if (i == 0)
						{
							cout << "ERROR! There is no pipe with this status and this id";
						}
						else
						{
							p.erase(id);
						}
					}
					else
						break;
				}
			}
		}
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
			res.push_back(cs.first);
		i++;
	}

	if (res.empty())
		cout << "There is no compressor station with this parameter" << endl;

	return res;
}

void DeleteStation(unordered_map<int, CStation>& cs)
{
	cout << "Enter compressor station id: ";
	int id = GetCorrectNumber<uint64_t>(1, CStation::MaxIDcs);
	if (cs.count(id) == 0)
		cout << "ERROR! There is no compressor station with this id\n";
	else if (cs[id].STishoda != 0 || cs[id].STzahoda != 0)
		cout << "ERROR! This station is working!";
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
			int i = GetCorrectNumber(0, (int)pipeline.size());
			if (i)
				{
				if (pipeline.count(i) == 0)
					cout << "ERROR! There is no pipe with this id\n";
				else
				{
					int k = 0;
					for (auto& pID : vectID)
					{
						if (i == pID)
						{
							k++;
						}
					}
					if (k == 0)
					{
						vectID.push_back(i);
					}
					else
					{
						cout << "ERROR! You have already edit this pipe\n ";
					}
				}
				}
			else
				break;
		}
			for (int i : vectID)
				pipeline[i].statusPipe = !pipeline[i].statusPipe;
	}
}

///////////// lab3

void Connect(unordered_map<int, Pipe>& pipeline, unordered_map<int, CStation>& CSSistem)
{
	if ((pipeline.size() > 0) && (CSSistem.size() > 0))
	{
		int IDpipeConnect = Proverka(pipeline, "Enter pipe's id to connect: ", "ERROR! Try again", 1, Pipe::MaxIDpipe, 0);
		if (pipeline[IDpipeConnect].CSidIN == 0 && pipeline[IDpipeConnect].CSidOUT == 0)
		{
			int IDout = Proverka(CSSistem, "Enter compressor station's id you want to pipe out: ", "ERROR! Try again", 1, CStation::MaxIDcs, 0);
			int IDin = Proverka(CSSistem, "Enter compressor station's id you want to pipe in: ", "ERROR! Try again", 1, CStation::MaxIDcs, IDout);
			pipeline[IDpipeConnect].CSidIN = IDin;
			pipeline[IDpipeConnect].CSidOUT = IDout;
			CSSistem[IDin].STzahoda += 1;
			CSSistem[IDout].STishoda += 1;
		}
		else
		{
			cout << "Pipe has been already connected";
		}
	}
	else
	{
		cout << "Trere are not enough pipes and compressor stations to make connection";
	}
}

void PrintSystem(unordered_map<int, Pipe>& pipeline)
{
	for (auto& p : pipeline)
	{
		if (p.second.CSidIN > 0 && p.second.CSidOUT > 0)
		{
			cout << "\nPipe's ID: " << p.first << endl;
			cout << "Pipe is connected" << endl;
			cout << "CS's IDout: " << p.second.CSidOUT << endl;
			cout << "CS's IDin: " << p.second.CSidIN << endl;
		}
		else
		{
			cout << "\nPipe's ID: " << p.first << endl;
			cout << "Pipe isn't connected" << endl;
		}
	}
}

void Disconnect(unordered_map<int, Pipe>& pipeline, unordered_map<int, CStation>& CSSistem)
{
	if (pipeline.size() > 0)
	{
		int IDpipeDisconnect = Proverka(pipeline, "Enter pipe's id to disconnect: ", "ERROR! Try again", 1, Pipe::MaxIDpipe, 0);
		if (pipeline[IDpipeDisconnect].CSidIN == 0)
		{
			cout << "Pipe isn't connected\n" << endl;
		}
		else
		{
			CSSistem[pipeline[IDpipeDisconnect].CSidIN].STzahoda -= 1;
			CSSistem[pipeline[IDpipeDisconnect].CSidOUT].STishoda -= 1;
			pipeline[IDpipeDisconnect].CSidIN = 0;
			pipeline[IDpipeDisconnect].CSidOUT = 0;
		}
	}
	else
		cout << "Trere is no pipe";
}

void sort(unordered_map<int, Pipe> pipeline, unordered_map<int, CStation> CSSistem, vector<int>& tops, vector<int>& edges, vector <int>& result)
{
	int cycleschet = 0;
	int deletedpoints = 0;

	vector <int> markedtops;          //?????????? ???????
	vector <int> markededges;         //????????? ?????
	markedtops.clear();

	bool flag;

	for (auto& cs : tops)
	{
		flag = false;
		markededges.clear();
		if (CSSistem[cs].STzahoda == 0 && CSSistem[cs].STishoda != 0)
		{
			for (auto& p : edges)
			{
				if (pipeline[p].CSidOUT == cs)
				{
					markededges.push_back(p);
				}
			}
			flag = true;
			for (const auto& p : markededges)
			{
				CSSistem[pipeline[p].CSidIN].STzahoda -= 1;
				CSSistem[pipeline[p].CSidOUT].STishoda -= 1;
				pipeline[p].CSidIN = 0;
				pipeline[p].CSidOUT = 0;
				edges.erase(find(edges.begin(), edges.end(), p));
			}
			deletedpoints += 1;
			markedtops.push_back(cs);
		}
		if (CSSistem[cs].STzahoda != 0 && CSSistem[cs].STishoda != 0)
		{
			cycleschet += 1;
		}
		if (CSSistem[cs].STzahoda == 0 && CSSistem[cs].STishoda == 0 && flag == false)
		{
			markedtops.push_back(cs);
		}
	}
	for (const auto& cs : markedtops)
	{
		result.push_back(cs);
		tops.erase(std::find(tops.begin(), tops.end(), cs));
	}
	if (deletedpoints == 0 || cycleschet == size(tops) || tops.empty())
	{
		return;
	}
	sort(pipeline, CSSistem, tops, edges, result);	
}

void TopologicalSort(unordered_map<int, Pipe> pipeline, unordered_map<int, CStation> CSSistem)
{
	vector <int> result;
	vector <int> tops;          //??????? ?????
	vector <int> edges;         //????? ?????
	for (auto& cs : CSSistem)
	{
		if (cs.second.STishoda != 0 || cs.second.STzahoda != 0)
			tops.push_back(cs.first);
	}
	for (auto& p : pipeline)
	{
		if (p.second.CSidIN != 0)
			edges.push_back(p.first);
	}

	int check = size(tops);
	sort(pipeline, CSSistem, tops, edges, result);
	if (!result.empty() && check == size(result))
	{
		std::cout << "Graf was sorted" << endl
			<< "Topological Sort: " << endl;
		for (const auto cs : result)
		{
			std::cout << cs << endl;
		}
	}
	else
	{
		std::cout << "ERROR! Can't sort because of cycle";
	}
}

/////////////// lab4

void ShortestWay(unordered_map<int, Pipe> pipeline, int IDout, int IDin, vector <int> tops)
{
	const int SIZE = tops.size();
	vector<int> resultPath;
	vector<vector<int>> a; //??????? ??????
	a.resize(SIZE);
	vector<int> d;         //???????????? ??????????
	d.resize(SIZE);
	vector<int> v;         //?????????? ???????
	v.resize(SIZE);
	unordered_map<int, int> mapIdIndex;
	int temp, min;
	int minindex;
	int counter = 0;
	
	for (const auto& cs : tops)
		mapIdIndex.emplace(cs, counter++);
	
	for (int i = 0; i < SIZE; i++)  //??????? ??????
		a[i].resize(SIZE);
	for (auto& pipe : pipeline)
		a[mapIdIndex[pipe.second.CSidOUT]][mapIdIndex[pipe.second.CSidIN]] = pipe.second.lenghtPipe;

	for (int i = 0; i < SIZE; i++)  //????????????? ?????? ? ??????????
	{
		d[i] = 10000;
		v[i] = 1;
	}
	int begin_index = mapIdIndex[IDout];
	d[begin_index] = 0;

	// ??? ?????????
	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < SIZE; i++)
		{
			if ((v[i] == 1) && (d[i] < min))    // ???? ??????? ??? ?? ?????? ? ??? ?????? min, ?? ??????????????? ????????
			{
				min = d[i];
				minindex = i;
			}
		}
		// ????????? ????????? ??????????? ??? ? ???????? ???? ??????? ? ?????????? ? ??????? ??????????? ????? ???????
		if (minindex != 10000)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (a[minindex][i] > 0)
				{
					temp = min + a[minindex][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[minindex] = 0;
		}
	} while (minindex < 10000);
	if (d[mapIdIndex[IDin]] == 10000)
		throw - 1;
	int WAY = d[mapIdIndex[IDin]];
	vector<int> ver;                            // ?????? ?????????? ??????
	int end = mapIdIndex[IDin];
	ver.push_back(end);
	int weight = d[end];                        // ??? ???????? ???????
	while (end != begin_index)                  // ???? ?? ????? ?? ????????? ???????
	{
		for (int i = 0; i < SIZE; i++)          // ????????????? ??? ???????
			if (a[i][end] != 0)                 // ???? ????? ????
			{
				int temp = weight - a[i][end];  // ?????????? ??? ???? ?? ?????????? ???????
				if (temp == d[i])               // ???? ??? ?????? ? ????????????, ?????? ?? ???? ??????? ? ??? ???????
				{
					weight = temp;              // ????????? ????? ???
					end = i;                    // ????????? ?????????? ???????
					ver.push_back(i);           // ? ?????????? ?? ? ??????
				}
			}
	}

	// ????? ????
	for (int i = 0; i < ver.size(); i++)
	{
		for (const auto& id : mapIdIndex)
			if (id.second == ver[i])
				resultPath.push_back(id.first);
	}
	std::reverse(resultPath.begin(), resultPath.end());
	
	cout << "The shortest way: " << WAY << '\n';
	for (const auto& id : resultPath)
		cout << "-" << id << "-";
}

int main()
{
	unordered_map <int, Pipe> pipeline = {};
	unordered_map <int, CStation> CSSistem = {};

	while (1)
	{
		PrintMenu();
		switch (GetCorrectNumber(0, 13))
		{
		case 1:
		{
			Pipe p;
			cin.clear();
			system("cls");
			cin >> p;
			pipeline.emplace(p.MaxIDpipe, p);
			break;
		}
		case 2:
		{
			CStation cs;
			cin.clear();
			system("cls");
			cin >> cs;
			CSSistem.emplace(cs.MaxIDcs, cs);
			break;
		}
		case 3:
		{
			cin.clear();
			system("cls");
			if ((pipeline.size() != 0) && (CSSistem.size() == 0))
			{
				for (const auto& [pID, p] : pipeline)
				{
					cout << pID;
					cout << p << endl;
				}
			}
			else if ((pipeline.size() == 0) && (CSSistem.size() != 0))
			{
				for (const auto& [csID, cs] : CSSistem)
				{
					cout << csID;
					cout << cs << endl;
				}
			}
			else if ((pipeline.size() != 0) && (CSSistem.size() != 0))
			{
				for (const auto& [pID, p] : pipeline)
				{
					cout << pID;
					cout << p << endl;
				}
				for (const auto& [csID, cs] : CSSistem)
				{
					cout << csID;
					cout << cs << endl;
				}
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
				SelectPipe(pipeline).EditPipe();
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
				CStation::EditStation(SelectCS(CSSistem));
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
				fout << pipeline.size() << endl;
				for (const auto& [pID, p] : pipeline)
					fout << p;
				fout << CSSistem.size() << endl;
				for (const auto& [csID, cs] : CSSistem)
					fout << cs;
				fout.close();
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
			ifstream fin;
			string fname;
			cout << "Enter file's name: ";
			cin.ignore(10000, '\n');
			getline(cin, fname);
			fin.open(fname + ".txt", ios::in);
			if (fin.is_open())
			{
				Load(fin, pipeline, CSSistem);
				fin.close();
			}
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
		case 12:
		{
			cin.clear();
			system("cls");
			cout << "Choose:\n [1] - to connect CSs with pipes;\n [2] - to show connections;\n [3] - to disconnect CSs with pipes;\n [4] - topological sort: \n";
			switch (GetCorrectNumber(1, 4))
			{
			case 1:
			{
				cin.clear();
				system("cls");
				Connect(pipeline, CSSistem);
				break;
			}
			case 2:
			{
				cin.clear();
				system("cls");
				PrintSystem(pipeline);
				break;
			}
			case 3:
			{
				cin.clear();
				system("cls");
				Disconnect(pipeline, CSSistem);
				break;
			}
			case 4:
			{
				cin.clear();
				system("cls");
				TopologicalSort(pipeline, CSSistem);
				break;
			}
			}
			break;
		}
		case 13:
		{
			cin.clear();
			system("cls");

			int S;
			cout << "Enter the id of compressor station which you want to find a way FROM: ";
			while ((cin >> S).fail() || CSSistem.count(S) == 0 || CSSistem[S].STishoda == 0)
			{
				cin.clear();
				cin.ignore(10000, '\n');
				if (CSSistem.count(S) == 0)
					cout << "ERROR! There is no object with this id\n Try again!\n";
				else if (CSSistem[S].STishoda == 0)
					cout << "ERROR! There is no ways from this CS\n Try again!\n";
			}

			int T;
			cout << "Enter the id of compressor station which you want to find a way TO: ";
			while ((cin >> T).fail() || CSSistem.count(S) == 0 || CSSistem[S].STzahoda == 0)
			{
				cin.clear();
				cin.ignore(10000, '\n');
				if (CSSistem.count(S) == 0)
					cout << "ERROR! There is no object with this id\n Try again!\n";
				else if (CSSistem[S].STzahoda == 0)
					cout << "ERROR! There is no ways to this CS\n Try again!\n";
			}

			vector <int> tops;
			for (auto& cs : CSSistem)
			{
				if (cs.second.STishoda != 0 || cs.second.STzahoda != 0)
					tops.push_back(cs.first);
			}
			try
			{
				ShortestWay(pipeline, S, T, tops);
			}
			catch (int)
			{
				cout << "There is no way from " << S << " to " << T;
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