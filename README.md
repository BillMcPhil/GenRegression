# GenRegression
A program that can calculate a regression for most basic functions using least squares

This program is partly based off of [LinRegressionModel](https://github.com/BillMcPhil/LinRegressionModel) which I made several months ago, but instead of using neural network principles this time I used 
[least squares](https://en.wikipedia.org/wiki/Least_squares)
in order to be able to generate regressions for a multitude of functions. Currently supported are linear, quadratic, cubic and logarithmic functions. Planning to
also add trigonometric functions soon.

Like my linear regression project, after compiling the code enter the name of a text file with the dataset, as well as specifying which type of regression you 
want (ex. `./main data.txt linear`) . This time it also has the ability to generate a random dataset, which you can specify by just saying "generate" instead of the name of the text file (ex. `./main generate cubic`).

There is also the functions.c file where the matrix operations such as matrix multiplication and Gaussian elimination are available in order to calculate the least squares solution.

Like LinRegressionModel I use [pbPlots](https://github.com/InductiveComputerScience/pbPlots?tab=License-1-ov-file) to graph the datasets and resulting regressions.
