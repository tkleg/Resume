from fixedPoint import fixedPoint

def a(x):
    return x * (1 + (7 - x**5)/(x**2))**3
def b(x):
    return x - (x**5-7)/x**2
def c(x):
    return x - (x**5-7)/(5*x**4)
def d(x):
    return x - (x**5-7)/12

start = 1

convergeTimes = [
    ('a', fixedPoint(a, start, 1e-10, 1e10)),
    ('b', fixedPoint(b, start, 1e-10, 1e10)),
    ('c', fixedPoint(c, start, 1e-10, 1e10)),
    ('d', fixedPoint(d, start, 1e-10, 1e10)),
]
for i, (name, result) in enumerate(convergeTimes):
    if isinstance(result, tuple):
        convergeTimes[i] = (name, result[0])  # Extract iteration count
        
fails = [ x for x in convergeTimes if type(x[1]) != int ]
successes = [ x for x in convergeTimes if type(x[1]) == int ]
successes.sort( key=lambda x: x[1] )
print('Successful methods (in order of iterations to converge):', successes)
print('Failed methods:', fails)