import numpy as np
from matplotlib import pyplot as plt
import sys

def main( argv ):
    fname = ""
    for arg in argv:
        if ( arg.find("--file=") != -1 ):
            fname = arg.split("--file=")[1]
        elif ( arg.find("--help") != -1 ):
            print ("Usage: python plot1DFiltered.py --file<fname>")
            print ("help: Print this message")
            print ("file: File containing the filetered and the unfiltered signal")
            return
        else:
            print ("Unknown argument %s"%(arg))
            return
    if ( fname == "" ):
        print ("No file given!")
        return

    unfiltered, filtered = np.loadtxt( fname, delimiter=",", unpack=True )
    fig = plt.figure()
    ax = fig.add_subplot(211)
    ax.plot( unfiltered, color="black", label="Unfiltered")
    ax.plot( filtered, color="red", label="filtered")
    ax.legend(loc="upper right")

    fftU = np.fft.fft( unfiltered )
    fftF = np.fft.fft( filtered )
    fftU = np.fft.fftshift( fftU )
    fftF = np.fft.fftshift( fftF )
    ax2 = fig.add_subplot(212)
    ax2.plot( np.abs(fftU), color="black", label="Unfiltered")
    ax2.plot( np.abs(fftF), color="red", label="filtered")
    plt.show()

if __name__ == "__main__":
    main( sys.argv[1:] )
