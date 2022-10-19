//Simulator of a communication system

// States of the simulator :
// Events of the simulator : 
// Imput parameters of the simulator : 

// Implementation of an exponential distribution random generator 
// We generate N numbers from an exponential distribution 
// We have to search the CDF of the distribution -> f
// put f(x) = y and isolate the x ; x = f-1(y)

// See Inverse Transform Sampling 

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>        /* log*/
#include <iostream>
#include <fstream>

float inverse_CDF(float y, float lambda)
{
    return -(log(1-y))/lambda;
}

float exponential_random_generator(float lambda)
{
    float y = ((float) rand())/((float) RAND_MAX);
    // printf("%f\n",y);
    return inverse_CDF(y, lambda);
}


int put_in_file(float lambda, int N, FILE* save)
{
    // fprintf(save, "Number of tries: %d\n", N);
    for (int i = 0; i<N ; i++){
        fprintf(save, "%f\n", exponential_random_generator(lambda));
    }
    return 0;   
}


float find_max(FILE* values_file, int N)
{
    float max;
    float value; 

    fscanf(values_file, "%f", &value);
    max = value; 

    for(int i = 1 ; i<N ; i++){
        fscanf(values_file, "%f", &value);
        if(value > max){
            max = value;
        }
    }

    return max;
}

int repartition_values(FILE* values_file, FILE* final_file, int nb_intervals, float maximum, int N)
{
    float value;
    int num_interval;
    float length_interval; 
    int length_tab = nb_intervals + 1;
    int tab_repartition [length_tab];

    length_interval = maximum/((float) nb_intervals);

    // Initialize the array
    for(int i = 0 ; i<length_tab ; i++){
        tab_repartition[i] = 0;
    }

    // Treatment of the values obtained earlier
    for(int i = 0 ; i<N ; i++){
        fscanf(values_file, "%f\n", &value);  
        // We determine the interval in which value is 
        // printf("read value is %f, length is %f\n", value, length_interval);
        num_interval = ((int) (value/length_interval));
        tab_repartition[num_interval] ++;
    }

    // Just to check everything is okay
    for(int i = 0 ; i<length_tab ; i++){
        printf("%d\n", tab_repartition[i]);
    }

    for(int i = 0 ; i<length_tab ; i++){
        fprintf(final_file, "%f %d\n", i*length_interval, tab_repartition[i]);
    }

    return 0;
}


int random_generator(int N, float lambda, int nb_intervals, FILE* save, FILE* final_file)
{   
    float max;

    /* initialize random seed: */
    srand (time(NULL));

    // Creation of the values
    put_in_file(lambda, N, save);
    rewind(save);

    // Finding the max of the values
    max = find_max(save, N);
    rewind(save);

    // Finding the repartition of the values
    repartition_values(save, final_file, nb_intervals, max, N);
    rewind(save);
    rewind(final_file);

    return 0;
}

/*
float representation(int N, float lambda)
{
    float numbers [N];
    float nb;
    for (int i = 0; i<N ; i++){
        numbers[i] = 0;
    }
    nb = exponential_random_generator(lambda);
    numbers[int(nb)]++;
    return 0;
}
*/

