#pragma once

float** preprocess(int matrix_size);
void matrix_tostring(float** a, int matrix_size);
void calculate_array(float** A, bool is_parallel, int matrix_size, int number_of_threads = 4);
void print_specific_elements(int argc, char** argv, float** temp, int matrix_size);
void parallel_calculation(float** A, int matrix_size, int number_of_threads);