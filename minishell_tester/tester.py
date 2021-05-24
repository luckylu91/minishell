import subprocess

proc = subprocess.Popen(['./minishell'] + result, stdout=subprocess.PIPE, stderr=subprocess.PIPE)