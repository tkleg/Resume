import numpy as np

def generate_peak(x, center, width, height):
    """Return a Gaussian-shaped peak."""
    return height * np.exp(-((x - center) ** 2) / (2 * width ** 2))

def generate_nmr_data(n_points=10000, start=-100, end=100, peaks=None, noise=0.005):
    """
    Generate synthetic NMR-like data.
    :param n_points: number of data points
    :param start: minimum chemical shift (ppm)
    :param end: maximum chemical shift (ppm)
    :param peaks: list of (center, width, height)
    :param noise: standard deviation of random noise
    """
    x = np.linspace(start, end, n_points)
    y = np.zeros_like(x)

    if peaks is None:
        # Default: a few peaks in ppm
        peaks = [(-75, 4, 3200),
                 (-5, 8, 6700),
                 (60, 2.5, 900)]

    for center, width, height in peaks:
        y += generate_peak(x, center, width, height)

    # Add random noise
    y *= np.random.uniform(1-noise, 1+noise, size=y.shape)

    return x, y

def save_nmr_data(filename, x, y):
    """Save NMR data as two columns: chemical shift and intensity."""
    with open(filename, 'w') as f:
        for xi, yi in zip(x, y):
            f.write(f"{xi:.6f}\t{yi:.6f}\n")

if __name__ == "__main__":
    x, y = generate_nmr_data()
    save_nmr_data("sample_nmr.dat", x, y)
    print("✅ Wrote synthetic NMR data to 'sample_nmr.dat'")
