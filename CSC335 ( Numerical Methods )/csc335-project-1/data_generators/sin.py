from math import sin
import numpy as np

start = -10
end = 10
num_steps = 8000
step = (end - start) / num_steps
with open("sin.dat", "w") as f:
    for x in np.arange(start, end, step):
        f.write(f"{x}\t{sin(x**2)}\n")
    f.write(f"{end}\t{sin(end**2)}\n")
    f.write(f"{0}\t{0}\n")