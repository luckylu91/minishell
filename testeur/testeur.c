#include <stdlib.h>
#include "testeur.h"

void	test_line(char *line)
{
	
	process_line(ft_strcat(line, " > our_res"));
	system(ft_strcat(line, " > bash_res"));
	system("diff bash_res our_res");
}

int main()
{

	system("ls | grep a");
}
