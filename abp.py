from pylab import *
from numpy import *
import re
def abp_read_file(fileName):
    fp = open(fileName)
    victimLs = []
    hospitalLs= []
    vPtn = re.compile(r'\d{1,3},\d{1,3},\d{1,3}')
    hPtn = re.compile(r'\d{1,3}')

    line = fp.readline()
    mode = 0
    while(line):
        if mode == 0:
            if 'person' in line:
                mode = 1
            elif 'hospital' in line:
                mode = 2
            line = fp.readline()

        elif mode == 1:
            if vPtn.match(line):
                victim = line.split(",")
                victim = map(int, victim)
                victimLs.append(victim)
                line = fp.readline()
            else:
                mode = 0
        elif mode == 2:
            if hPtn.match(line):
                hospital = line.split()
                hospital = map(int, hospital)
                hospitalLs.append(hospital)
                line = fp.readline()
            else:
                mode = 0 
    victimLs = array(victimLs)
    hospitalLs = array(hospitalLs)
    return victimLs, hospitalLs

def abp_draw(victimLs):
    plot(victimLs[:,:2], '*')
    show()

if __name__ == "__main__":
    victimLs, hospitalLs = abp_read_file('ambusamp2010.txt')
    abp_draw(victimLs)
