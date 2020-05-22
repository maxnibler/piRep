#Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

import sys
import requests as req
import yfinance as yf

msft = yf.Ticker("MSFT")

msftHist = msft.history(period="1d", interval="5m")

#print(msftHist.to_string())

msftout = open('out.txt','a')

msftout.write(msftHist.to_string())

msftout.close()
