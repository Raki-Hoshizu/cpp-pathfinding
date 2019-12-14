import sys
import random
import math
if(len(sys.argv)==1):
	print("python genGraphe.py housenumber outgoingdegforeachhouse >> filetosavein")
	sys.exit()

housenumber=int(sys.argv[1])
outDeg=int(sys.argv[2])
MAPsize = housenumber * 3
print("o no")
print("v {}".format(housenumber))

MAPlocation = [i for i in range(MAPsize)]; 
houses = [i for i in range(housenumber)];
houseCoords = [random.sample(MAPlocation,k=housenumber),random.sample(MAPlocation,k=housenumber)]

for i in houses:
	print("m {} {} {}".format(i+1,houseCoords[0][i],houseCoords[1][i]))

#edges = [random.sample(houses,k=outDeg),random.sample(houses,k=outDeg)]
Edge_sources = [[] for i in range(housenumber+1)]

for src in houses:
	for dst in random.sample(houses,outDeg):
		if src!=dst:
			Edge_sources[src].append(dst)

for src, srclist in enumerate(Edge_sources):
	for dst in srclist:
		#print("e {} {} ".format(src,dst))
		srcx=float(houseCoords[0][src])
		srcy=float(houseCoords[1][src])
		dstx=float(houseCoords[0][dst])
		dsty=float(houseCoords[1][dst])

		dist = (math.sqrt(((dstx-srcx)**2)+((dsty-srcy)**2)))
		#print("e {}({},{}) {}({},{}) dist={}".format(src,srcx,srcy,dst,dstx,dsty,dist))

		print("e {} {} {:.2f}".format(src+1,dst+1,dist))