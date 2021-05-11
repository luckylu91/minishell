import os
import re
import sys
from optparse import OptionParser
import shutil

old_dirname = '__norm_py_old__'
dirnames_to_exclude = ['.git', '.vscode']

proto_patt = re.compile('(\w+)\s+(.+)')

fun_var_patt = re.compile('\t(\w+)\s+(\w+;)')

def print_declare_group(declare_group, lines_out):
	max_space = max(len(m.group(1)) for m in declare_group)
	print("max_space = ", max_space)
	varname_col = (max_space // 4 + 1) * 4
	print("varname_col = ", varname_col)
	for m in declare_group:
		n = len(m.group(1))
		n_tabs = (varname_col - len(m.group(1)) - 1) // 4 + 1
		line = '\t' + m.group(1) + n_tabs * '\t' + m.group(2) + '\n'
		lines_out.append(line)

def norm(fname, fname_old=None):
	f = open(fname, "r")
	lines_out = []
	lines = f.readlines()
	if (fname_old):
		f_old = open(fname_old, "w")
		f_old.writelines(lines)
		f_old.close()
	declare_group = []
	do_declare_group = False
	for line in lines:
		if len(line) == 0:
			if len(declare_group) > 0:
				print_declare_group(declare_group, lines_out)
				declare_group = []
			lines_out.append('\n')
			continue
		m = proto_patt.match(line)
		if m:
			line = m.group(1) + '\t' + m.group(2) + '\n'
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
print(options)

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
			print('Cannot create directory {} for saving old version of files'.format(old_dirname))
			print(error)
			exit()

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
				if (contains_no_source(os.path.join(root, dirname))):
					continue
				os.mkdir(os.path.join(root_old, dirname))
				print("making", os.path.join(root_old, dirname))
		for file in files:
			fpath = os.path.join(root, file)
			if not is_source(fpath):
				continue
			fpath_old = None if not options.save_old else os.path.join(root_old, file)
			print("fpath :", fpath)
			print("fpath_old :", fpath_old)
			# norm(fpath, fpath_old)



# norm('test.c')
