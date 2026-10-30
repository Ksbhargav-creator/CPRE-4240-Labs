def plotf():
    # First, figure out how many lines there are
    fid = open('bessel.data', 'r')
    NumPts = 0
    while True:
        line = fid.readline()
        if not line: break
        NumPts = NumPts+1
    fid.close()

    import numpy as np
    import matplotlib.pyplot as plt

    # Second, read-in all the floats
    x  = np.zeros(NumPts, dtype=float)
    J0 = np.zeros(NumPts, dtype=float)
    fid = open('bessel.data', 'r')
    for k in range(0, NumPts):
        linelist = fid.readline().split()
        x[k]  = float(linelist[0])
        J0[k] = float(linelist[1])
    fid.close()

    # Third, plot the result
    plt.rc("font", size=16)
    plt.figure(1)
    plt.plot(x, J0, color='b', linewidth=2, label='adaptive quadrature')
    try:
        from scipy.special import j0
        plt.plot(x[::10], j0(x[::10]), 'o', color='r', markersize=4, label='scipy j0')
    except ImportError:
        pass
    plt.xlabel('x')
    plt.ylabel(r'$J_0(x)$')
    plt.title('Bessel function $J_0(x)$')
    plt.grid(True)
    plt.legend()
    plt.savefig('bessel.png', dpi=400, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    plotf()
