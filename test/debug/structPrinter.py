#!/usr/bin/env python3.4
# test.py for  in /home/penava_b/perso/test/structPrinter
# 
# Made by penava_b
# Login   <penava_b@epitech.net>
# 
# Started on  Tue Jan 19 05:06:26 2016 penava_b
# Last update Tue Jan 19 06:57:12 2016 penava_b
##

from fileinput import input
import re

def main():
  data = []
  for line in input():
    data.append(line.rstrip('\n'))
  for x in re.findall(r'struct[ \t\n]*[a-zA-Z0-9_]*[ \t\n]*{[a-zA-Z0-9_; \n\t\(\)\*]*};', '\n'.join(data)):
    tmp = []
    x = x.replace('\n', '')
    for tmp2 in x.split(';'):
      if (len(tmp2.rstrip(' ').rstrip('\t')) > 0):
        tmp.append(tmp2)
    tmp.append('')
    x = ';\n'.join(tmp)
    x = '\n{\n'.join(x.split('{'))
    for tmp in x.split('\n'):
      if '};' in tmp:
        tmp = tmp.strip(' ').strip('\t')
      print(tmp)

if __name__ == "__main__":
  main()
