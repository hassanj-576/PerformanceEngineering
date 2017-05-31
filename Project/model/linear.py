from numpy import loadtxt, where
from pylab import scatter, show, legend, xlabel, ylabel
from sklearn.linear_model import LogisticRegression
from sklearn import datasets, linear_model
import pandas as pd
import numpy as np


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
	print "Actual value: "+str(testY[index])
	print "Predicted Value: "+ str(predictedVal)
	error=(predictedVal-testY[index])**2
	allError.append(error)
	index=index+1


print np.mean(allError)



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




