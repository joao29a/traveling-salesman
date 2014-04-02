#!/usr/bin/python

from sys import argv
from random import random

#generate a complete graph
def main():
    if len(argv) > 3:
        f = open(argv[1], 'w')
        for i in range(1, int(argv[2]) + 1):
            pos_x = random()*int(argv[3]) + 1
            pos_y = random()*int(argv[3]) + 1
            if (.01 > random()):
                pos_x = -pos_x
            if (.01 > random()):
                pos_y = -pos_y
            f.write("%d %d %d\n" % (i, pos_x, pos_y))
        f.close()
    else:
        print "Insert file name, total vertices, max distance\n"

if __name__ == '__main__':
    main()
