#include "ast_st_machine.h"

static void init_ast_st_machine(t_ast_st_machine *st);

int create_ast_st_machine(t_ast_st_machine **st)
{
	if (!st)
		return ();
	*st = ft_calloc(1, sizeof(t_ast_st_machine));
	if (!*st)
		return ();
	init_ast_st_machine(*st);
}

static void init_ast_st_machine(t_ast_st_machine *st)
{
	st->ast = NULL;
	st->begining = 1;
	st->building_cmd = 0;
	st->chaining_cmd = 0;
	st->cmd_chain_op = NULL;
	st->building_redir = 0;
	st->redir_op = NULL;
}