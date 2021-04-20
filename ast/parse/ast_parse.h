#ifndef AST_PARSE_H
#define AST_PARSE_H

#include "ast_api.h"

t_status	parse_text(t_ast **text_ast, t_list **tokens);
t_status	parse_redir(t_ast **redir_ast, t_list **tokens);
t_status	parse_cmd(t_ast **cmd_ast, t_list **tokens);
t_status	parse_cmdchain(t_ast **cmdchain_ast, t_list **tokens);
t_status	parse_cmdseq(t_list **ast_list, t_list *tokens);
int	identify_semicol(t_list **tokens);
char	*to_str(t_list *block_lst);
void	skip_spaces(t_list **tokens);

// Experimental (build ast with text_list = blocks_list, and replace after env replacement)
t_status	parse_text_block_lst(t_list **text_block_list, t_list **tokens);
t_status	parse_redir_block_list(t_ast **redir_ast, t_list **tokens);
t_status	parse_cmd_block_list(t_ast **cmd_ast, t_list **tokens);

#endif
