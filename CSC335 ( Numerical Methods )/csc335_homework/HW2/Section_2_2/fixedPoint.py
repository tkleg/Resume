def fixedPoint(f, p0, tol, maxIter, bounds=None, printPeriod=False):
    i = 1
    p = None
    while( i <= maxIter ):
        try:
            p = f(p0)
            if bounds is not None and (p < bounds[0] or p > bounds[1]):
                return 'Out of bounds'
        except OverflowError:
            return 'Overflow' 
        if abs(p - p0) < tol:
            if printPeriod:
                print(f'Converged to {p}')
            return (i, p)
        i += 1
        p0 = p
    return 'Hit MaxIter'