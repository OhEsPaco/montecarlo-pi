#include "math_utils.h"
#include <stdio.h>
#include <math.h>

unsigned int seed = 1;

// rand no funciona bien en paralelo, asi que he buscado otra solucion
// https://www.bnl.gov/bnlhpc2013/files/pdf/OpenMPTutorial.pdf
// https://en.wikipedia.org/wiki/Lehmer_random_number_generator

void setSeed(int newSeed)
{
    if (newSeed >= 1)
    {
#pragma omp threadprivate(seed)
        seed = newSeed;
    }
}

double generateRandomDouble(double min, double max)
{
#pragma omp threadprivate(seed)
    seed = seed * 1103515245 + 67890;
    unsigned int rand = ((unsigned)(seed / 65536) % 32768);
    double randomDouble = rand / (double)32768;
    return (max - min) * randomDouble + min;
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
