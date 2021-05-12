#include "execution.h"
#include <sys/wait.h>

//extern char **environ;

extern t_minishell g_global_var;

char	*get_char_from_block(t_list *l)
{
	return (((t_block*)(l->content))->str);

}
void	dup_str(t_list *l, char **res, int i)
{
	enum flags f;
	//	printf("dup str i = %i\n",i);
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
	//	printf("t = %i\n",t);
	res = wrap_malloc(sizeof(char*) * (t + 1));
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
	//	printf("dans get redir |%s| \n",get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)));
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
		//		printf("mais c'est pas possible\n");
		if (((t_ast*)l->content)->expr.redir.redir_op->str[1] =='>')
			fd = open(get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)), O_CREAT | O_RDWR | O_APPEND, 0666);
		else
			fd = open(get_char_from_block((((t_ast*)(l->content))->expr.redir.file_name)), O_CREAT | O_RDWR, 0666);
		if (is_last(l->next, '>'))
		{
			res->out = l->content;
			//			printf("la voie du seigneur\n");
		}
		else
			write(fd,"\0",1);
		if (fd == -1)
		{
			printf("erreur out fichier\n");
			return (-1);
		}
		close(fd);
	}
	return (get_redir_fd(res, l->next));
}

int		start_builtin(char **c)
{
//printf("start builtin |%s|\n",c[0]);
	if (ft_strcmp(c[0], "echo") == 0)
		return our_echo(c);
	if (ft_strcmp(c[0], "cd") == 0)
		 return our_cd(c);
	if (ft_strcmp(c[0], "pwd") == 0)
		return our_pwd(c);
	if (ft_strcmp(c[0], "export") == 0)
	{
//		printf("if export\n");
		return export(c, &(g_global_var.env));
	}
		else if (ft_strcmp(c[0], "unset") == 0)
	{
		//printf("if unset\n");
		//printf("adress = %p\n",&(g_global_var.env));
		return (our_unset(c, &(g_global_var.env)));
	}
	else if (ft_strcmp(c[0], "env") == 0)
	{
//		printf("start env\n");
		return (our_env(g_global_var.env));
	}
	else if (ft_strcmp(c[0], "exit") == 0)
		ft_exit();
	return (-1);
}

int		is_builtin(char *c)
{
	if (ft_strcmp(c, "echo") == 0)
		return (1);
	if (ft_strcmp(c, "pwd") == 0)
		return (1);
	if (ft_strcmp(c, "env") == 0)
		return (1);
	return (0);
}
int		is_builtin_nopipe(char *c)
{
	//printf("in is bultnopipe |%s|\n",c);
	if (ft_strcmp(c, "cd") == 0)
		return (1);
	if (ft_strcmp(c, "unset") == 0)
		return (1);
	if (ft_strcmp(c, "export") == 0)
		return (1);
	if (ft_strcmp(c, "exit") == 0)
		return (1);

	//printf("in is bultnopipe end \n");
	return (0);
}

int	exe_cmd(t_ast *cmd, int *pipe, int state, int *old_pipe)
{
	//printf("start exe_cmd\n");
	char **all_path;
	both_fd fd;
	char **all_var;
	int status;
	char* path;
	pid_t child;

	//printf("before fom list to str\n");
	all_var = from_list_to_str_tab(cmd->expr.command.text_list); 
	fd.in = NULL;
	fd.out = NULL;
	fd.int_in = -1;
	fd.int_out = -1;
	//printf("mange mes couilles \n");
	if ((get_redir_fd(&fd, cmd->expr.command.redir_list)) < 0)
		return (-1);
	all_path = split_path();

	if (cmd->expr.command.text_list == NULL)
	{
		//	printf("je deviens fou\n");
		return (-1);
	}
	//printf("manges tes morts\n");
	path = search_cmd(all_path,all_var[0]); 
	if (path == NULL && is_builtin(all_var[0]) == 0 && is_builtin_nopipe(all_var[0]) == 0)
	{
		g_global_var.exit_code = 127;
		printf("bash: %s: command not found\n", all_var[0]);
		return (-1);
	}
	if (is_builtin_nopipe(all_var[0]) && state != 0)
	{	
		if (state >0)
		{
			if (state != 1)
			{
				close(pipe[1]);
				close(pipe[0]);
			}
		}	
		return (-1);
	}
	else if (is_builtin_nopipe(all_var[0]))
	{
	
		g_global_var.exit_code = start_builtin(all_var);
		return (1);
	}
	
	//printf("avant le fork\n");
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		//printf("dans le fork\n");
		//printf("state = %i pipe 0=%ipipe 1=%i\n",state,pipe[0],pipe[1]);
	if (fd.in != NULL)
	{

		//	printf("in#####|%s|######\n", get_char_from_block(fd.in->expr.redir.file_name));
		fd.int_in = open(get_char_from_block(fd.in->expr.redir.file_name), O_RDWR, 0666);
		if (fd.int_in == -1)
		{
			printf("erreur ouverture fichier in\n");
			return (-1);
		}
	}
	if (fd.out != NULL)
	{

		//	printf("out#####|%s|######\n", get_char_from_block(fd.out->expr.redir.file_name));
		
	if (fd.out->expr.redir.redir_op->str[1] =='>') 
	{
		printf("doublette ?\n");
		fd.int_out = open(get_char_from_block(fd.out->expr.redir.file_name), O_WRONLY | O_APPEND, 0666);
	}
		else
		fd.int_out = open(get_char_from_block(fd.out->expr.redir.file_name), O_WRONLY |O_TRUNC, 0666);
		if (fd.int_out == -1)
		{
			printf("erreur ouverture fichier out\n");
			return (-1);
		}
	}

		//printf("dans le fork222\n");
		if (state == 1 && fd.out == NULL)
		{

			dup2(pipe[1],STDOUT_FILENO);
			close(pipe[0]);
			close(pipe[1]);
		}
		if (state == 3 && fd.out == NULL)
		{

			dup2(old_pipe[1], STDOUT_FILENO);
			close(old_pipe[0]);
			close(old_pipe[1]);
		}
		if ((state == 2 || state == 3) && fd.in == NULL)
		{
			dup2(pipe[0], STDIN_FILENO);
			close(pipe[1]);
			close(pipe[0]);
		}
		if (fd.int_in != -1)
		{
			dup2(fd.int_in, fd.in->expr.redir.fildes);
			//close(fd.int_in);
		}
		if (fd.int_out != -1)
		{
			dup2(fd.int_out, fd.out->expr.redir.fildes);
			//close(fd.int_out);
		}
		if (is_builtin(all_var[0]))
		{
			exit(start_builtin(all_var));
	//		printf("apres exit builtin\n");
		}
		else
			execve(path, all_var, g_global_var.env);
	}
	//printf("apres le fork\n");
	if (state >0)
	{
		if (state != 1)
		{
			close(pipe[1]);
			close(pipe[0]);
		}
	}
/*	if (fd.in != NULL)
		close(fd.int_in);
	if (fd.out != NULL)
		close(fd.int_out);
*/	//printf("avant wait\n");
	//waitpid(child, &status, 0);
	//printf("apres wait\n");
	/*if (WIFEXITED(status))
	{
		//printf("Child's exit code %d\n", WEXITSTATUS(status));
		g_global_var.exit_code = WEXITSTATUS(status);
	//	printf("hein ? %d\n",cmd->exit_code); 

	}
	else
		printf("Child did not terminate with exit\n");
	//wait(&status);*/
	return (child);
}
