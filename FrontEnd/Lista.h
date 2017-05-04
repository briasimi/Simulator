#pragma once
# include "Nod.h"
class Lista
{
public:
	Lista();
	void push_back(int x1,int y1,int x2,int y2,streetTypes type);
	void push_back(Nod *obj);
	int size();
	Nod * operator [] (int poz);
	void print();
	~Lista();
private:
	Nod *head = nullptr;
	Nod* ultim = nullptr;
	int actualSize = 0;
};

