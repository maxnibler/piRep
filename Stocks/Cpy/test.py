import sys

for i, arg in enumerate(sys.argv):
    print(arg)

f = open('out.txt', 'w')
f.write("Hello World\n")
f.close()
