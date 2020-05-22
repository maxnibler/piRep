#Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

import sys
import yfinance as yf

argumentLen = len(sys.argv)

if argumentLen != 4:
    exit()

name = sys.argv[1]
per = sys.argv[2]
inter = sys.argv[3]

stockTicker = yf.Ticker(name)

Hist = stockTicker.history(period=per, interval=inter)

#print(msftHist)
path = "Database/"
path = path+name+"_history.txt"
#print(path)
outPath = open(path,'w')

outPath.write(Hist.to_string())
outPath.write("\n")
outPath.close()
