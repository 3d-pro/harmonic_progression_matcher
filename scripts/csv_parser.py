#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import os
import sys
import csv
import json
import pymongo

fileList = []
rootdir = sys.argv[1]

for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.csv'):
        	full_path = os.path.join(root, file)
        	f = open(full_path, 'r')
        	csvReader = csv.reader(open(full_path, 'rb'), delimiter=',', quotechar='"')
        	for row in csvReader:
        		id = row[0]
        		data = row[1].split(' ')