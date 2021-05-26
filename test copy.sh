touch tmp/cmds

for i in seq []
	echo 'ls | cat | grep m ; echo tamere' >> tmp/cmds
	echo 'echo a 1>tmp/1 1>>tmp/1 1>tmp/2 2>tmp/2 255>tmp/255 256>tmp/256'  >> tmp/cmds