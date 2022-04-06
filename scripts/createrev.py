#!/usr/bin/env python3

import inspect
import os, os.path
from colorama import init, Fore, Back, Style

import bashutil

init()

# TOOD: move these to a separate file


# get DIR_MATHQ, the top-level dir for this repo
filename = inspect.getframeinfo(inspect.currentframe()).filename
path     = os.path.dirname(os.path.abspath(filename))
split = path.split("/")
split.pop()
DIR_MATHQ = "/".join(split)
# print(DIR_MATHQ)

# set the rest of the directories and files
VERSION_FILE_MATHQ = DIR_MATHQ + "/versioning/version.mathq"

# get the most recent tag
print("  reading from: "+VERSION_FILE_MATHQ)
env = bashutil.source(VERSION_FILE_MATHQ)
VERSION_MATHQ = env["VERSION_MATHQ"]
# print(VERSION_MATHQ)

TAG_FILE_MATHQ = DIR_MATHQ + "/versioning/tag.mathq"
print("  reading from: "+TAG_FILE_MATHQ)
f = open(TAG_FILE_MATHQ, 'r')
TAG_MATHQ = f.read().strip()
f.close()
# print(TAG_MATHQ)

# create a new tag
TAG_NEW = "v" + VERSION_MATHQ
# TAG_NEW = 'v3.3'
print("  loading git tags for: "+TAG_NEW)
VERSIONS_STR = bashutil.getstdout('git tag -l "{}.*" | cat'.format(TAG_NEW))
VERSIONS = VERSIONS_STR.split("\n")
REV = 0
if len(VERSIONS) == 1 and VERSIONS[0] == '':
    REV = 0
else:    
    REV = len(VERSIONS)
#print("REV={}".format(REV))

FULL_TAG = "{}.{}".format(TAG_NEW, REV)
print("  new tag="+FULL_TAG)

print("  reading from: "+TAG_FILE_MATHQ)
f = open(TAG_FILE_MATHQ, "w")
f.write(FULL_TAG)
f.close()

print("  reading from: "+VERSION_FILE_MATHQ)
f = open(VERSION_FILE_MATHQ, 'r')
version_file_contents = f.read()
f.close()

TAG_ANNOTATION_FILE = DIR_MATHQ + "/versioning/tag.annotation.mathq"
print("  writing to: "+TAG_ANNOTATION_FILE)
f = open(TAG_ANNOTATION_FILE, "w")
doc = FULL_TAG + "\n" + version_file_contents
f.write(doc)
f.close()

# output to screen
print("  VERSION_MATHQ" + Style.RESET_ALL + "=" + Style.BRIGHT + Fore.GREEN + VERSION_MATHQ + Style.RESET_ALL)   
print("  Tag for this commit: " + Style.BRIGHT + Fore.GREEN + FULL_TAG + Style.RESET_ALL)   


# TODO: move to respective make files
# echo -e "Updating "$(BLUE)"$(notdir $(VERSION_HEADER_FILE_MATHQ))"$(DEFCLR)
#VERSION_HEADER_FILE_MATHQ = DIR_MATHQ + "/include/version_mathq.h"
# print(VERSION_HEADER_FILE_MATHQ)
# $(shell echo "inline const char vers_mathq[] = \"`cat $(TAG_FILE_MATHQ)`\";" > $(VERSION_HEADER_FILE_MATHQ) )
# sed -i -e "/__EXAMPLE_CPP__/{r $(DIR_MATHQ)/examples/example.cpp" -e 'd}' $(DIR_MATHQ)/README.md

# documentaiton files
# TODO: move to respective make files
# cp  $(DIR_MATHQ)/doc/README.md  $(DIR_MATHQ)/README.md
# TAG=`cat $(TAG_FILE_MATHQ)` && echo -e " "$(BLUE)"VERSION_MATHQ"$(DEFCLR)"="$${TAG} && sed -i "s/__VERSION_MATHQ__/$${TAG}/g"  $(DIR_MATHQ)/README.md

