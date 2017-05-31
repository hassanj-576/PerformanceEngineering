import random
import time
import sys
temp=""
N=int(sys.argv[2])
random.seed( time.time() )
f = open(sys.argv[1], 'w')
for row in xrange(0,N):
	temp=""
	temp=temp+str(random.randint(0,1000))+" "
	temp=temp+str(random.randint(0,1000))
	f.write(temp+"\n") 
	


f.close()