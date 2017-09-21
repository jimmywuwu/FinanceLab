from bs4 import BeautifulSoup
import urllib.request
import locale
import csv

locale.setlocale( locale.LC_ALL, 'en_US.UTF-8' ) 



html=urllib.request.urlopen("http://www.twse.com.tw/exchangeReport/MI_5MINS_INDEX?response=html&date=20170525")
soup = BeautifulSoup(html, 'html.parser')
now=datetime.datetime.now().strftime("%Y%m%d")
# print(soup.prettify())
f=open(now+"_pricedata.csv","w")
w=csv.writer(f)

# write for header

header=[td.text for td in soup.find_all('tr')[1].find_all('td')]
w.writerow(header)
#

for child in soup.find("tbody").find_all("tr"):
	w.writerow([td.text for td in child.find_all('td')])

f.close()






f2=open(now+"weight.csv","w")
w=csv.writer(f2)

html2=urllib.request.urlopen('http://www.taifex.com.tw/chinese/9/9_7_1.asp')
soup2=BeautifulSoup(html,'html.parser')
n=len(soup2.find_all(attrs={"style":"vnd: 0.000%"}))

for child in soup2.find_all("tr",attrs={"valign":"bottom"}):
    w.writerow([td.text for td in child.find_all('td')])

header=[a.text for a in soup2.find_all("tr",attrs={"valign":"bottom"})]





