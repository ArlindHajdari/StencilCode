#include <iostream>
#include "stencil.h"
#include "omp.h"

using namespace std;

int main(int argc /*Number of arguments*/, char** argv /*Arguments(first argument the current .cpp path)*/)
{
#pragma region [Asynchronous]
	omp_set_num_threads(4);
	double start_asynchronous = omp_get_wtime();

	int** temp_asynchronous = preprocess();
	calculate_array(temp_asynchronous, true);

	double end_asynchronous = omp_get_wtime();

	//matrix_tostring(temp);
	print_specific_elements(argc, argv, temp_asynchronous);

	cout << "\nTime elapsed asynchronous: " << end_asynchronous - start_asynchronous;

	delete[] temp_asynchronous;
#pragma endregion [Asynchronous]

#pragma region [Synchronous]
	double start_synchronous = omp_get_wtime();

	int** temp_synchronous = preprocess();
	calculate_array(temp_synchronous, false);

	double end_synchronous = omp_get_wtime();

	print_specific_elements(argc, argv, temp_synchronous);

	cout << "\nTime elapsed synchronous: " << end_synchronous - start_synchronous;

	delete[] temp_synchronous;
#pragma endregion [Synchronous]
	return 0;
}