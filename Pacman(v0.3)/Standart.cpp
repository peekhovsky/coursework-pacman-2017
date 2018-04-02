#include"Map.h"

int** allocateMatrix(unsigned x, unsigned y)
{
	int** pointer = nullptr;
	
	pointer = new int* [y];
	
	for (int i = 0; i < y; i++)
	{
		pointer[i] = new int[x];
	}

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			pointer[i][j] = 0;
		}
	}
	return pointer;
}

void deleteMatrix(int** pointer)
{

	delete[] pointer;
}

void Error(std::string message)
{
	std::cout<<message.c_str()<<std::endl;
}

int Random(int number, int new_int)
{
	//srand(new_int);
	return (rand() % (number));
}