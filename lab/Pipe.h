#pragma once
#include <iostream>
#include <string>

class Pipe
{
public:
	static int MaxIDpipe;
	//int idPipe;
	int pID;
	std::string namePipe;
	int lenghtPipe;
	int diametrPipe;
	bool statusPipe;

	Pipe();

	static void EditPipe(Pipe& p);
	
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
};

