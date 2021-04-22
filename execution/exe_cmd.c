#include "execution.h"
#include <sys/wait.h>

extern char **environ;


char	*get_char_from_block(t_list *l)
{
	return (((t_block*)(l->content))->str);

}
void	dup_str(t_list *l, char **res, int i)
{
	enum flags f;
	printf("dup str i = %i\n",i);
	if (l != NULL)
	{

		f= ((t_block*)(l->content))->f; 
		if (f == none)
		{
			res[i] = get_char_from_block(l);
			dup_str(l->next, res, i + 1);
		}
		else
			dup_str(l->next, res, i);
	}
	else
		res[i] = NULL;
}

int		size_list(t_list *l)
{
	if (l == NULL)
		return 0;
	//printf("coucou |%s|\n",get_char_from_block(l);
	return size_list(l->next) + 1;

}
char **from_list_to_str_tab(t_list *l)
{
	int t;
	char **res;

	t = size_list(l);
	printf("t = %i\n",t);
	res = malloc(sizeof(char*) * (t + 1));
	dup_str(l, res, 0);
	res[t] = NULL;
	return (res);
}

int		is_last(t_list *l, char c)
{
	if (l == NULL)
		return (1);
	if ((((t_ast*)l->content)->expr.redir).redir_op->str[0] == c)
		return (0);
	return is_last(l->next, c);
}

int	get_redir_fd(both_fd *res, t_list *l)
{
	int v;
	int fd;
	
	if (l == NULL)
		return (1);
	printf("dans get redir |%s| \n",get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)));
	if ((((t_ast*)(l->content))->expr.redir).redir_op->str[0] =='<') 
	{
		fd = open(get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)), O_RDWR);
		if (fd == -1)
		{	
			printf("erreur in fichier non existant\n");
			return (-1);
		}
		close(fd);
		if (is_last(l->next, '<'))
			res->in = l->content;
	}
	if (((t_ast*)l->content)->expr.redir.redir_op->str[0] =='>') 
	{
		printf("mais c'est pas possible\n");
		fd = open(get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)), O_CREAT | O_RDWR, 0666);
		if (is_last(l->next, '>'))
		{
			res->out = l->content;
			printf("la voie du seigneur\n");
		}
			else
			write(fd,"\0",1);
		if (fd == -1)
		{
			printf("erreur ou fichier\n");
			return (-1);
		}
		close(fd);
	}
	return (get_redir_fd(res, l->next));
}

int	exe_cmd(t_ast *cmd, int *pipe, int state, int *old_pipe)
{
	printf("start exe_cmd\n");
	char **all_path;
	both_fd fd;
	char **all_var;
	char* path;
	pid_t child;

	all_var = from_list_to_str_tab(cmd->expr.command.text_list); 
	fd.in = NULL;
	fd.out = NULL;
	fd.int_in = -1;
	fd.int_out = -1;
	printf("mange mes couilles \n");
	if ((get_redir_fd(&fd, cmd->expr.command.redir_list)) < 0)
		return (-1);
	all_path = split_path();
	
	if (cmd->expr.command.text_list == NULL)
	{
		printf("je deviens fou\n");
		return (-1);
	}
	printf("manges tes morts\n");
	path = search_cmd(all_path,all_var[0]); 
	if (path == NULL)
	{
		printf("commande introuvable\n");
		return (-1);
	}
	if (fd.in != NULL)
	{
		fd.int_in = open(get_char_from_block(fd.in->expr.redir.file_name), O_RDWR, 0666);
		if (fd.int_in == -1)
		{
			printf("erreur ouverture fichier in\n");
			return (-1);
		}
	}
	if (fd.out != NULL)
	{

		printf("#####|%s|######\n", get_char_from_block(fd.out->expr.redir.file_name));
		fd.int_out = open(get_char_from_block(fd.out->expr.redir.file_name), O_RDWR, 0666);
		if (fd.int_out == -1)
		{
			printf("erreur ouverture fichier out\n");
			return (-1);
		}
	}
	printf("avant le fork\n");
	child = fork();
	if (child == 0)
	{
		printf("state = %i\n",state);
		if (state == 1)
		{
			
			dup2(pipe[1],STDOUT_FILENO);
			close(pipe[0]);
			close(pipe[1]);
		}
		if (state == 3)
		{
			
			dup2(old_pipe[1], STDOUT_FILENO);
			close(old_pipe[0]);
			close(old_pipe[1]);
		}
		printf("premier dup2 pipe[0] = %i stdin =%i\n",pipe[0], 0);
		if (state == 2 || state == 3)
		{
			dup2(pipe[0], STDIN_FILENO);
			close(pipe[1]);
		}
		printf("deuxieme dup2\n");
		if (fd.int_in != -1)
			dup2(fd.int_in, fd.in->expr.redir.fildes);
		printf("troisieme dup2\n");
		if (fd.int_out != -1)
			dup2(fd.int_out, fd.out->expr.redir.fildes);
		printf("quatrieme dup2\n");
		execve(path, all_var, environ);
		printf("apres execve\n");
	}
		close(pipe[1]);
		printf("avant wait\n");
		waitpid(child, NULL, 0);
		printf("apres wait\n");
		return (1);
}
