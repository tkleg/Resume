from fixedPoint import fixedPoint
from math import sin, cos, e

def a(x):
    return 2 + sin(x) - x
def b(x):
    return x**3 - 2 * x - 5
def c(x):
    return 3 * x**2 - e**x
def d(x):
    return x - cos(x)

tol = 1e-5
maxIter = 1000

convergeTimes = [
    ('a', fixedPoint(a, 2.5, tol, maxIter, bounds=(2, 3))),
    ('b', fixedPoint(b, 2.5, tol, maxIter, bounds=(2, 3))),
    ('c', fixedPoint(c, 0, tol, maxIter)),
    ('d', fixedPoint(d, 0, tol, maxIter))
]
for i, (name, result) in enumerate(convergeTimes):
    if isinstance(result, tuple):
        convergeTimes[i] = (name, result[0])  # Extract iteration count

print( convergeTimes )