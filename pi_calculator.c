#include "pi_calculator.h"
#include <math.h>
#include <omp.h>
#include <sys/types.h>
#include <unistd.h>
#include "math_utils.h"

double calculatePi(int numberOfThreads, int numberOfPoints, int *numberOfPointsInsideCircle)
{
    omp_set_num_threads(numberOfThreads);

    // Ponemos una seed aleatoria
    setSeed(getpid());
    // Calculamos pi
    // Se va a usar solo un cuarto de circulo, por lo que el resultado final habra que
    // multiplicarlo por 4
    int i = 0;
    int auxNumberOfPointsInsideCircle = 0;
#pragma omp parallel for private(i) reduction(+ \
                                              : auxNumberOfPointsInsideCircle)
    for (i = 0; i < numberOfPoints; i++)
    {
        // Generamos un punto entre 0 y 1
        double x1 = generateRandomDouble(0.0, 1.0);
        double y1 = generateRandomDouble(0.0, 1.0);

        // Medimos la distancia con el centro (0,0)
        double distance = fabs(distanceBetweenPoints(x1, y1, 0, 0));

        // Si la distancia es menor o igual que 1 es que esta dentro del circulo
        // de radio 1
        if (distance <= 1)
        {
            auxNumberOfPointsInsideCircle++;
        }
    }

    *numberOfPointsInsideCircle = auxNumberOfPointsInsideCircle;
    // Ahora solo hay que calcular pi
    return ((double)auxNumberOfPointsInsideCircle / numberOfPoints) * 4;
}