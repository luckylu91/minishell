#include "execution.h"

void	save_fd(int *save, int *fd)
{
	int i;

	i = 0;
	while(i < 256)
	{
		printf("i = %i\n",i);
		if (fd[i] >= 0)
		{

			save[i] = dup(i);
		printf("if i = %i %i\n",i, fd[i]);
			dup2(fd[i], i);

	ft_putstr_fd("leto\n", 2);

		ft_putstr_fd("letal\n",2);
		}
		i++;
	}
}

void	restore_fd(int *save, int *fd)
{
	int i;

	i = 0;
	while (i <256)
	{
		if (fd[i] >=0)
		{

			ft_putstr_fd("leto\n", 2);
			ft_putstr_fd(ft_itoa(i), 2);
			ft_putstr_fd("\n", 2);
			dup2(save[i], i);
			close(fd[i]);
		}
		i++;
	}
}
