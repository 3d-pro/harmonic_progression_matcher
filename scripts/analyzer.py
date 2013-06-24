#!/usr/bin/env python
# -*- coding: utf-8 -*- 

# Analyzer script for sonic annotator

import os
import sys
import subprocess

fileList = []
rootdir = sys.argv[1]

#walking through folder
for root, subFolders, files in os.walk(rootdir):
    for file in files:
        if file.endswith('.mp3'):
        	full_path = os.path.join(root, file)
        	p = subprocess.Popen(['sonic-annotator', '-d' , 'vamp:HPA:HPA_LBC:beat_synced_LBC', full_path, '-w', 'csv'], stdout=subprocess.PIPE)
        	p.communicate()
