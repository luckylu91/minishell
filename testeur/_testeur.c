#include <stdlib.h>
#include "testeur.h"


char	*name_file(int c)
{
	return (ft_strjoin("./testeur_file/diff",ft_itoa(c)));	
}
void	test_line(char *line)
{

	int static compteur;
	int i;
	int r;
	char buff[1];
	char *diff;

	diff = name_file(compteur);
	process_line_test(ft_strjoin(line, " > ./testeur_file/our_res"));
	system(ft_strjoin(line, " > ./testeur_file/bash_res"));
	system(ft_strjoin("diff ./testeur_file/bash_res ./testeur_file/our_res >", diff));
	i = open(diff, O_RDONLY);
	r = read(i,buff,1);
	printf("testavant test\n");
	if (buff[0] == '\0')
		printf("\nPOUR  #%s# test %i [OK]",line, compteur);
	else
		printf("\nPOUR #%s# test %i [ERR]",line, compteur);
	compteur++;
	close(i);
}	

int main()
{
//	printf("mange mes couilles\n");
//	system("ls | grep a");
//	system("ls");
	//test_line("ls | grep a");
	//test_line("echo ~");
	//test_line("pwd | grep h");
	
	test_line("echo a");
//	test_line("echo b");
}
