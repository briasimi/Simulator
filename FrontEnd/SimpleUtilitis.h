# include <iostream>
void inline realloc_simple_buffer(char *&ptr, int size)
{if (ptr != nullptr) { delete ptr; ptr = new char[size]; }}
void inline deleteTokendeBuffersEx(char *&buffer, int lenght)
{
	for (int i = 0;i < lenght;i++)
		buffer[i] = 'a';
	delete buffer;
}
//void writeBinary(char*file)
//{
//	ofstream fil;
//	fil.open("map.jpg", ofstream::out | ofstream::binary);
//	fil.write(file, 40000);
//}