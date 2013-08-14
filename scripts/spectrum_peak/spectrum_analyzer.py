#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import csv

length = 256
spectrum_array = []
modified_spectrum_array = []
i = 1
index = 0
full_path = 'Bodyslam - Sticker_LogFreqSpec.csv'
f = open(full_path, 'r')
csvReader = csv.reader(open(full_path, 'rb'), delimiter=',')
csvWriter = csv.writer(open('modified_' + full_path, 'wb'), delimiter=',')
for row in csvReader:
	#extracted row from spectrum
    time = row[0]
    while (i <= 256):
    	spectrum_array.append(row[i])
    	i = i+1

    #build modified row of spectrum
    modified_spectrum_array.append(float(time))
    for value in spectrum_array:
        if (max(spectrum_array) == '0' or value == '0'):
            modified_spectrum_array.append(0)
        elif (value != max(spectrum_array)):
            modified_spectrum_array.append(0)
        else:
            modified_spectrum_array.append(50000)
    print modified_spectrum_array
    csvWriter.writerow(modified_spectrum_array)
    
    #clean up
    modified_spectrum_array = []
    spectrum_array = []
    i = 1