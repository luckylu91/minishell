import os
import re

proto_patt = re.compile('(\w+)\s+(.+)')
fun_var_patt = re.compite('\t(\w+)\s+(\w+);')

# for root, dirs, files in os.walk():
f = open("test.c")
lines = f.readlines()
declar_group = []
for line in lines:
	if len(line) == 0:
		if len(declar_group) > 0:
			max_space = max(len(m.group(1)) for m in declar_group)
			varname_col = (max_space + 1) / 4 * 4
			for m in declar_group:
				line = '\t' + m.group(1) + + m.group(2)

			declar_group = []
		print()
		continue
	m = proto_patt.fullmatch(line)
	if m:
		line = m.group(1) + '\t' + m.group(2)
		print(line)
	m = fun_var_patt.fullmatch(line)
	if m:
		declar_group.append(m)
	

f.close()
