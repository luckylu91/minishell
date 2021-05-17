CC = clang
SUBDIRS_ALL = $(shell find . -type d | grep -Ev "(.git|.vscode|.dSYM|__norm_py_old__)")
SUBDIRS = $(filter-out ./test_%, $(SUBDIRS_ALL))
SUBDIRS_TEST = $(filter ./test_%, $(SUBDIRS_ALL))
TEST_EXECS = $(filter-out %.c %.h, $(shell find $(SUBDIRS_TEST) -maxdepth 1 -mindepth 1))
IFLAGS = $(addprefix -I, $(SUBDIRS))
LFLAGS = -Llibft -lft -lncurses
DBFLAGS = -g3 -fsanitize=address
SRCS = $(addprefix ast/add/, add_textitem_totext.c add_textredir_tocmd.c add_cmd_tochain.c addback_none_block_nodup.c addback_space_block.c)
SRCS += $(addprefix ast/create_destroy/, create_ast.c create_block.c destroy_block.c dup_block.c destroy_ast.c destroy_text_ast.c destroy_redir_ast.c destroy_unary_ast.c destroy_binary_ast.c destroy_command_ast.c)
SRCS += $(addprefix execution/, exe_cmd.c exe_ast.c split_path.c)
SRCS += $(addprefix ast/parse/, identify_semicol.c parse_cmd.c parse_cmdchain.c parse_cmdseq.c parse_redir.c parse_text.c skip_spaces.c to_str.c)
# SRCS += $(addprefix lst_utils/, )
SRCS += $(addprefix block_api/, block_at.c is_chainop.c is_eof.c is_redirop.c is_semicol.c is_space.c is_special.c is_wildcard.c parse_redirop.c is_text.c \
			is_dollar.c is_rawtext.c is_tilde.c)
SRCS += $(addprefix ast/errors/, unexpected_token.c)
SRCS += $(addprefix term/, init_termcaps.c init_termios.c termcaps_errors.c termcaps_utils.c bigger_calloc.c linebuffer.c prompt.c)
SRCS +=	$(addprefix searchdir/, dir_contains.c  dir_utils.c search_cmd.c)
SRCS +=	$(addprefix execution/builtin/, cd.c echo.c pwd.c export.c env.c export_todo.c unset.c export_utils.c)
SRCS +=	$(addprefix execution/replace_env/, replace_dquoted.c replace_env.c replace_unquoted.c remove_spaces.c remove_spaces_cmdchain.c our_getenv.c our_getcwd.c)
SRCS += $(addprefix error/, error_message.c ambiguous_redirect_error.c)
SRCS += $(addprefix to_block/, to_block_main.c dollar.c dquote.c quote.c separator.c to_block_utils.c redir_tild.c backslash.c)
SRCS += $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)
SRCS += $(addprefix hist/, add_hist_line.c create_hist.c destroy_hist.c file_utils.c get_hist_line.c move_hist.c parse_file.c read_truncate_histfile.c rewind_hist.c write_histfile.c)
SRCS += $(addprefix main/, current_line.c redirect_special_key.c process_line.c exit_properly.c)

SRCS += $(addprefix ast/_print/, print_ast.c print_block.c)
OBJS = $(SRCS:%.c=%.o)
LIBFT = libft/libft.a

echo:
	@echo $(TEST_EXECS)

$(LIBFT):
	make -C libft bonus

libft:
	make -C libft bonus

%.o:	%.c
	$(CC) -c $< -o $@ $(IFLAGS)

# .SECONDARY:	$(OBJS)
$(OBJS):	$(LIBFT)

_%:	_%.c $(OBJS)
	$(CC) $< $(OBJS) -o $@ $(IFLAGS) $(LFLAGS)

_%_db:	_%.c $(OBJS)
	$(CC) $< $(OBJS) -o $@ $(IFLAGS) $(LFLAGS) $(DBFLAGS)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -rf $(TEST_EXECS)

.PHONY: all libft clean fclean
