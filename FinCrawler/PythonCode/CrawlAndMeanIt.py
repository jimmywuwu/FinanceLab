from bs4 import BeautifulSoup
import urllib.request
import locale
import numpy as np
import pandas as pd
import matplotlib
from ggplot import *

html=urllib.request.urlopen("http://www.twse.com.tw/exchangeReport/MI_5MINS_INDEX?response=html&date=20170609")
soup = BeautifulSoup(html, 'html.parser')
locale.setlocale( locale.LC_ALL, 'en_US.UTF-8') 

#資料採集
#注意find("tbody")，此行若少會採集到表頭，表頭只有一格所以會產生error
a=[]
price=[locale.atof(td) for child in soup.find("tbody").find_all("tr") for td in child.find_all('td')[1] ]
time =[td for child in soup.find("tbody").find_all("tr") for td in child.find_all('td')[0] ]

# 採集的資料整理成可以處理的資料格式

pdPrice=pd.DataFrame(price)
pdTime=pd.DataFrame(time)
Price_dataFrame=pd.concat([pdTime,pdPrice],axis=1) # pd.concat裡面要放pandas dadframe
Price_dataFrame.columns=["time","price"]

# pandas DataFrame取用1到100row
Price_dataFrame.ix[1:100,:]# 可以用"名字"叫
Price_dataFrame.iloc[1:100,:]#只能用數字叫
Price_dataFrame['price'] 
Price_dataFrame['time']
Price_dataFrame.describe()
# np.mean(TimeSeries['price']) # 計算price之平均




import plotly.plotly as py
import plotly.graph_objs as go
#畫圖前須執行%pylab
#Series Object
PriceTimeSeries=pd.Series(price,index=time) #需arg需帶list
pd.rolling_mean(PriceTimeSeries,window=12).plot()
pd.rolling_mean(PriceTimeSeries,window=120).plot()

ggplot(aes(x='date', y='Price'), data=PriceTimeSeries) +\
    geom_line() +\
    stat_smooth(colour='blue', span=0.2)
qplot(PriceTimeSeries)

PriceTimeSeries.boxplot()
#差分

#ACf

#PACf

#






