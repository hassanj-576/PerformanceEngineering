from numpy import loadtxt, where
from pylab import scatter, show, legend, xlabel, ylabel
from sklearn.linear_model import LogisticRegression
from sklearn import datasets, linear_model
import pandas as pd
import numpy as np

df = pd.read_csv('resultsMerged.csv')
print df
main = df[df["Function"] == "EC2"]
print main
main.to_csv('ec2.csv', index=False)