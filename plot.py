import numpy as np
import matplotlib.pyplot as plt
import csv
import pandas as pd

# Readdata = open('ECGdata.csv')
# Readcsv = csv.reader(Readdata)
# datalist = list(Readdata)
#print(datalist)

#x=list(range(10000))
#y=datalist[0:10000]
#plt.plot(x, y)
df = pd.read_csv('ECGdata4.csv')
print(df)
print(df[1:])
x=list(range(len(df)))
y=df
plt.plot(x,y[:])
plt.show()