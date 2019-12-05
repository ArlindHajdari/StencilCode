#include <iostream>
#include <omp.h>
#include <math.h>

using namespace std;

const int N = 3000;

int** preprocess()
{
	int** A = new int* [N];
	int i;
	#pragma omp parallel private(i) shared (A)
	{
		#pragma omp for
		for (i = 0; i < N; ++i)
			A[i] = new int[N] {};

		#pragma omp for
		for (i = 1; i < N; i++)
		{
			A[i][0] = 150;
			A[0][i] = 250;
		}
	}

	return A;
}

void matrix_tostring(int** a)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
}

void calculate_array(int** A, bool is_parallel)
{
	if (is_parallel)
	{
#pragma omp parallel for
		for (int i = 1; i < N; i++)
			for (int j = 1; j < N; j++)
				A[i][j] = (fabs(sin(A[i - 1][j - 1]))
					+ fabs(sin(A[i][j - 1]))
					+ fabs(sin(A[i - 1][j]))) * 100;
	}
	else {
		for (int i = 1; i < N; i++)
			for (int j = 1; j < N; j++)
				A[i][j] = (fabs(sin(A[i - 1][j - 1]))
					+ fabs(sin(A[i][j - 1]))
					+ fabs(sin(A[i - 1][j]))) * 100;
	}
}

void print_specific_elements(int argc, char ** argv, int ** temp) 
{
	if (argc % 2 == 1) {
		for (int i = 1; i < argc; i = i + 2)
		{
			int firstIndex = atoi(argv[i]);
			int secondIndex = atoi(argv[i + 1]);

			if (firstIndex < N && secondIndex < N)
				cout << "\nA[" << firstIndex << "][" << secondIndex << "]: " << temp[firstIndex][secondIndex];
		}
	}
	else
		cout << "Number of arguments cannot be odd!";
}