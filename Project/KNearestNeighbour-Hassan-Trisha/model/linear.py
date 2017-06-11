from numpy import loadtxt, where
from pylab import scatter, show, legend, xlabel, ylabel
from sklearn.linear_model import LogisticRegression
from sklearn import datasets, linear_model
import pandas as pd
import numpy as np
import sys


if(len(sys.argv)<3):
	print "Please give value of N and k"
	exit()

inputN =int(sys.argv[1])
inputK = int(sys.argv[2])

userInputSelection = np.array([0,inputN,inputK])
userInputCustom = np.array([1,inputN,inputK])

df = pd.read_csv('model.csv')

df.ix[df["Function"]=="EC2", "Function"] = 1
df.ix[df["Function"]=="Main", "Function"] = 0
ec2Df = df[df["Function"] == 1]
mainDf=df[df["Function"] == 0]



data = mainDf.values

np.random.shuffle(data)

X = data[:, 0:3]
y = data[:, 3]

limit = len(X)*0.9
trainingX, testX = X[:limit,:], X[limit:,:]
trainingY, testY = y[:limit], y[limit:]
regr = linear_model.LinearRegression()
regr.fit(trainingX, trainingY)
index=0
allError =[]
for val in testX:
	val=val.reshape(1,-1)
	predictedVal=regr.predict(val)
	error=(predictedVal-testY[index])**2
	allError.append(error)
	index=index+1



print "Mean Error for Selection Algorithm Aglortihm: "+ str( np.mean(allError) ) +" seconds"
userInputSelection=userInputSelection.reshape(1,-1)
print "Time Predicted for Selection Algorithm for Given Input : "+ str((regr.predict(userInputSelection)) )+ " seconds"

#print ec2Df
# ec2Df.is_copy = False
# ec2Df["Nsq"] = ec2Df["N"]*ec2Df["N"]
# ec2Df["totalSq"]=ec2Df["TotalNumber"]*ec2Df["TotalNumber"]
# ec2Df = ec2Df[['Function', 'TotalNumber', 'totalSq', 'N', 'Nsq','ExecutionTime']]

data = ec2Df.values


np.random.shuffle(data)

X = data[:, 0:3]
y = data[:, 3]

limit = len(X)*0.8
trainingX, testX = X[:limit,:], X[limit:,:]
trainingY, testY = y[:limit], y[limit:]
regr = linear_model.LinearRegression()
regr.fit(trainingX, trainingY)
index=0
allError =[]
for val in testX:
	val=val.reshape(1,-1)
	predictedVal=regr.predict(val) 

	error=(predictedVal-testY[index])**2
	#print error
	allError.append(error)
	index=index+1

print "Mean Error for custom Aglortihm: "+ str( np.mean(allError) ) +" seconds"
userInputCustom=userInputCustom.reshape(1,-1)
print "Time Predicted for Selection Algorithm for Given Input : "+ str((regr.predict(userInputSelection)) )+ " seconds"






