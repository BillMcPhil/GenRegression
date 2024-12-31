#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "pbPlots.h"
#include "supportLib.h"
#include "FileManagement.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    FILE *dataset;
    if (strcmp(argv[1], "generate") == 0)
    {

        // Make sure arguments are all there
        if (argc < 2)
        {
            printf("Wrong number of arguments.");
            return 0;
        }

        // Open a new file in write mode
        dataset = fopen("dataset.txt", "w");
        if (dataset == NULL)
        {
            printf("File open failed1\n");
            return 0;
        }

        // Generate random dataset
        generateDataset(dataset, argv[2]);

        // Close the file and reopen in read mode
        fclose(dataset);
        dataset = fopen("dataset.txt", "r");
    }

    else
    {
        // Open file in read mode
        dataset = fopen(argv[1], "r");
        if (dataset == NULL)
        {
            printf("File Read Failed\n");
            return 1;
        }
    }

    // Set up arrays
    int numLines = countLines(dataset);
    // printf("%d\n", numLines);
    double *xs = malloc(numLines * sizeof(double));
    double *ys = malloc(numLines * sizeof(double));
    double *regression = malloc(numLines * sizeof(double));

    // Parse the file into the data arrays
    parseFile(dataset, xs, ys, numLines);

    // Linear regression
    if (strcmp(argv[2], "linear") == 0)
    {
        double matrix[numLines][2];
        double y[numLines][1];

        for (int i = 0; i < numLines; i++)
        {
            y[i][0] = ys[i];
            matrix[i][0] = 1;
            matrix[i][1] = xs[i];
        }

        double b[2][1];
        leastSquares(numLines, 2, matrix, b, y);
        printf("Least squares solution found at: y = %lfx + %lf\n", b[1][0], b[0][0]);
        for (int i = 0; i < numLines; i++)
        {
            regression[i] = b[1][0] * xs[i] + b[0][0];
        }
    }

    // Quadratic regression
    else if (strcmp(argv[2], "quadratic") == 0)
    {
        double matrix[numLines][3];
        double y[numLines][1];

        for (int i = 0; i < numLines; i++)
        {
            y[i][0] = ys[i];
            matrix[i][0] = 1;
            matrix[i][1] = xs[i];
            matrix[i][2] = pow(xs[i], 2);
        }

        double b[3][1];
        leastSquares(numLines, 3, matrix, b, y);
        printf("Least squares solution found at: y = %lfx^2 + %lfx + %lf\n", b[2][0], b[1][0], b[0][0]);

        for (int i = 0; i < numLines; i++)
        {
            regression[i] = b[2][0] * pow(xs[i], 2) + b[1][0] * xs[i] + b[0][0];
        }
    }

    // Natural log regression
    else if (strcmp(argv[2], "log") == 0)
    {
        numLines -= 1;
        double matrix[numLines][2];
        double y[numLines][1];

        for (int i = 0; i < numLines; i++)
        {
            y[i][0] = ys[i];
            matrix[i][0] = 1;
            matrix[i][1] = log(xs[i]);
        }

        double b[2][1];
        leastSquares(numLines, 2, matrix, b, y);
        printf("Least squares solution found at %lfln(x) + %lf\n", b[1][0], b[0][0]);

        for (int i = 0; i < numLines; i++)
        {
            regression[i] = b[1][0] * log(xs[i]) + b[0][0];
        }
    }

    // Cubic regression
    else if (strcmp(argv[2], "cubic") == 0)
    {
        double matrix[numLines][4];
        double y[numLines][1];

        for (int i = 0; i < numLines; i++)
        {
            y[i][0] = ys[i];
            matrix[i][0] = 1;
            matrix[i][1] = xs[i];
            matrix[i][2] = pow(xs[i], 2);
            matrix[i][3] = pow(xs[i], 3);
        }

        double b[4][1];
        leastSquares(numLines, 4, matrix, b, y);
        printf("Least squares solution found at %lfx^3 + %lfx^2 + %lfx + %lf\n", b[3][0], b[2][0], b[1][0], b[0][0]);

        for (int i = 0; i < numLines; i++)
        {
            regression[i] = b[3][0] * pow(xs[i], 3) + b[2][0] * pow(xs[i], 2) + b[1][0] * xs[i] + b[0][0];
        }
    }

    fclose(dataset);

    // Plot settings for the raw data
    ScatterPlotSeries *dataSeries = GetDefaultScatterPlotSeriesSettings();
    dataSeries->xs = xs;
    dataSeries->xsLength = numLines;
    dataSeries->ysLength = numLines;
    dataSeries->ys = ys;
    dataSeries->linearInterpolation = false;
    dataSeries->color = CreateRGBColor(0, 0, 0);
    dataSeries->pointType = L"dots";
    dataSeries->pointTypeLength = wcslen(dataSeries->pointType);

    // Plot settings for the regression graph

    ScatterPlotSeries *regressionSeries = GetDefaultScatterPlotSeriesSettings();
    regressionSeries->xs = xs;
    regressionSeries->xsLength = numLines - 1;
    regressionSeries->ysLength = numLines - 1;
    regressionSeries->ys = regression;
    regressionSeries->linearInterpolation = true;
    regressionSeries->lineType = L"solid";
    regressionSeries->lineTypeLength = wcslen(regressionSeries->lineType);
    regressionSeries->lineThickness = 2;
    regressionSeries->color = CreateRGBColor(0, 0, 1);

    // Graph settings for the before training graph
    ScatterPlotSettings *beforeSettings = GetDefaultScatterPlotSettings();
    beforeSettings->width = 600;
    beforeSettings->height = 400;
    beforeSettings->autoBoundaries = true;
    beforeSettings->xMax = 70;
    beforeSettings->xMin = 15;
    beforeSettings->yMin = 100;
    beforeSettings->yMax = 160;
    beforeSettings->autoPadding = true;
    beforeSettings->title = L"Raw Data";
    beforeSettings->titleLength = wcslen(beforeSettings->title);
    ScatterPlotSeries *s[] = {dataSeries};
    beforeSettings->scatterPlotSeries = s;
    beforeSettings->scatterPlotSeriesLength = 1;

    // Graph settings for the regression graph
    ScatterPlotSettings *afterSettings = GetDefaultScatterPlotSettings();
    afterSettings->width = 600;
    afterSettings->height = 400;
    afterSettings->autoBoundaries = true;
    afterSettings->xMax = 70;
    afterSettings->xMin = 15;
    afterSettings->yMin = 100;
    afterSettings->yMax = 160;
    afterSettings->autoPadding = true;
    afterSettings->title = L"Regression";
    afterSettings->titleLength = wcslen(afterSettings->title);
    ScatterPlotSeries *t[] = {dataSeries, regressionSeries};
    afterSettings->scatterPlotSeries = t;
    afterSettings->scatterPlotSeriesLength = 2;

    // Graph canvas
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();

    // Draw the before graph
    DrawScatterPlotFromSettings(canvasReference, beforeSettings);

    // Output the before graph into an image
    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, "raw.png");

    // Draw the after graph
    DrawScatterPlotFromSettings(canvasReference, afterSettings);

    // Output the after graph into an image
    pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, "regression.png");

    DeleteImage(canvasReference->image);
    free(xs);
    free(ys);
    free(regression);
}
