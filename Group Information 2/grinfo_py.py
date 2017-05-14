#!/usr/bin/python
#Abhishek Polavarapu
#Assignment 2
#UIN:01028922

import os
import sys
import collections

def assignment2(count):
	x=0
	order1 = collections.OrderedDict()
	order2 = collections.OrderedDict()	
	path1 = os.popen("getent group")
	result1 = path1.readlines()
	path2 = os.popen("getent passwd")
	result2 = path2.readlines()
	list=[];
	for line in result1:
		a = (line.split(':')[0])
		b = (line.split(':')[2])
		order1[b] = a;
	for line in result2:
		if line not in ['\n', '\r\n']:
			b = (line.split(':')[3])
			a = (line.split(':')[0])
			list.append(b);
	counts = collections.Counter(list)
	for key, value in counts.items():
		order2[key] = value
	print "Count\tGID\tName"
	print "----\t", "----\t","----"
	for key in order1:
		if (key in order2.keys()):
			if(int(order2[key]) >= int(count)):
				print int(order2[key]) ,"\t" , key , " \t" , order1[key]
				x +=1			
	print "There are (", str(x),")groups with at least ("  , str(count) , ")members"
	return

print "Retrieving Data\n";
if len(sys.argv)<3:
	print "Usage: grinfo.pl [-c <count>]"
	print "Examples:"
	print "\tgrinfo.pl       // Help"
	print "\tgrinfo.pl -c 10 // List groups of at least 10"

elif(sys.argv[1]!="" and sys.argv[0]!=""):
	count = sys.argv[2]
	assignment2(count);
	