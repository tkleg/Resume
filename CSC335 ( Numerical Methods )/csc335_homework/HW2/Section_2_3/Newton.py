def newtonMethod(f, df, p0, tol, maxiter):
    i = 1
    while i <= maxiter:
        try:
            p = p0 - f(p0)/df(p0)
        except OverflowError:
            return 'Overflow Error'
        if abs( p - p0 ) < tol:
            return (i, p)
        i += 1
        p0 = p
    return 'Max Iterations hit'        