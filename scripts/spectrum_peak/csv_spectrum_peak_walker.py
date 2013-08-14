#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import os
import sys
import csv

fileList = []
rootdir = sys.argv[1]

for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.csv'):
        	full_path = os.path.join(root, file)
        	print 'start: ' + root + '/modified_' + file
        	csvReader = csv.reader(open(full_path, 'rb'), delimiter=',')
        	csvWriter = csv.writer(open(root + '/modified' + file, 'wb'), delimiter=',')
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
			    csvWriter.writerow(modified_spectrum_array)

			    #clean up
			    modified_spectrum_array = []
			    spectrum_array = []
			    i = 1
