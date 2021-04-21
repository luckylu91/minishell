#include "execution.h"


int		exe_ast(t_list *l_ast, int i)
{
	if ((t_ast*)(l_ast->content).type == command_expr)
	{
		if (i == 0)
			exe_cmd((command)(*(t_ast->content)),NULL,0);
		else
			exe_cmd((command)(*(t_ast->content)),NULL,2);
	}
	else if ((t_ast*)(l_ast->content).type == binary_expr)
	{
		if (i == 0)
			exe_cmd((binary)(*(t_ast->content))->left,NULL,1);
		else
			exe_cmd((binary)(*(t_ast->content))->left,NULL,3);
		exe_ast((binary)(*(t_ast->content))->right, 1);
	}
}
