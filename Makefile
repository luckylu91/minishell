SUBDIRS = $(shell find . -type d | grep -Ev "(.git|.vscode|.dSYM)")
IFLAGS = $(addprefix -I, $(SUBDIRS))
LFLAGS = -Llibft -lft -lncurses
DBFLAGS = -g3 -fsanitize=address
SRCS = $(addprefix ast/add/, add_textitem_totext.c add_textredir_tocmd.c add_cmd_tochain.c addback_none_block_nodup.c addback_space_block.c)
SRCS += $(addprefix ast/create_destroy/, create_ast.c create_block.c destroy_block.c dup_block.c destroy_ast.c)
SRCS += $(addprefix execution/, exe_cmd.c exe_ast.c split_path.c)
SRCS += $(addprefix ast/parse/, identify_semicol.c parse_cmd.c parse_cmdchain.c parse_cmdseq.c parse_redir.c parse_text.c skip_spaces.c to_str.c)
# SRCS += $(addprefix lst_utils/, )
SRCS += $(addprefix ast/print/, print_ast.c print_block.c)
SRCS += $(addprefix block_api/, block_at.c is_chainop.c is_eof.c is_redirop.c is_semicol.c is_space.c is_special.c is_wildcard.c parse_redirop.c is_text.c \
			is_dollar.c is_rawtext.c)
SRCS += $(addprefix ast/errors/, unexpected_token.c)

SRCS +=	$(addprefix execution/searchdir/, dir_contains.c  dir_utils.c search_cmd.c)
SRCS +=	$(addprefix execution/builtin/, cd.c echo.c pwd.c export.c)
SRCS +=	$(addprefix execution/replace_env/, replace_dquoted.c replace_env.c replace_unquoted.c remove_spaces.c remove_spaces_cmdchain.c)
SRCS += $(addprefix error/, error_message.c ambiguous_redirect_error.c)
SRCS += $(addprefix to_block/, to_block_main.c)
OBJS = $(SRCS:%.c=%.o)
LIBFT = libft/libft.a

$(LIBFT):
	make -C libft bonus

libft:
	make -C libft bonus

%.o:	%.c
	gcc -c $< -o $@ $(IFLAGS)

.SECONDARY:	$(OBJS)

_%:	_%.c $(OBJS) $(LIBFT)
	gcc $< $(OBJS) -o $@ $(IFLAGS) $(LFLAGS)
#$(DBFLAGS)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean

.PHONY: all libft clean fclean
