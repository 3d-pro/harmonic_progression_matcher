#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import os
import sys
import csv
import json

fileList = []
chordList = ['N', 'D#:min', 'D:min', 'C#:min', 'F#:min/C#', 'F#:min', 'B:min', 'D:maj', 'C#:maj', 'E:maj', 'A:maj', 'B:maj', 'C:maj', 'Ab:maj/G#', 'F#:maj', 'G:min', 'G:maj', 'E:min', 'Bb:min/A#', 'Ab:min/D#']
rootdir = sys.argv[1]

for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.csv'):
        	full_path = os.path.join(root, file)
        	print full_path
        	f = open(full_path, 'r')
        	csvReader = csv.reader(open(full_path, 'rb'), delimiter=',')
        	for row in csvReader:
        		time = row[0]
        		chord = row[1]
        		if chord in chordList:
        			continue
        		else:
        			chordList.append(chord)
        	print chordList

