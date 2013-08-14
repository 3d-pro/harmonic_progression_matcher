#!/usr/bin/env python
# -*- coding: utf-8 -*- import os
import sys
import csv

chordList = []
full_path = 'HPA Generated File/Get_Lucky_Original-HPA.csv'
index = 0
n = 0
f = open(full_path, 'r')
csvReader = csv.reader(open(full_path, 'rb'), delimiter=',')
for row in csvReader:
    time = row[0]
    chord = row[1]
    chordList.append(chord)
print chordList

for i in range(len(chordList)):
	index = 0
	progression = []
	while (index <= 4):
		for n in range(5):
			progression.append(chordList[n])
		index=index+4
		n=n+4
	i=i+4
	print progression