import numpy as np
from fixedPoint import fixedPoint
import math
from collections import Counter
import inspect
from sys import stdout

def c_g_1(x):
    return math.sqrt(math.e**x / 3)

def d_g_1(x):
    return math.cos(x)

def a_g_1(x):
    return 2 + math.sin(x)

def b_g_1(x):
    return (x**3 - 5) / 2
def b_g_2(x):
    return math.pow(2*x + 5, 1/3)

def findRootAndCount(f, bounds):
    roots = set()
    iterations = Counter()
    spots = np.linspace(bounds[0], bounds[1], 100000)
    numFails = 0
    for spot in spots:
        result = fixedPoint( f, spot, 1e-5, 1000)
        if type(result) == tuple:
            roots.add( result[1] )
            iterations[result[0]] += 1
        else:
            numFails += 1
    print( inspect.getsource(f), end = '' )
    print( "Bounds:", bounds )
    print( 'Root found', sum(roots) / len(roots) )
    print( iterations )
    print( 'Weighted average of iterations:', 
          sum( k * v for k, v in iterations.items() ) / sum( iterations.values() ) )
    print( 'Number of starting points that failed:', numFails )
    print()

findRootAndCount(d_g_1, (-1, 1))
# d_g_1 used
# Root found 0.7390855725964666
# Counter({29: 29434, 28: 19614, 30: 15306, 27: 12044, 26: 7820, 25: 5186, 24: 3468, 23: 2330, 22: 1568, 21: 1054, 20: 712, 19: 478, 18: 320, 17: 218, 16: 146, 15: 98, 14: 68, 13: 44, 12: 30, 11: 20, 10: 14, 9: 8, 8: 8, 7: 4, 6: 2, 3: 2, 2: 2, 5: 2})
# Weighted average of iterations: 27.52602
# Number of starting points that failed: 0
# Mathematica: FindRoot[x-Cos[x]==0,{x,0}] gave {x->0.739085}

findRootAndCount(c_g_1, (0.5, 1))
# c_g_1 used
# Root found 0.9100040265366686
# Counter({13: 29980, 14: 29724, 12: 20987, 11: 10527, 10: 4786, 9: 2178, 8: 991, 7: 451, 6: 205, 5: 93, 4: 42, 3: 20, 2: 9, 1: 7})
# Weighted average of iterations: 12.54012
# Number of starting points that failed: 0
# Mathematica: FindRoot[3x^2-Exp[x]==0,{x,1}] gave {x->0.910008}

findRootAndCount(a_g_1, (2, 3))
# a_g_1 used
# Root found 2.5541958723301703
# Counter({62: 21689, 61: 14977, 60: 11207, 59: 8733, 58: 6961, 57: 5633, 56: 4599, 63: 4049, 55: 3777, 54: 3118, 53: 2578, 52: 2137, 51: 1775, 50: 1473, 49: 1225, 48: 1019, 47: 847, 46: 705, 45: 587, 44: 487, 43: 407, 42: 338, 41: 282, 40: 233, 39: 196, 38: 162, 37: 135, 36: 112, 35: 94, 34: 78, 33: 64, 32: 54, 31: 46, 30: 38, 29: 30, 28: 26, 27: 22, 26: 18, 25: 14, 24: 14, 23: 10, 22: 8, 21: 8, 20: 6, 19: 4, 18: 4, 17: 4, 15: 4, 16: 2, 14: 2, 12: 2, 11: 2, 5: 2, 9: 1, 1: 1, 8: 1})
# Weighted average of iterations: 57.92695
# Mathematica: FindRoot[2+Sin[x]-x==0,{x,1}] gave {x->2.5542}
# My calculator gave me 2.5541959528371
# I will be using 2.5542 for the filter number as this is rounded to 10^-5

findRootAndCount(b_g_2, (2, 3))
# b_g_2 used
# b_g_1 did not converge for any starting points in (2,3)
# Root found 2.094552269176937
# Counter({7: 75809, 6: 19768, 5: 3751, 4: 569, 3: 88, 2: 12, 1: 3})
# Weighted average of iterations: 6.70593
# Number of starting points that failed: 0
# Mathematica: FindRoot[x^3-2x-5==0,{x,1}] gave {x->2.09455}