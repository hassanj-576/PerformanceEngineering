from numpy import loadtxt, where
from pylab import scatter, show, legend, xlabel, ylabel
from sklearn.linear_model import LogisticRegression
from sklearn import datasets, linear_model
import pandas as pd
import numpy as np

df = pd.read_csv('seq.csv')
print df
main = df[df["Function"] == "Main"]
print main
main.to_csv('mainSeq.csv', index=False)