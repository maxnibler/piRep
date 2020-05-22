#Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

import sys
import yfinance as yf

argumentLen = len(sys.argv)
print(argumentLen)
if argumentLen > 1:
    for i, arg in enumerate(sys.argv):
        print(arg)

name = sys.argv[1]
per = sys.argv[2]
inter = sys.argv[3]

msft = yf.Ticker(name)

msftHist = msft.history(period=per, interval=inter)

#print(msftHist)
path = "Database/"
path = path+name+"_history.txt"
print(path)
msftout = open(path,'w')

msftout.write(msftHist.to_string())
msftout.write("\n")
msftout.close()
