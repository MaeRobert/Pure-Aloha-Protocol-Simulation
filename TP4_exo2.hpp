
#include <iostream>
#include <fstream>

float inverse_CDF(float y, float lambda); 
float exponential_random_generator(float lambda); 
int put_in_file(float lambda, int N, FILE* save); 
float find_max(FILE* values_file, int N);
int repartition_values(FILE* values_file, FILE* final_file, int nb_intervals, float maximum, int N);
int random_generator(int N, float lambda, int nb_intervals, FILE* save, FILE* final_file);