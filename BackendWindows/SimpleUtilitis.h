# include <iostream>
/*# define realloc_simple_buffer (char *&ptr, int size)\
					{if (ptr!=nullptr) {delete ptr; ptr=new char[size];}}*/
void inline realloc_simple_buffer(char *&ptr, int size)
{if (ptr != nullptr) { delete ptr; ptr = new char[size]; }}