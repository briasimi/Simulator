#include "Lista.h"



Lista::Lista()
{
}

void Lista::push_back(int x1, int y1, int x2, int y2, streetTypes type)
{
	Nod *nod = new Nod(x1, y1,x2,y2, type);
	this->push_back(nod);
}

void Lista::push_back(Nod * obj)
{
	this->actualSize++;
	if (head == nullptr)
	{
		head = obj;
		ultim = head;
		head->next = nullptr;
	}
	else
	{
		ultim->next = obj;
		ultim->next->next = nullptr;
		ultim = ultim->next;
	}
}

int Lista::size()
{
	return actualSize;
}

Nod * Lista::operator[](int poz)
{
	if (poz<0||poz>=actualSize)
		return nullptr;
	else
	{
		Nod *index;
		index = head;
		int contor = 0;
		while (index != nullptr)
		{
			if (poz == contor)
				return index;
			contor++;
			index = index->next;
		}
	}
	return nullptr;
}

void Lista::print()
{
	Nod *index;
	index = head;
	while (index != nullptr)
	{
		std::cout << index->xStart << " " << index->yStart << " " << index->xFinal << " " << index->xFinal << endl;
		index = index->next;
	}
}



Lista::~Lista()
{
}
