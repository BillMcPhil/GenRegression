#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "FileManagement.h"

int countLines(FILE *file)
{
    int count = 1;
    int ch;
    fseek(file, 0, SEEK_SET);
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }

    fseek(file, 0, SEEK_SET);
    return count;
}

void parseFile(FILE *file, double *trainxs, double *trainys, int dataLength)
{
    for (int i = 0; i < dataLength; ++i)
    {
        fscanf(file, "%lf %lf", trainxs + i, trainys + i);
    }
}

void generateDataset(FILE *file, char *function)
{
    if (strcmp(function, "linear") == 0)
    {
        double m = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double b = ((double)rand() / (double)(RAND_MAX / 10)) * (pow(-1, rand() % 2));

        for (int i = 0; i < 20; i++)
        {
            double y = m * i + b;
            y += ((double)rand() / (double)(RAND_MAX / 8)) * (pow(-1, rand() % 2));
            fprintf(file, "%lf %lf\n", (double)i, y);
        }
    }

    else if (strcmp(function, "quadratic") == 0)
    {
        double a = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double b = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double c = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));

        for (float i = -5; i < 5; i += 0.5)
        {
            double y = a * pow(i, 2) + b * i + c;
            y += ((double)rand() / (double)(RAND_MAX / 8)) * (pow(-1, rand() % 2));
            fprintf(file, "%lf %lf\n", (double)i, y);
        }
    }

    else if (strcmp(function, "log") == 0)
    {
        double a = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double b = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));

        for (int i = 1; i < 21; i++)
        {
            double y = a * log(i) + b;
            y += ((double)rand() / (double)(RAND_MAX / 1)) * (pow(-1, rand() % 2));
            fprintf(file, "%lf %lf\n", (double)i, y);
        }
    }

    else if (strcmp(function, "cubic") == 0)
    {
        double a = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double b = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double c = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));
        double d = ((double)rand() / (double)(RAND_MAX / 5)) * (pow(-1, rand() % 2));

        for (float i = -4; i < 4; i += 0.3)
        {
            double y = a * pow(i, 3) + b * pow(i, 2) + c * i + d;
            y += ((double)rand() / (double)(RAND_MAX / 15)) * (pow(-1, rand() % 2));
            fprintf(file, "%lf %lf\n", (double)i, y);
        }
    }
}