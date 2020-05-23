#Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

import sys
import yfinance as yf

argumentLen = len(sys.argv)

flag1 = False

if argumentLen < 5:
    exit()
if argumentLen >= 6:
    flag1 = True
    fileSuff = sys.argv[5]

name = sys.argv[1]
start = sys.argv[2]
end = sys.argv[3]
inter = sys.argv[4]

stockTicker = yf.Ticker(name)

Hist = stockTicker.history(start=start, end=end, interval=inter)

#print(msftHist)
path = "Database/"
path = path+name+"/"
if flag1:
    path = path+name+fileSuff
else:
    path = path+name+"_history.txt"
#print(path)
outPath = open(path,'w')

outPath.write(Hist.to_string())
outPath.write("\n")
outPath.close()
