#include <iostream>
#include "stencil.h"
using namespace std;

int main(int argc /*Number of arguments*/, char** argv /*Arguments(first argument the current .cpp path)*/)
{
#pragma region [Command Line Arguments]
	for (int i = 1; i < argc; i++)
		cout << argv[i] << "\n";
#pragma endregion

	int** temp = preprocess();

	array_tostring(temp);

	return 0;
}