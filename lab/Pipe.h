#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Pipe
{
	int pID{};
public:
	static int MaxIDpipe;
	std::string namePipe;
	int lenghtPipe;
	int diametrPipe;
	bool statusPipe;
	int CSidOUT;
	int CSidIN;

	int GetID() const;
	void SetID();

	void EditPipe();
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& out, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& in, Pipe& p);
};

