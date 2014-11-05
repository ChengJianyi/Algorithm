#!/usr/bin/env python
# coding=utf-8

lines1 = open('TestSamples.csv').readlines()
i = 0
nl = []
while i < len(lines1):
    line = lines1[i].strip()
    newline = ''
    l = line.split(',')
    for a in l:
        newline += ' %s'%a
    newline = newline+'\n'
    nl.append(newline) 
    i += 1
f1 = open('testsamples.txt', 'w')
f1.writelines(nl)

