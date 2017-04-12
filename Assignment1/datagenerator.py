import random
import time
import sys
temp=""
M=int(sys.argv[2])
N=int(sys.argv[3])
random.seed( time.time() )
f = open(sys.argv[1], 'w')
for row in xrange(0,M):
	temp=""
	for column in xrange(0,N):
		temp=temp+str(random.randint(0,100))+" "
	f.write(temp+"\n") 
	


f.close()