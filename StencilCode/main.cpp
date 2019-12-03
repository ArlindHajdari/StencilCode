#include <iostream>
#include "stencil.h"
#include "omp.h"

using namespace std;

int main(int argc /*Number of arguments*/, char** argv /*Arguments(first argument the current .cpp path)*/)
{
	omp_set_num_threads(4);
	double start = omp_get_wtime();

	int** temp = preprocess();
	calculate_array(temp, false);

	double end = omp_get_wtime();

	//array_tostring(temp);
	print_specific_elements(argc, argv, temp);
	
	cout << "Time elapsed: " << end - start;
	delete[] temp;
	return 0;
}