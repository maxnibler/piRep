import requests, json
from config import *

CORE_URL = "https://paper-api.alpaca.markets"
ACCOUNT_URL = "{}/v2/account".format(CORE_URL)
ORDERS_URL = "{}/v2/orders".format(CORE_URL)
HEADERS = {'APCA-API-KEY-ID': API_KEY,'APCA-API-SECRET-KEY': SECRET_KEY}

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

print(getAccount())
order = makeOrder("MSFT", 1, "sell", "market", "gtc")
print(order)
