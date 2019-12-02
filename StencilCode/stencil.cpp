#include <iostream>
using namespace std;

const int N = 8;

int ** preprocess()
{
	int** a = new int* [N];
	for (int i = 0; i < N; ++i)
		a[i] = new int[N] {};

	for (int i = 1; i < N; i++)
	{
		a[i][0] = 155;
		a[0][i] = 255;
	}

	return a;
}

void array_tostring(int ** a)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
}