#include <iostream>
#include "stencil.h"
#include "omp.h"

using namespace std;

//const int N = 8192;
//const int N = 20000;
const int N = 3001;
//const int N = 10;

const int number_of_threads = 8;

int main(int argc /*Number of arguments*/, char** argv /*Arguments(first argument the current .cpp path)*/)
{
	float** temp_asynchronous = preprocess(N);
	float** temp_synchronous = new float* [N];
	memcpy(temp_synchronous, temp_asynchronous, sizeof(int) * N);

#pragma region [Asynchronous]
	double start_asynchronous = omp_get_wtime();
	
	calculate_array(temp_asynchronous, true, N, number_of_threads);
	//matrix_tostring(temp_asynchronous, N);

	double end_asynchronous = omp_get_wtime();
	print_specific_elements(argc, argv, temp_asynchronous, N);

	cout << "\nTime elapsed asynchronous: " << end_asynchronous - start_asynchronous;

	delete[] temp_asynchronous;
#pragma endregion [Asynchronous]

#pragma region [Synchronous]
	double start_synchronous = omp_get_wtime();

	calculate_array(temp_synchronous, false, N);
	//matrix_tostring(temp_synchronous,N);

	double end_synchronous = omp_get_wtime();

	print_specific_elements(argc, argv, temp_synchronous, N);

	cout << "\nTime elapsed synchronous: " << end_synchronous - start_synchronous;

	delete[] temp_synchronous;
#pragma endregion [Synchronous]

	return 0;
}