#include "Nod.h"



Nod::Nod()
{
}

Nod::Nod(int x1, int y1, int x2, int y2,streetTypes type)
{
	xStart = x1;
	yStart = y1;
	xFinal = x2;
	yFinal = y2;
	this->type = type;
}


Nod::~Nod()
{
}
