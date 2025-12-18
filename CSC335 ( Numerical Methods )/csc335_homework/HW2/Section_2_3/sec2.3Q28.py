from Newton import newtonMethod
import math

def c_toSolve(t):
    return math.e / 3 * t * math.exp(-t/3) - 0.25

def c_dt(t):
    return math.e / 3 * math.exp(-t/3) * (1 - t/3)

print(newtonMethod(c_toSolve, c_dt, 5, 1e-5, 10000))
# (5, 11.077903586669088)