#pragma once
#include <iostream>
#include <string>

class Pipe
{
public:
	static int MaxIDpipe;
	int idPipe;
	std::string namePipe;
	int lenghtPipe;
	int diametrPipe;
	bool statusPipe;

	Pipe();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
};

