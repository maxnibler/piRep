#Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

import sys
import yfinance as yf

argumentLen = len(sys.argv)

if argumentLen < 5:
    exit()
if argumentLen >= 6:
    fileName = sys.argv[5]

name = sys.argv[1]
start = sys.argv[2]
end = sys.argv[3]
inter = sys.argv[4]

stockTicker = yf.Ticker(name)

Hist = stockTicker.history(start=start, end=end, interval=inter)

#print(msftHist)
path = "Database/"
path = path+name+"_history.txt"
#print(path)
outPath = open(path,'w')

outPath.write(Hist.to_string())
outPath.write("\n")
outPath.close()
