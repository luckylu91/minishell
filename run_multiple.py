import random as r
import subprocess
import statistics
import os
import shutil

n_runs = 10
n_nums = 100
range_min = 0
range_max = 500

def get_score(start, stop, n):
	result = r.sample(list(range(start, stop)), n)
	result = [str(n) for n in result]
	proc = subprocess.Popen(['./push_swap'] + result, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	out, err = proc.communicate()
	out = out.decode("utf-8")
	return len(out.split('\n')) - 1, result, out

scores_in_out = []
for i in range(n_runs):
	scores_in_out.append(get_score(range_min, range_max, n_nums))
scores_in_out = list(sorted(scores_in_out, key = lambda x: x[0]))

dir_name = 'results'
if os.path.isdir(dir_name):
	shutil.rmtree(dir_name)
os.mkdir(dir_name)

for i, (score, algo_in, algo_out) in enumerate(scores_in_out):
	fin = open(os.path.join(dir_name, str(i) + '_in_score_' + str(score)), 'w')
	fin.write(str(algo_in))
	fin.close()
	fout = open(os.path.join(dir_name, str(i) + '_out_score_' + str(score)), 'w')
	fout.write(algo_out)
	fout.close()
f = open(os.path.join(dir_name,'stats'), 'w')

scores, _, _ = zip(*scores_in_out)

print("moyenne :", statistics.mean(scores))
print("max :", max(scores))
