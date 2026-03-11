/*
    This program computes the value of π using numerical integration.
    We evaluate the definite integral:
        4 ∫₀¹ √(1 − x²) dx

    1. Mathematical Background:
    --------------------------------
    The function we are integrating is:
        f(x) = 4√(1 − x²)     |      The curve: y = √(1 − x²) 
    represents the upper half of a circle of radius 1 centered at the origin,
    because the equation of a unit circle is:
        x² + y² = 1
      → y = √(1 − x²)
    From x = 0 to x = 1, this curve represents ONE QUARTER of the unit circle.

    The area of a full circle of radius 1 is: Area = πr² = π(1)² = π

    Therefore:
        ∫₀¹ √(1 − x²)dx = π/4

    Multiplying by 4 gives:
        4 ∫₀¹ √(1 − x²) dx = π
    So the exact analytical result of this integral (using calculus)
    is π.


    NOW, we will approximate this integral using numerical methods.
    2. Numerical Approximation Method:
    --------------------------------

    Since computers cannot compute symbolic integrals directly,
    we approximate the integral using the Midpoint Riemann Sum method.
    We divide the interval [a, b] into N equal subintervals.
        a = 0
        b = 1

    Width of each rectangle: Δx = (b − a) / N

    For each subinterval, we evaluate the function at the midpoint:
        xᵢ = a + (i + 0.5)Δx, where xᵢ is the midpoint of the i-th rectangle.

    Then the Riemann sum approximation becomes:
        ∫₀¹ f(x) dx ≈ Σ f(xᵢ) Δx

    In our case: f(x) = 4√(1 − x²)

    So: π ≈ Σ [ 4√(1 − xᵢ²) ] Δx

    Increasing N makes width/Δx smaller, making rectangles thinner and improving accuracy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // Ensure the user provides the number of intervals
    if (argc < 2)
    {
        printf("Usage: %s <number_of_intervals>\n", argv[0]);
        return 1;
    }

    long N = atol(argv[1]);  // Number of rectangles (subintervals)

    double a = 0.0;  // Lower limit of integration
    double b = 1.0;  // Upper limit of integration

    // Width of each rectangle:
    // Δx = (b − a) / N
    double width = (b - a) / (double)N;

    // sum will accumulate all function evaluations
    double sum = 0.0;

    for (long i = 0; i < N; i++)
    {
        // Midpoint of the i-th rectangle:
        // xᵢ = a + (i + 0.5)Δx
        double x = a + (i + 0.5) * width;

        // Evaluate the function:
        // f(x) = 4√(1 − x²)
        // This represents the height of the rectangle
        sum += 4.0 * sqrt(1.0 - x * x);
    }

    // Multiply accumulated heights by rectangle width:
    // π ≈ Σ f(xᵢ) Δx
    double pi = sum * width;

    printf("Serial Method\n");
    printf("Intervals = %ld\n", N);
    printf("Computed PI ≈ %.10f\n", pi);

    return 0;
}