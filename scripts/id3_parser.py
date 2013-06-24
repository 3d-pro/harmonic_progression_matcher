#!/usr/bin/env python
# -*- coding: utf-8 -*- 

# ID3 tag parser

import os
import sys
import eyed3

fileList = []
rootdir = sys.argv[1]

for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.mp3'):
        	full_path = os.path.join(root, file)
        	audiofile = eyed3.load(full_path)
        	print audiofile.tag.artist + " - " + audiofile.tag.title

