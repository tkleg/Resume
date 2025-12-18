def getOvalFunc( centerX, centerY, a, b ):
    def circleFunc( x ):
        return centerY + (a**2 * (1 - ( (x-centerX)**2 / b**2 ) ) ) ** 0.5
    return circleFunc

def getTriangleFunc( height, startX, endX ):
    def triangleFunc( x ):
        if x < startX or x > endX:
            return 0
        midX = ( startX + endX ) / 2
        if x <= midX:
            slope = height / ( midX - startX )
            return slope * ( x - startX )
        else:
            slope = - height / ( endX - midX )
            return slope * ( x - midX ) + height
    return triangleFunc

centerX = 4
centerY = 0
a = 943.6
b = 30

circleFunc = getOvalFunc( centerX, centerY, a, b )


triangleHeight = 541.4
triangleStartX = -56
triangleEndX = -40

triangleFunc = getTriangleFunc( triangleHeight, triangleStartX, triangleEndX )


def combinedFunc( x, ovalFunc, triangleFunc, ovalStart, ovalEnd, triangleStart, triangleEnd ):
    if x >= ovalStart and x <= ovalEnd:
        return ovalFunc( x )
    elif x >= triangleStart and x <= triangleEnd:
        return triangleFunc( x )
    else:
        return 0

start = -100
end = 100
step = 0.01

with open( "semi_circle.dat", "w" ) as f:
    x = start
    while x <= end:
        y = combinedFunc( x, circleFunc, triangleFunc, centerX - b, centerX + b, triangleStartX, triangleEndX )
        f.write( f"{x} {y}\n" )
        x += step