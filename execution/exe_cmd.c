#include "execution.h"



int		is_last(t_list *l, char c)
{
	if (((redir)l->content).redir_op->str[0] == c)
		return (1);
	if (l->next == NULL)
		return (0);
	return is_last(l->next, c);
}

void	get_redir_fd(both_fd *res, t_list *l)
{
	int v;
	int fd;

	if (((redir)l->content).redir_op->str[0] =='<') 
	{
		fd =open((char*)((((redir)l->content).file_name)->text->content, O_RDONLY));
		if (fd == -1)
		{	
			printf("erreur in fichier non existant\n");
			return ;
		}
		close(fd);
		if (is_last(l->next, '<'))
			res->in == (redir)l->content;
	}
	if (((redir)l->content).redir_op->str[0] =='>') 
	{
		fd =open((char*)((((redir)l->content).file_name)->text->content), O_CREAT | O_WRONLY);
		if (is_last(l->next, '>'))
			res->out == (redir)l->content;
		else
			write(fd,"\0",1);
		if (fd != -1)
			close(fd);
	}
	if (l->next != NULL)
		get_redir_fd(res, l->next);
}

void	exe_cmd(command cmd)
{
	char **all_path;
	both_fd fd;

	fd->in = NULL;
	fd->out = NULL;
	get_redir_fd(&fd, cmd.redir_list);
	all_path = split_path();
	if (cmd.text_list == NULL)
		return ;


}
