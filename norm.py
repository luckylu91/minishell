import os
import re
import sys
from optparse import OptionParser
import shutil

old_dirname = '__norm_py_old__'
dirnames_to_exclude = ['.git', '.vscode']

proto_patt = re.compile(r'((?:[_a-zA-Z]\w*\**\s+)(?:\**[_a-zA-Z]\w*\s+)*)(\**\w+\(.*\)\s*)')
h_proto_patt = re.compile(r'((?:[_a-zA-Z]\w*\**\s+)(?:\**[_a-zA-Z]\w*\s+)*)(\**\w+\(.+\)\s*;)')
fun_var_patt = re.compile(r'\t((?:[_a-zA-Z]\w*\**\s+)(?:\**[_a-zA-Z]\w*\s+)*)(\**\w+(?:\[\w+\])*;)')
proc_patt = re.compile(r'#\s*(.+)')
ifproc_patt = re.compile(r'#if')
ifndef_patt = re.compile(r'#ifndef\s(\w+)')
endif_patt = re.compile(r'#endif')


def print_declare_group(declare_group, lines_out):
	groups = [(' '.join(re.findall('\w+', m.group(1))), m.group(2))
		for m in declare_group]
	max_space = max(len(grp[0]) for grp in groups)
	print("max_space = ", max_space)
	varname_col = (max_space // 4 + 1) * 4
	print("varname_col = ", varname_col)
	for grp in groups:
		n = len(grp[0])
		n_tabs = (varname_col - len(grp[0]) - 1) // 4 + 1
		line = '\t' + grp[0] + n_tabs * '\t' + grp[1] + '\n'
		lines_out.append(line)

def norm_c(fname, fname_old=None):
	f = open(fname, "r")
	lines_out = []
	lines = f.readlines()
	if (fname_old):
		f_old = open(fname_old, "w")
		f_old.writelines(lines)
		f_old.close()
	declare_group = []

	for line in lines:
		if len(line) == 0:
			if len(declare_group) > 0:
				print_declare_group(declare_group, lines_out)
				declare_group = []
			lines_out.append('\n')
			continue
		m = proto_patt.match(line)
		if m:
			if len(declare_group) > 0:
				print_declare_group(declare_group, lines_out)
				declare_group = []
			line = m.group(1).strip() + '\t' + m.group(2).strip() + '\n'
			lines_out.append(line)
			continue
		m = fun_var_patt.match(line)
		if m:
			declare_group.append(m)
			continue
		if len(declare_group) > 0:
			print_declare_group(declare_group, lines_out)
			declare_group = []
		lines_out.append(line)
	
	if len(declare_group) > 0:
		print_declare_group(declare_group, lines_out)
		declare_group = []
	f.close()
	f = open(fname, "w")
	f.writelines(lines_out)
	if lines_out[-1] != '\n':
		f.write('\n')
	f.close()

def print_proto_groups(proto_groups, lines_out):
	groups = [(' '.join(re.findall('\w+', m.group(1))), m.group(2))
		for m in proto_groups]
	max_space = max(len(grp[0]) for grp in groups)
	print("max_space = ", max_space)
	varname_col = (max_space // 4 + 1) * 4
	print("varname_col = ", varname_col)
	for grp in groups:
		n = len(grp[0])
		n_tabs = (varname_col - len(grp[0]) - 1) // 4 + 1
		line = grp[0] + n_tabs * '\t' + grp[1] + '\n'
		lines_out.append(line)

def norm_h(fname, fname_old=None):
	f = open(fname, "r")
	lines_out = []
	lines = f.readlines()
	if (fname_old):
		f_old = open(fname_old, "w")
		f_old.writelines(lines)
		f_old.close()
	proto_groups = []
	declare_group = []

	proc_indent_level = 0

	for line in lines:
		if len(line) == 0:
			if len(proto_groups) > 0:
				print_proto_groups(proto_groups, lines_out)
				proto_groups = []
			elif len(declare_group) > 0:
				print_declare_group(declare_group, lines_out)
				declare_group = []
			lines_out.append('\n')
			continue
		m = proc_patt.match(line)
		if m:
			if len(proto_groups) > 0:
				print_proto_groups(proto_groups, lines_out)
				proto_groups = []
			# proc line
			content = m.group(1)
			if ifproc_patt.match(line): # #ifdef / #ifndef
				line_out = '#' + proc_indent_level * ' ' + content + '\n'
				proc_indent_level += 1
			elif endif_patt.match(line): # #endif
				proc_indent_level = max(0, proc_indent_level - 1)
				line_out = '#' + proc_indent_level * ' ' + content + '\n'
			else:
				line_out = '#' + proc_indent_level * ' ' + content + '\n'
			lines_out.append(line_out)
			continue

		m = h_proto_patt.match(line)
		if m:
			proto_groups.append(m)
			continue
			
		m = fun_var_patt.match(line)
		if m:
			declare_group.append(m)
			continue
		
		if len(proto_groups) > 0:
			print_proto_groups(proto_groups, lines_out)
			proto_groups = []
		elif len(declare_group) > 0:
			print_declare_group(declare_group, lines_out)
			declare_group = []
		
		lines_out.append(line)
	
	
	if len(proto_groups) > 0:
		print_proto_groups(proto_groups, lines_out)
		proto_groups = []
	elif len(declare_group) > 0:
		print_declare_group(declare_group, lines_out)
		declare_group = []

	f.close()
	f = open(fname, "w")
	f.writelines(lines_out)
	if lines_out[-1] != '\n':
		f.write('\n')
	f.close()

# argc = len(sys.argv)
# if (sys.argc > 1):
# 	if (sys.argv[1]) == '-a':
		# for root, dirs, files in os.walk('.')



parser = OptionParser()
parser.add_option("-r", "--recursive", dest="recursive",
	help="Apply recursively to every .c", action="store_true")
parser.add_option("-d", "--directory",
	action="store", dest="directory", default='.',
	help="Specify a starting directory when the -r / --recursive option is used")
parser.add_option("-s", "--save-old", dest="save_old",
	help="Whether to save the old version of the file (for mistrusting people)",
	action="store_true")

(options, args) = parser.parse_args()

def strip_beg(name):
	return name[2:] if name.startswith('./') else name

def is_source(fname):
	return (fname.endswith('.c') or fname.endswith('.h'))

def contains_no_source(dirname):
	return (not any([is_source(fname) for fname in os.listdir(dirname)]))

if (options.recursive):
	if options.save_old:
		try:
			shutil.rmtree(old_dirname)
			print("deleting", old_dirname)
		except:
			pass
		try:
			os.mkdir(old_dirname)
			print("making", old_dirname)
		except OSError as error:
			print(f'Cannot create directory {old_dirname} for saving old version of files')
			print(error)
			exit()

	if (options.save_old and options.directory != '.'):
		os.mkdir(os.path.join(old_dirname, options.directory))

	for root, dirs, files in os.walk(options.directory):
		root = strip_beg(root)
		# dirs = [strip_beg(n) for n in dirs]
		# files = [strip_beg(n) for n in files]

		if (root.split('/')[0] in dirnames_to_exclude):
			continue
		print("root :", root)

		if options.save_old:
			root_old = old_dirname if root == '.' else os.path.join(old_dirname, root)
			print("root_old :", root_old)
			for dirname in dirs:
				if (dirname.split('/')[0] in dirnames_to_exclude):
					continue
				os.mkdir(os.path.join(root_old, dirname))
				print("making", os.path.join(root_old, dirname))
		
		for file in files:
			fpath = os.path.join(root, file)
			if not is_source(fpath):
				continue
			fpath_old = None if not options.save_old else os.path.join(root_old, file)
			if (not fpath.endswith('.c') and not fpath.endswith('.h')):
				print(f'Ignoring file {fpath}, not a .c or .h file')
				continue
			if (fpath.endswith('.c')):
				norm_c(fpath, fpath_old)
			else:
				norm_h(fpath, fpath_old)
			# norm_c(fpath, fpath_old)
else:
	if len(args) != 1:
		print("Not enough arguments")
		exit()
	if (not args[0].endswith('.c') and not args[0].endswith('.h')):
		print(f'Ignoring file {args[0]}, not a .c or .h file')
		exit()
	if options.save_old:
		fpath = args[0]
		spl = fpath.split('.')
		fpath_old = '.'.join(spl[:-1]) + '_old' + '.' + spl[-1]
	else:
		fpath = args[0]
		fpath_old = None
	if (args[0].endswith('.c')):
		norm_c(fpath, fpath_old)
	else:
		norm_h(fpath, fpath_old)






# norm('test.c')
