#ifndef AST_ST_MACHINE
#define AST_ST_MACHINE

#include "ast.h"
#include <stdlib.h>

typedef struct	s_ast_st_machine
{
	t_ast		*ast;
	t_ast		*ast_building;
	int			begining;
	int			building_cmd;
	int			chaining_cmd; // 0, 1
	char		*cmd_chain_op;
	int			building_redir; // 0, 1
	char		*redir_op;
}				t_ast_st_machine;

#endif