//
// Created by Zion on 9/8/2020.
//
#include <limits>
#include <stdio.h>
#include "nbonacci.h"

/* Computes the nth number in the {series}bonacci series
 * unsigned int series: nbonacci series to compute. Fibonacci = 2
 * unsigned int n: nth number to compute
 */
long nbonacci(unsigned int series, unsigned int n)
{
    // Validate
    if (series < 2) {
        printf("Cannot compute %ubonacci number\n", series);
        exit(1);
    }
    if (n < 1) {
        printf("n must be greater than 1");
        exit(1);
    }

    // Base case
    if (n <= series) {
        return 1;
    }

    // nbonacci
    long sum = 0;
    for (unsigned int i = 1; i <= series; ++i) {
        sum += nbonacci(series, n - i);
    }

    return sum;
}

/* Computes the ratio of the given nbonacci series.
 * std::string title: title of series. Used for printed output
 * unsigned int series: index of nbonacci series to compute. Fibonacci = 2
 */
void computeNbonacciRatio(std::string title, unsigned int series)
{
    // Validate
    if (series < 2) {
        printf("Cannot compute %ubonacci number\n", series);
        exit(1);
    }

    static const float MAX_DIFF = 0.000001;
    static const unsigned int MIN_N = 1;

    // Initial values
    long fn = nbonacci(series, MIN_N);
    long fn1 = nbonacci(series, MIN_N+1);

    double prev_ratio = std::numeric_limits<double>::max();
    double ratio = static_cast<double>(fn1) / fn;

    int iters = 1;
    while (std::abs(ratio - prev_ratio) > MAX_DIFF) {
        fn = nbonacci(series, MIN_N+iters);
        fn1 = nbonacci(series, MIN_N+iters+1);

        prev_ratio = ratio;

        ratio = static_cast<double>(fn1) / fn;

        iters++;
    }

    printf("%s ratio approaches %f after %d iterations\n", title.c_str(), ratio, iters);
}


