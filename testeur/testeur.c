#include <stdlib.h>
#include "testeur.h"

void	test_line(char *line)
{
	
	process_line(ft_strjoin(line, " > our_res"));
	system(ft_strjoin(line, " > bash_res"));
	system("diff bash_res our_res");
}

int main()
{

//	system("ls | grep a");
//	system("ls");
	test_line("ls | grep a");
}
