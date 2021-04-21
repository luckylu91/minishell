#include "execution.h"

extern char **environ;

char	*get_char_from_block(t_list *l)
{
	return ((t_block)(l->content).str);

}
int		is_last(t_list *l, char c)
{
	if (((redir)l->content).redir_op->str[0] == c)
		return (1);
	if (l->next == NULL)
		return (0);
	return is_last(l->next, c);
}

int	get_redir_fd(both_fd *res, t_list *l)
{
	int v;
	int fd;

	if (((redir)l->content).redir_op->str[0] =='<') 
	{
		fd = open( get_char_from_block((((redir)(l->content)).file_name)->text->content), O_RDONLY);
		if (fd == -1)
		{	
			printf("erreur in fichier non existant\n");
			return (-1);
		}
		close(fd);
		if (is_last(l->next, '<'))
			res->in == (redir)l->content;
	}
	if (((redir)l->content).redir_op->str[0] =='>') 
	{
		fd = open(get_char_from_block((((redir)(l->content)).file_name)->text->content), O_CREAT | O_WRONLY);
		if (is_last(l->next, '>'))
			res->out == (redir)l->content;
		else
			write(fd,"\0",1);
		if (fd == -1)
		{
			printf("erreur ou fichier\n")
				return (-1);
		}
		close(fd);
	}
	if (l->next != NULL)
		return (get_redir_fd(res, l->next));
	return (1);
}

int	exe_cmd(command cmd, int *pipe, int state)
{
	char **all_path;
	both_fd fd;
	char **all_var;
	char* path;
	pid_t child;

	all_var = ft_lststrjoin(cmd.text_list);
	fd->in = NULL;
	fd->out = NULL;
	fd->int_in = -1;
	fd->int_out = -1;
	if ((get_redir_fd(&fd, cmd.redir_list)) > 0)
		return (-1);
	all_path = split_path();
	if (cmd.text_list == NULL)
		return ;
	path = search_cmd(all_path,all_var[0]); 
	if (path == NULL)
	{
		printf("commande introuvable\n");
		return (-1);
	}
	if (fd->in != NULL)
	{
		fd->int_in = open(get_char_from_list(fd->in.file_name->text), O_RDWR, 0666);
		if (fd->int_in == -1)
		{
			printf("erreur ouverture fichier in\n");
			return (-1);
		}
	}
	if (fd->out != NULL)
	{
		fd->int_out = open(get_char_from_list(fd->out.file_name->text), O_RDWR, 0666);
		if (fd->int_out == -1)
		{
			printf("erreur ouverture fichier out\n");
			return (-1);
		}
	}
	child = fork();
	if (child == 0)
	{
		if (state == 1 || state == 3)
			dup2(pipe[1],STDOUT_FILENO);
		if (state == 2 || state == 3)
			dup2(pipe[0],STDIN_FILENO);
		if (fd->int_in != -1)
			dup2(fd->int_in, fd->in.fildes);
		if (fd->int_out != -1)
			dup2(fd->int_out, fd->out.fildes);
		execve(path, all_var, environ);
	}
}
