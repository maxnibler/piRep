import requests, json, sys
from config import *

ACCOUNT_URL = "{}/v2/account".format(CORE_URL)
ORDERS_URL = "{}/v2/orders".format(CORE_URL)
HEADERS = {'APCA-API-KEY-ID': API_KEY,'APCA-API-SECRET-KEY': SECRET_KEY}
config = open(".config",'r')
path = config.readline()
configs = path.split("=")
configs = configs[1].split("\n")
path = configs[0]
PATH = path

argLen = len(sys.argv)

if argLen < 4:
    exit()

sym = sys.argv[1]
quant = sys.argv[2]
buySell = sys.argv[3]

def getAccount():
    r = requests.get(ACCOUNT_URL, headers = HEADERS)
    return json.loads(r.content)

def makeOrder(symbol, qty, side, types, timeInForce):
    data = {
        "symbol": symbol,
        "qty": qty,
        "side": side,
        "type": types,
        "time_in_force": timeInForce
    }
    r = requests.post(ORDERS_URL, json = data, headers = HEADERS)
    return json.loads(r.content)

def logOrder(trade):
    path = PATH+"Orders/"+sym+"/order.txt"
    outPath = open(path,'w')
    outPath.write(json.dumps(trade))
    outPath.write("\n")
    outPath.close()
    
#print(getAccount())
order = makeOrder(sym, quant, buySell, "market", "day")
logOrder(order)
#print(order)
