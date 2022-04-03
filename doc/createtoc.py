#!/usr/bin/python

import sys
import datetime
import json

today = datetime.datetime.now().strftime("%d %B %Y")
#print(today)

usage="""
USAGE: python3 createtoc.py 
"""
#print(sys.argv[0])
# print(type(sys.argv))
# print(str(sys.argv))
# for arg in sys.argv:
#     print(arg)

n = len(sys.argv)
if n != 1:
    print("Invalid number of command line arguments ({})\n".format(n) + usage)
    sys.exit(1)


# read toc.txt
# create array from toc.txt
lines = []
with open('toc.txt', 'r') as f:
  for line in f:
    lines.append(line.rstrip())
f.close()
 
N = len(lines)
i = 1
pages = {}
names = []
for line in lines:
    print("{} ".format(i)+line)
    split = line.split('|')
    title = split[0].strip()
    name = split[1].strip()
    numtitle = str(i) + "-" + title
    src = name+"/template.md"
    dest = name+".md"
    link = "[{}]({})".format(title, dest)
    numlink = "[{}]({})".format(numtitle, dest)
    page = {
        "index": i,
        "name": name,
        "title": title,
        "numtitle": numtitle,
        "src": src,
        "dest": dest,
        "link": link,
        "numlink": numlink,
        "prev": None,
        "next": None,
    }
    pages[name] = page
    names.append(name)
    i += 1


for i in range(N):
    name = names[i]
    page = pages[name]
    if (i > 0): 
        page["prev"] = names[i-1]
    if (i < N-1): 
        page["next"] = names[i+1]



with open('toc.json', 'w') as f:
    json.dump(pages, f,  indent=2)



header = """

# Mathématiques __VERSION_MATHQ__

_This document was automatically generated by doc/Makefile on {}_

""".format(today)



f = open("top/template.md", 'r')
body = f.read()
f.close()

toc1 = """
-------------------------

# Table of Contents

""".format()


toc2 = ""
for name in pages:
    page = pages[name]
    toc2 += str(page["index"]) + ". " + page["link"] + "\n"

f = open("README.md", "w")
f.write(header + body + toc1 + toc2)
f.close()


header = "# Mathématiques __VERSION_MATHQ__\n"

footer = """

_This document was automatically generated by doc/Makefile on {}_

""".format(today)


f = open("toc.md", "w")
f.write(header + toc1 + toc2 + footer)
f.close()
