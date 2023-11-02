# fib_cy.pyx

cpdef long long  fib_cy(int n):
    cdef long long a, b, temp
    a = 0
    b = 1

    for i in range(n):
        a, b = a + b, a
    return a    