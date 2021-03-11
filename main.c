#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#include "pi_calculator.h"

#define MAX_THREADS 16

int main(int argc, char *argv[])
{

    // Comprobamos que el numero de argumentos sea correcto
    if (argc != 3)
    {
        printf("usage: %s number_of_threads number_of_points\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Tomamos el numero de puntos
    char *a = argv[2];
    int numberOfPoints = atoi(a);

    if (numberOfPoints <= 0)
    {
        printf("The number of points must be a integer greater than 0\n");
        return EXIT_FAILURE;
    }

    // Tomamos el numero de threads
    char *b = argv[1];
    int numberOfThreads = atoi(b);

    if (numberOfThreads <= 0)
    {
        printf("The number of threads must be a integer greater than 0\n");
        return EXIT_FAILURE;
    }

    // Determinamos el numero de threads
    if (numberOfThreads > MAX_THREADS)
    {
        numberOfThreads = MAX_THREADS;
    }
    if (numberOfPoints < numberOfThreads)
    {
        numberOfThreads = numberOfPoints;
    }

    int numberOfPointsInsideCircle = 0;
    // Calculamos pi
    double timeStart = omp_get_wtime();
    double finalPi = calculatePi(numberOfThreads, numberOfPoints, &numberOfPointsInsideCircle);
    double timeEnd = omp_get_wtime();
    printf("Pi: %f, Time: %gs, Threads: %d, Points inside: %d\n", finalPi, timeEnd - timeStart, numberOfThreads, numberOfPointsInsideCircle);

    return EXIT_SUCCESS;
}