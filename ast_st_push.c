#include "ast_st_machine.h"

int push_token(t_ast_st_machine *st, t_block *token)
{
	if (st->begining)
		ast_st_begin(st, token);
	else if (st->building_cmd)
		ast_st_cmd(st, token);
	else if (st->building_redir)
		ast_st_redir(st, token);
}
