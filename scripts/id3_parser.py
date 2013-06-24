#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import os
import sys
import eyed3
import pymongo

fileList = []
rootdir = sys.argv[1]

client = pymongo.MongoClient('localhost', 27017)

for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.mp3'):
        	full_path = os.path.join(root, file)
        	audiofile = eyed3.load(full_path)
        	print audiofile.tag.artist + " - " + audiofile.tag.title

