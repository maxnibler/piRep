 #Maximillian H Nibler
#max.nibler@gmail.com
#https://github.com/maxnibler/

try:
    import sys
    import yfinance as yf

    argLen = len(sys.argv)

    if argLen != 2:
        exit()

    name = sys.argv[1]
    stockTicker = yf.Ticker(name)
    #print("ticker set")
    update = stockTicker.history(period="1d",interval="1m")
    #print("api call made")
    config = open(".config")
    path = config.readline()
    configs = path.split("=")
    path = configs[1].split("\n")
    path = path+"History/"
    path = path+name+"/"+name+"_update.txt"

    #print(path)
    outPath = open(path,'w')

    outPath.write(update.to_string())
    outPath.write("\n")
    outPath.close()
    #print("python out")

except KeyboardInterrupt:
    name = sys.argv[1]
    config = open(".config")
    path = config.readline()
    configs = path.split("=")
    path = configs[1].split("\n")
    path = path+name+"/"+name+"_update.txt"
    outPath = open(path, 'w')
    outPath.write("Terminated\n")
    outPath.close()
