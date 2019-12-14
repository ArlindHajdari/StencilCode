#include <iostream>
#include <omp.h>
#include <math.h>

using namespace std;

float** preprocess(int matrix_size)
{
	float** A = new float* [matrix_size];
	int i;
	#pragma omp parallel private(i)
	{
		#pragma omp for
		for (i = 0; i < matrix_size; ++i)
		{
			A[i] = new float[matrix_size] {};
			A[i][0] = 150;
			A[0][i] = 250;
		}
	}

	A[0][0] = 0;

	return A;
}

void matrix_tostring(float** a, int matrix_size)
{
	for (int i = 0; i < matrix_size; i++)
	{
		cout << "\n";
		for (int j = 0; j < matrix_size; j++) {
			cout << a[i][j] << "\t";
		}
	}
}

void parallel_calculation(float** A, int matrix_size, int number_of_threads) 
{
	for (int i = 2; i < matrix_size + matrix_size; i++)
	{
		if (i <= matrix_size)
		{
			#pragma omp parallel for num_threads(number_of_threads)
			for (int j = 1; j < i; j++)
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1]))
					+ fabs(sin(A[i - j][j - 1]))
					+ fabs(sin(A[i - j - 1][j]))) * 100;
		}
		else {
			#pragma omp parallel for num_threads(number_of_threads)
			for (int j = matrix_size - 1; j > i - matrix_size; j--)
				A[i - j][j] = (fabs(sin(A[i - j - 1][j - 1]))
					+ fabs(sin(A[i - j][j - 1]))
					+ fabs(sin(A[i - j - 1][j]))) * 100;
		}
	}
}

void calculate_array(float** A, bool is_parallel, int matrix_size, int number_of_threads = 4)
{
	if (is_parallel)
	{
		parallel_calculation(A, matrix_size, number_of_threads);
	}
	else {
		for (int i = 1; i < matrix_size; i++)
			for (int j = 1; j < matrix_size; j++)
				A[i][j] = (fabs(sin(A[i - 1][j - 1]))
					+ fabs(sin(A[i][j - 1]))
					+ fabs(sin(A[i - 1][j]))) * 100;
	}
}

void print_specific_elements(int argc, char ** argv, float** temp, int matrix_size)
{
	if (argc % 2 == 1) {
		for (int i = 1; i < argc; i = i + 2)
		{
			int firstIndex = atoi(argv[i]);
			int secondIndex = atoi(argv[i + 1]);

			if (firstIndex < matrix_size && secondIndex < matrix_size)
				cout << "\nA[" << firstIndex << "][" << secondIndex << "]: " << temp[firstIndex][secondIndex];
		}
	}
	else
		cout << "Number of arguments cannot be odd!";
}