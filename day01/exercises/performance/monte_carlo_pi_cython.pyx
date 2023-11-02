from libc.stdlib cimport rand, srand, RAND_MAX
import random

cpdef double monte_carlo_pi_cython(int num_points):
    cdef int inside_circle = 0
    cdef double x, y

    srand(42)

    for _ in range(num_points):
        x = rand() / RAND_MAX
        y = rand() / RAND_MAX
        if x * x + y * y <= 1:
            inside_circle += 1

    return (inside_circle / num_points) * 4
