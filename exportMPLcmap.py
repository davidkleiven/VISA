from matplotlib import cm as cm
import numpy as np

name = "inferno"
fname = "cmap.csv"
cmap = cm.get_cmap( name, 255 )
rgb = np.zeros((cmap.N,3))
for i in range( 0, cmap.N ):
    rgb[i,:] = cmap(i)[:3]

out = open( fname, 'w' )
for i in range(0,len(rgb[:,0])):
    out.write("{%.4f,%.4f,%.4f},\n"%(rgb[i,0],rgb[i,1],rgb[i,2]))
out.close()
