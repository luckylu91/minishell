#!/usr/bin/env python3
import sys
import re
import os
from colorama import Fore, Style

error_line_pattern = re.compile(
	r"(Error:\s+)(\w+)\s*" \
	r"\(line:\s*([0-9]+),\s*"
	r"col:\s*([0-9]+)\):\s*"
	r"(.*)\n")

lines = sys.stdin.readlines()
is_fname_line = True
i = 0
while i < len(lines):
	line = lines[i]
	if (is_fname_line):
		fname, status = line.split(':')
		fpath, ftail = os.path.split(fname)
		if (not status.strip().startswith('Error!')):
			print(line, end='')
			i += 1
			continue
		is_fname_line = False
	else:
		m = error_line_pattern.fullmatch(line)
		if not m:
			is_fname_line = True
			continue
		err1a, err1b, line, col, err2 = m.groups()
		print(
			f"{Fore.CYAN + fname + Style.RESET_ALL}:{line},{col}\n" \
			f"\t{Fore.LIGHTRED_EX + err2 + Style.RESET_ALL}")
	i += 1