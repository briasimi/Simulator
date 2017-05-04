#pragma once
# include <iostream>
# include "NewTypes.h"
using namespace std;
class Nod
{
public:
	Nod();
	Nod(int x1, int y1,int x2,int y2 ,streetTypes type);
	~Nod();

public:
	int xStart;
	int yStart;
	int xFinal;
	int yFinal;
	streetTypes type;
	Nod *next=nullptr;

};

