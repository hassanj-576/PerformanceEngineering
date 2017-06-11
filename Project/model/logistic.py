from numpy import loadtxt, where
from pylab import scatter, show, legend, xlabel, ylabel
from sklearn.linear_model import LogisticRegression
import pandas as pd
import numpy as np


df = pd.read_csv('model.csv')
print("Total Data: "+str(len(df)))
ec2DF= df.loc[df['Function'] == "EC2"]
mainDF= df.loc[df['Function'] == "Main"]

ec2Final = pd.DataFrame(ec2DF, columns=['TotalNumber', 'N','ExecutionTime']).reset_index()
mainFinal = pd.DataFrame(mainDF, columns=['TotalNumber', 'N','ExecutionTime']).reset_index()
finalDf = pd.DataFrame(ec2DF, columns=['TotalNumber', 'N'])
finalDf['model'] = np.where((ec2Final['ExecutionTime'] <= mainFinal['ExecutionTime']), 1, 0)

print "Data in Model: "+ str(len(finalDf))
X = pd.DataFrame(finalDf, columns=['TotalNumber', 'N'])
y = pd.DataFrame(finalDf, columns=['model'])
xNumpy = X.values
yNumpy = y.values
pos = where(yNumpy == 1)
neg = where(yNumpy == 0)
scatter(xNumpy[pos, 0], xNumpy[pos, 1], marker='o', c='b')
scatter(xNumpy[neg, 0], xNumpy[neg, 1], marker='x', c='r')
xlabel('Total Number Of Data N')
ylabel('k')
legend(['CustomAlgo', 'SelectionAlgo'])
show()


shuffelData =np.hstack((xNumpy,yNumpy))
np.random.shuffle(shuffelData)

X = shuffelData[:, 0:2]
y = shuffelData[:, 2]




limit = len(X)*0.8

trainingX, testX = X[:limit,:], X[limit:,:]
trainingY, testY = y[:limit], y[limit:]



logistic = LogisticRegression()




logistic.fit(trainingX,trainingY)
index=0
correct=0
wrong=0
for val in testX:
	
	val=val.reshape(1,-1)
	if(logistic.predict(val)==testY[index]):
		correct=correct+1
	else:
		wrong=wrong+1

	index=index+1

print "Correct Prediction: "+ str(correct)
print "Wrong Prediction: "+ str(wrong)
errorPercent = (wrong/float(correct))*100
print "Percentage Error of Mode %f" %errorPercent
print "Correct Percentage " +str(100-errorPercent)

