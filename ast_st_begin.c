#include "ast_st_machine.h"

int ast_st_begin(t_ast_st_machine *st, t_token *token)
{
	if (is_error(token))
		return (message_error(token, UNEXPECTED_TOKEN));
	if (is_rawstr(token))
	{
		
	}
	if (is_semicol(token))
	{
		if (st->building_cmd)
		{

		}
	}
		
}