#!/usr/bin/env python
# coding=utf-8
from __future__ import division

l1 = open('result.txt', 'r').readlines()
l2 = open('TestLabels.csv', 'r').readlines()

i = 0
count1 = [0]*10
count2 = [0]*10
while i < len(l1):
    count2[int(l2[i].strip())]+=1
    if l1[i] == l2[i]:
        a = int(l1[i].strip())
        count1[a]+=1
    i+=1

i=0
sum1 = 0
sum2 = 0
count3 = [0]*10
while i < len(count1):
    sum1+=count1[i]
    sum2+=count2[i]
    count3[i] = count1[i]/float(count2[i])
    i+=1
print count1
print count2
print sum1/float(sum2)
print count3
