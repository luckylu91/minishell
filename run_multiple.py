import random as r
import subprocess
import statistics
import os
import shutil
from pathlib import Path
import shlex

bash_args = shlex.split("echo 'echo a' | ./minishell")
Path('test_dir').mkdir(parents = True, exist_ok = True)
proc = subprocess.Popen(['/bin/bash'] + bash_args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
out, err = proc.communicate()
out = out.decode("utf-8")
print(out)
