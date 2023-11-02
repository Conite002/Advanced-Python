from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules = cythonize(["poly_cy.pyx", "fib_cy.pyx", "monte_carlo_pi_cython.pyx"])
)